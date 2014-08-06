
#include "SRTX/Data_router.h"
#include "SRTX/End_of_frame.h"
#include "SRTX/Linked_list.h"
#include "SRTX/Reference_time.h"
#include "SRTX/RTC.h"
#include "SRTX/Runtime_attributes.h"
#include "SRTX/Scheduler.h"
#include "base/XPRINTF.h"


namespace SRTX
{

    namespace
    {
        const char* const task_name = "Scheduler";
    }

    /* These are the elements that we are going to store in the rategroup list.
     */
    struct Sched_item
    {
        Sched_item(units::Nanoseconds p)
            : period(p), finished(true)
        {
        }

        Runtime_attributes rt_attr;
        Runtime_attributes_db::symbol_t* rt_attr_symbol;
        units::Nanoseconds period;
        Syncpoint sync;
        End_of_frame* eof_task;
        bool finished;
        units::Nanoseconds start_time;
        units::Nanoseconds end_time;

    };
    typedef Linked_list<Sched_item*> Sched_list;



    struct Scheduler_impl
    {
        /* A linked list of rategroups. Each rategroup has a Syncpoint that the
         * scheduler will signal to release all tasks in that rategroup
         * when its time for them to run.
         */
        Sched_list rategroup;
    };


    Scheduler::Scheduler() :
        Task(task_name),
        m_sched_impl(new Scheduler_impl),
        m_use_external_clock(false)
    {
        /* Presumably the base class set the valid flag to true. If we couldn't
         * allocate the schedule implementation structure, then construction
         * failed and we need to set the valid flag back to false.
         */
        if(NULL == m_sched_impl)
        {
            m_valid = false;
        }
    }


    Syncpoint* Scheduler::add_task(Task& p)
    {
        static unsigned int list_len = 0;
        const units::Nanoseconds p_period = p.get_period();
        const units::Nanoseconds s_period = get_period();

        /* If periodic tasks period is faster than the scheduler's period,
         * then reject the task as unschedulable. A periodic task is also
         * not schedulable if its period is not a modulo of the scheduler
         * period.
         */
        if((p_period < s_period) || ((p_period % s_period) != 0))
        {
            EPRINTF("Invalid task period: %"PRId64"\n", int64_t(p_period));
            return NULL;
        }

        Sched_list& list = m_sched_impl->rategroup;
        Sched_list::Node* n = list.head();

        /* Search for an existing rategroup entry with the same period.
         */
        while(n)
        {
            if(p_period == n->data->period)
            {
                /* Found the rategroup. Pass the associated syncpoint back to
                 * the task.
                 */
                return &(n->data->sync);
            }

            n = n->next();
        }

        /* Didn't find the rategroup. We'll have to add an entry in the list.
         */
        DPRINTF("Adding rategroup entry for %"PRId64" period\n",
                int64_t(p_period));
        Sched_item* item = new Sched_item(p_period);
        if(NULL == item)
        {
            return NULL;
        }

        /* Add a symbol table entry for the runtime attributes of the rategroup.
         */
        Runtime_attributes_db& rt_db = Runtime_attributes_db::get_instance();
        char name[SYM_ENTRY_STRLEN + 1];
        snprintf(name, SYM_ENTRY_STRLEN, "%s%"PRId64"",
                runtime_attr_symbol_prefix, int64_t(p_period));
        item->rt_attr_symbol = rt_db.add_symbol(name);
        if((NULL == item->rt_attr_symbol) ||
                (false == item->rt_attr_symbol->is_valid()))
        {
            EPRINTF("Failed while adding runtime attributes symbol table entry\n");
            delete item;
            return NULL;
        }

        /* If this is the scheduler's rategroup (which defines the minor
         * frame), then alias the runtime properties to the minor frame runtime
         * properties name.
         */
        if(p_period == s_period)
        {
            Runtime_attributes_db::symbol_t* rt_sym_alias =
                rt_db.alias_symbol(minor_frame_runtime_attr_symbol_name,
                        item->rt_attr_symbol);
            if((NULL == rt_sym_alias) || (false == rt_sym_alias->is_valid()))
            {
                EPRINTF("Failed while aliasing runtime attributes symbol table "
                        "entry\n");
                delete item;
                return NULL;
            }

            DPRINTF("Aliased the minor frame runtime attributes symbol\n");
        }

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
        snprintf(name, SYM_ENTRY_STRLEN, "End_of_frame_%"PRId64,
                int64_t(p_period));
        item->eof_task = new End_of_frame(name, item->finished, item->end_time);
        item->eof_task->set_properties(tprops);
        item->eof_task->start();

        return &(item->sync);
    }


