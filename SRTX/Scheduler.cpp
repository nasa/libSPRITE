#include <unistd.h>
#include "SRTX/Data_router.h"
#include "SRTX/End_of_frame.h"
#include "SRTX/Reference_time.h"
#include "SRTX/RTC.h"
#include "SRTX/Runtime_attributes.h"
#include "SRTX/Scheduler.h"
#include "util/Linked_list.h"
#include "base/types.h"
#include "base/XPRINTF.h"

namespace SRTX {

    namespace {
        const char *const task_name = "Scheduler";
        unsigned int sched_unwind_tics = 1;
    }

    /* These are the elements that we are going to store in the rategroup list.
    */
    struct Sched_item {
        Sched_item(units::Nanoseconds p)
            : rt_attr()
            , rt_attr_symbol(NULL)
            , period(p)
            , sync()
            , eof_task(NULL)
            , finished(true)
            , start_time(0)
            , end_time(0)
        {
        }

        Runtime_attributes rt_attr;
        Runtime_attributes_db::symbol_t *rt_attr_symbol;
        units::Nanoseconds period;
        Syncpoint sync;
        End_of_frame *eof_task;
        bool finished;
        units::Nanoseconds start_time;
        units::Nanoseconds end_time;

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Sched_item(const Sched_item &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Sched_item &operator=(const Sched_item &);
    };
    typedef util::Linked_list<Sched_item *> Sched_list;

    struct Scheduler_impl {
        Scheduler_impl()
            : rategroup()
            , sync()
        {
        }

        /* A linked list of rategroups. Each rategroup has a Syncpoint that the
         * scheduler will signal to release all tasks in that rategroup
         * when its time for them to run.
         */
        Sched_list rategroup;
        Syncpoint sync;
    };

    Scheduler &Scheduler::get_instance()
    {
        if(!m_instance) {
            m_instance = new Scheduler;
        }

        return *m_instance;
    }

    Scheduler::Scheduler()
        : Task(task_name)
        , m_sched_impl(new Scheduler_impl)
        , m_schedule(0)
        , m_use_external_clock(false)
    {
        /* Presumably the base class set the valid flag to true. If we couldn't
         * allocate the schedule implementation structure, then construction
         * failed and we need to set the valid flag back to false.
         */
        if(NULL == m_sched_impl) {
            m_valid = false;
        }
    }

    /* The number of unwind tics is the number of times the scheduler must run
     * to ensure that all rategroups have completed.
     */
    static void update_unwind_tics(unsigned int rate_unwind_tics)
    {
        if(rate_unwind_tics > sched_unwind_tics) {
            sched_unwind_tics = rate_unwind_tics;
        }
    }

    Syncpoint *Scheduler::add_task(Task &p)
    {
        static unsigned int list_len = 0;
        const units::Nanoseconds p_period = p.get_period();
        const units::Nanoseconds s_period = get_period();

        /* If periodic tasks period is faster than the scheduler's period,
         * then reject the task as unschedulable. A periodic task is also
         * not schedulable if its period is not a modulo of the scheduler
         * period.
         */
        if((p_period < s_period) || ((p_period % s_period) != 0)) {
            EPRINTF("Invalid task period: %" PRId64 "\n", int64_t(p_period));
            return NULL;
        }

        Sched_list &list = m_sched_impl->rategroup;
        Sched_list::Node *n = list.head();

        /* Search for an existing rategroup entry with the same period.
        */
        while(n) {
            if(p_period == n->data->period) {
                /* Found the rategroup. Pass the associated syncpoint back to
                 * the task.
                 */
                return &(n->data->sync);
            }

            n = n->next();
        }

        /* Didn't find the rategroup. We'll have to add an entry in the list.
        */
        DPRINTF("Adding rategroup entry for %" PRId64 " period\n",
                int64_t(p_period));
        Sched_item *item = new Sched_item(p_period);
        if(NULL == item) {
            return NULL;
        }

        /* Add a symbol table entry for the runtime attributes of the rategroup.
        */
        Runtime_attributes_db &rt_db = Runtime_attributes_db::get_instance();
        char name[SYM_ENTRY_STRLEN + 1];
        snprintf(name, SYM_ENTRY_STRLEN, "%s%" PRId64 "",
                 runtime_attr_symbol_prefix, int64_t(p_period));
        item->rt_attr_symbol = rt_db.add_symbol(name);
        if((NULL == item->rt_attr_symbol) ||
           (false == item->rt_attr_symbol->is_valid())) {
            EPRINTF(
                "Failed while adding runtime attributes symbol table entry\n");
            delete item;
            return NULL;
        }

        /* Initialize the runtime attribute data.
        */
        item->rt_attr_symbol->entry->write(item->rt_attr);

        DPRINTF("%s rategroup mutex is %p\n", name, &(item->sync));

        /* If this is the scheduler's rategroup (which defines the minor
         * frame), then alias the runtime properties to the minor frame runtime
         * properties name.
         */
        if(p_period == s_period) {
            Runtime_attributes_db::symbol_t *rt_sym_alias = rt_db.alias_symbol(
                minor_frame_runtime_attr_symbol_name, item->rt_attr_symbol);
            if((NULL == rt_sym_alias) || (false == rt_sym_alias->is_valid())) {
                EPRINTF("Failed while aliasing runtime attributes symbol table "
                        "entry\n");
                delete item;
                return NULL;
            }

            DPRINTF("Aliased the minor frame runtime attributes symbol\n");
        }

        update_unwind_tics(p_period / s_period);
        list.add_back(item);
        ++list_len;
        DPRINTF("List length is now %u\n", list_len);

        /*  Add a lowest priority task to this rategroup which its execution
         *  will signify the completion of all other tasks in this this
         *  rategroup.
         */
        Task_properties tprops;
        tprops.period = p_period;
        tprops.prio = MIN_PRIO;
        snprintf(name, SYM_ENTRY_STRLEN, "End_of_frame_%" PRId64,
                 int64_t(p_period));
        item->eof_task =
            new End_of_frame(name, item->finished, item->end_time, item->sync);
        item->eof_task->set_properties(tprops);
        item->eof_task->start();

        return &(item->sync);
    }