    void Scheduler::remove_task(Task& p)
    {
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
        if(false == m_valid)
        {
            EPRINTF("%s:Invalid task\n", m_name);
            return false;
        }

        if(true == m_operational)
        {
            EPRINTF("%s:Is already running\n", m_name);
            return false;
        }

        /* Get the task attributes.
         */
        if(false == m_prop_symbol->entry->read(m_props))
        {
            EPRINTF("%s:Failed to get task properties\n", m_name);
            return false;
        }

        /* It doesn't matter what priority the user appplication passed in for
         * the Scheduler. We're going to make sure that it is the highest
         * priority task.
         */
        m_props.prio = MAX_PRIO;
        if(false == m_prop_symbol->entry->write(m_props))
        {
            EPRINTF("%s:Failed to set task priority\n", m_name);
            return false;
        }

        if(false == start_prep())
        {
            return false;
        }

        return spawn_thread();
    }


    bool Scheduler::execute()
    {
        static units::Nanoseconds time(0);

        DPRINTF("Begin executing the scheduler\n");

        /* If we let the period be zero, then the scheduler will always be
         * running.
         * TODO move this into an initialization routine called before
         * start().
         */
        if(0 == m_props.period)
        {
            EPRINTF("Invalid period\n");
            return false;
        }

        /* The first time through we have to get the time from the RTC.
         * Thereafter, we just add the period.
         */
        if(false == get_time(time))
        {
            EPRINTF("Failed to get the time\n");
            return false;
        }

        /* The scheduler tracks reference time. Reference time starts at zero
         * and gets incremented by the scheduler's period each time the
         * scheduler runs.
         */
        Reference_time& rtimer = Reference_time::get_instance();
        units::Nanoseconds ref_time(0);

        /* We have to have the mutex before calling wait.
         */
        if(false == m_sync.lock())
        {
            EPRINTF("Failed to get mutex\n");
            return false;
        }

        /* Get an reference to the data router. We'll be calling this to move
         * data for the pub/sub system.
         */
        Data_router& router = Data_router::get_instance();

        DPRINTF("Entering the scheduler loop\n");

        /* Here's the meat of the show! This stuff is done in an infinite loop
         * while the task is running.
         */
        Sched_list& list = m_sched_impl->rategroup;
        while(this->is_operational())
        {
            /* The scheduler goes to sleep until its runtime period has elapsed.
             * Time of zero means wait forever on the sync point. This allows
             * the scheduler to be driven by an external time source.
             */
            if(m_use_external_clock)
            {
                time = units::Nanoseconds(0);
            } else {
                time = units::Nanoseconds(m_props.period + time);
            }

            if(false == m_sync.wait(time))
            {
                EPRINTF("Scheduler wait failed\n");
                m_sync.unlock();
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

            DPRINTF("ref_time = %"PRId64"\n", int64_t(ref_time));

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
            Sched_list::Node* n = list.head();
            unsigned int item_num = 0;
            while(n)
            {
                ++item_num;
                DPRINTF("Checking list item number %u\n", item_num);
                if(0 == (ref_time % n->data->period))
                {
                    n->data->rt_attr.last_runtime = n->data->end_time -
                        n->data->start_time;

                    if(n->data->rt_attr.last_runtime >
                            n->data->rt_attr.max_runtime)
                    {
                        n->data->rt_attr.max_runtime =
                            n->data->rt_attr.last_runtime;
                    }

                    if(!n->data->finished)
                    {
                        WPRINTF("OVERRUN Rategroup %"PRId64"\n",
                                int64_t(n->data->period));
                        ++n->data->rt_attr.num_overruns;
                        n->data->rt_attr_symbol->entry->write(n->data->rt_attr);
                        /* If an overrun occurs in this rategroup, break out.
                         * If we try to grab the rategroup lock we could cause
                         * the scheduler to block for some non-deterministic
                         * period of time.
                         */
                        break;
                    }
                    n->data->rt_attr_symbol->entry->write(n->data->rt_attr);

                    DPRINTF("Signaling %"PRId64" period tasks\n",
                            int64_t(n->data->period));
                    n->data->sync.lock();
                    n->data->start_time = start_time;
                    n->data->finished = false;
                    n->data->sync.release();
                    n->data->sync.unlock();
                }

                n = n->next();
            }

            DPRINTF("Scheduler is running!\n");
        }

        /* Release the scheduler lock and exit the scheduler task.
         */
        m_sync.unlock();
        return false;
    }

    void Scheduler::terminate()
    {
        m_sync.lock();
        m_sync.release();
        m_sync.unlock();
    }


    Scheduler* Scheduler::m_instance(NULL);

} // namespace