    void Scheduler::remove_task(Task &p)
    {
        (void)p; // suppress unused variable compiler warning.
#if 0
        Sched_list& list = m_sched_impl->rategroup;
        Sched_list::Node* n = list.head();

        /* Search for an existing rategroup entry with the same period.
        */
        while(n)
        {
            if(period == n->data->period)
            {
                /* Found the rategroup. Pass the associated syncpoint back to
                 * the task.
                 */

                /* TODO: Remove task from the linked list.
                */
                return;
            }

            n = n->next();
        }
#endif
    }

    bool Scheduler::start()
    {
        /* If construction was not successful, don't bother trying to start.
        */
        if(false == m_valid) {
            EPRINTF("%s:Invalid task\n", m_name);
            return false;
        }

        if(true == m_operational) {
            EPRINTF("%s:Is already running\n", m_name);
            return false;
        }

        /* Get the task attributes.
        */
        if(false == m_prop_symbol->entry->read(m_props)) {
            EPRINTF("%s:Failed to get task properties\n", m_name);
            return false;
        }

        /* It doesn't matter what priority the user appplication passed in for
         * the Scheduler. We're going to make sure that it is the highest
         * priority task.
         */
        m_props.prio = MAX_PRIO;
        if(false == m_prop_symbol->entry->write(m_props)) {
            EPRINTF("%s:Failed to set task priority\n", m_name);
            return false;
        }

        if(false == start_prep()) {
            return false;
        }

        return spawn_thread();
    }

    bool Scheduler::execute()
    {
        static units::Nanoseconds time(0);

        DPRINTF("Begin executing the scheduler\n");
        DPRINTF("Scheduler mutex addr is %p\n", &(m_sched_impl->sync));

        /* If we let the period be zero, then the scheduler will always be
         * running.
         * TODO move this into an initialization routine called before
         * start().
         */
        if(0 == m_props.period) {
            EPRINTF("Invalid period\n");
            return false;
        }

        /* The first time through we have to get the time from the RTC.
         * Thereafter, we just add the period.
         */
        if(false == get_time(time)) {
            EPRINTF("Failed to get the time\n");
            return false;
        }

        /* The scheduler tracks reference time. Reference time starts at zero
         * and gets incremented by the scheduler's period each time the
         * scheduler runs.
         */
        Reference_time &rtimer = Reference_time::get_instance();
        units::Nanoseconds ref_time(0);

        /* We have to have the mutex before calling wait.
        */
        if(false == this->lock()) {
            EPRINTF("Failed to get mutex\n");
            return false;
        }

        /* Get an reference to the data router. We'll be calling this to move
         * data for the pub/sub system.
         */
        Data_router &router = Data_router::get_instance();

        DPRINTF("Entering the scheduler loop\n");

        /* Here's the meat of the show! This stuff is done in an infinite loop
         * while the task is running.
         */
        Sched_list &list = m_sched_impl->rategroup;
        while(this->is_operational() || sched_unwind_tics) {
            /* If the scheduler has been asked to halt, start counting down the
             * unwind tics. The unwind tics make sure that all tasks have had
             * time to complete before the schduler exits and ceases scheduling
             * the tasks.
             */
            if(!(this->is_operational())) {
                --sched_unwind_tics;
                DPRINTF("Unwinding, %u tics left\n", sched_unwind_tics);
            }

            /* The scheduler goes to sleep until its runtime period has elapsed.
             * Time of zero means wait forever on the sync point. This allows
             * the scheduler to be driven by an external time source.
             */
            DPRINTF("Wait for next tic\n");
            if(m_use_external_clock) {
                time = units::Nanoseconds(0);
            } else {
                time = units::Nanoseconds(m_props.period + time);
            }

            m_sched_impl->sync.condition_cleared();
            if(false == m_sched_impl->sync.wait(time)) {
                EPRINTF("Scheduler wait failed\n");
                this->unlock();
                return false;
            }

            units::Nanoseconds start_time;
            get_time(start_time);

            /* Increment the reference timer by the period of the scheduler.
             * TODO This isn't really how I want to handle reference time.
             * Right now there is no lock around it so it could misbehave on
             * multicore. I think it should be sent via pub/sub message, but
             * I'm also using it as the predicate around the tasks wait
             * condition which makes some possibly undesirable dependencies.
             */
            ref_time = rtimer.increment(m_props.period);

            DPRINTF("ref_time = %" PRId64 "\n", int64_t(ref_time));

            /* Transfer all registered data that is scheduled to be moved this
             * period.
             */
            router.do_transfers(ref_time);
            DPRINTF("Data routing complete\n");

            /* For each rategroup, look to see if it is time to run.
             * TODO The rategroups should be in a sorted list so we can bail
             * early once we reach a period that is not modulo the reference
             * time.
             */
            unsigned int item_num = 0;
            for(Sched_list::Node *n = list.head(); n; n = n->next()) {
                ++item_num;
                DPRINTF("Checking list item number %u\n", item_num);
                if(0 == (ref_time % n->data->period)) {
                    if(n->data->finished) {
                        n->data->rt_attr.last_runtime =
                            n->data->end_time - n->data->start_time;

                        if(n->data->rt_attr.last_runtime >
                           n->data->rt_attr.max_runtime) {
                            n->data->rt_attr.max_runtime =
                                n->data->rt_attr.last_runtime;
                        }
                    } else {
                        WPRINTF("OVERRUN Rategroup %" PRId64 "\n",
                                int64_t(n->data->period));
                        ++(n->data->rt_attr.num_overruns);
#ifdef DEBUG_OVERRUN_BUG
                        fprintf(stderr, "num overruns = %u\n",
                                n->data->rt_attr.num_overruns);
                        fprintf(stderr, "last runtime = %ld\n",
                                int64_t(n->data->rt_attr.last_runtime));
                        fprintf(stderr, "max runtime = %ld\n",
                                int64_t(n->data->rt_attr.max_runtime));
#endif
                        n->data->rt_attr_symbol->entry->write(n->data->rt_attr);
                        /* If an overrun occurs in this rategroup, break out.
                         * If we try to grab the rategroup lock we could cause
                         * the scheduler to block for some non-deterministic
                         * period of time.
                         */
                        continue;
                    }
                    n->data->rt_attr_symbol->entry->write(n->data->rt_attr);

                    DPRINTF("Signaling %" PRId64 " period tasks\n",
                            int64_t(n->data->period));
                    if(false == n->data->sync.lock()) {
                        EPRINTF("Attaining rategroup lock\n");
                        continue;
                    }
                    n->data->start_time = start_time;
                    n->data->finished = false;
                    n->data->sync.condition_satisfied();
                    if(false == n->data->sync.release()) {
                        EPRINTF("Releasing rategroup\n");
                    }
                    if(false == n->data->sync.unlock()) {
                        EPRINTF("Releasing rategroup lock\n");
                    }
                }
            }

            DPRINTF("Scheduler is running!\n");
        }

        /* Release the scheduler lock and exit the scheduler task.
        */
        this->unlock();
        return false;
    }

    void Scheduler::terminate()
    {
        if(m_use_external_clock) {
            /* If we're set to use an external trigger, we need to generate the
             * necessary triggers internally to wind down all of the tasks to
             * allow for a clean exit.
             */
            const units::Nanoseconds s_period = get_period();
            while(sched_unwind_tics) {
                usleep(s_period / 1000);
                trigger();
            }
        } else {
            this->lock();
            m_sched_impl->sync.condition_satisfied();
            m_sched_impl->sync.release();
            this->unlock();
        }
    }

    bool Scheduler::lock()
    {
        return m_sched_impl->sync.lock();
    }

    bool Scheduler::unlock()
    {
        return m_sched_impl->sync.unlock();
    }

    void Scheduler::use_external_trigger(bool slave)
    {
        m_use_external_clock = slave;
    }

    bool Scheduler::trigger(void)
    {
        if(false == this->lock()) {
            EPRINTF("Error locking scheduler\n");
            return false;
        }

        if(!m_use_external_clock) {
            this->unlock();
            EPRINTF("Attempting to trigger when not using an external clock\n");
            return false;
        }

        m_sched_impl->sync.condition_satisfied();
        if(false == m_sched_impl->sync.release()) {
            this->unlock();
            EPRINTF("Error locking external clock trigger\n");
            return false;
        }

        if(false == this->unlock()) {
            EPRINTF("Error unlocking scheduler\n");
            return false;
        }

        return true;
    }

    Scheduler *Scheduler::m_instance(NULL);

} // namespace
