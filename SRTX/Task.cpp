#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include "SRTX/Reference_time.h"
#include "SRTX/RTC.h"
#include "SRTX/Scheduler.h"
#include "base/types.h"
#include "base/XPRINTF.h"

namespace SRTX {

    struct Task_impl {
        pthread_t tid;
        pthread_attr_t attr;
        Syncpoint *rategroup_sync;
        bool *rategroup_condition;
        struct sched_param sched_attr;
        units::Nanoseconds expected_wake_time;
        bool first_pass;

        Task_impl()
            : tid(0)
            , attr()
            , rategroup_sync(NULL)
            , rategroup_condition(NULL)
            , sched_attr()
            , expected_wake_time(0)
            , first_pass(true)
        {
        }
    };

    static volatile bool _thread_initializing;

    Task::Task(const char *name)
        : m_props()
        , m_prop_symbol(NULL)
        , m_valid(false)
        , m_operational(false)
        , m_name(NULL)
        , m_is_eof_task(false)
        , m_impl(new Task_impl)
    {
        /* Make sure the implementation specific data got allocated.
        */
        if(NULL == m_impl) {
            EPRINTF("Failed to allocation task implementation "
                    "attributes\n");
            return;
        }

        /* Create a task attribute entry in the task database.
        */
        Task_db &proc_db = Task_db::get_instance();

        m_prop_symbol = proc_db.add_symbol(name);
        if((NULL == m_prop_symbol) || (false == m_prop_symbol->is_valid())) {
            EPRINTF("Failed while adding task symbol table entry\n");
            return;
        }

        /* Store a pointer to the task name.
        */
        m_name = m_prop_symbol->get_name();

        /* Initialize the pthread attributes.
        */
        if(pthread_attr_init(&(m_impl->attr)) != 0) {
            EPRINTF("Failed to initialize thread attributes\n");
            return;
        }

        DPRINTF("Shared thread mutex is %p\n", &(m_thread_syncpoint));

        m_valid = true;
    }

    bool Task::set_properties(const Task_db::value_t &props)
    {
        return m_valid && m_prop_symbol->entry->write(props);
    }

    void *Task::run(void *arg)
    {
        Task *p = reinterpret_cast<Task *>(arg);
        struct sched_param sched_attr;
        int policy;
        pthread_t tid = pthread_self();
        Scheduler &sched = Scheduler::get_instance();

        m_thread_syncpoint.lock();
        m_thread_syncpoint.condition_satisfied();

        /* Set the scheduler parameters. Linux at least fails when the
         * parameters are set before creating the thread. The parameters must
         * be set BY the affected thread. Stupid little penguins!!!
         */
        if(pthread_getschedparam(tid, &policy, &sched_attr) != 0) {
            m_thread_syncpoint.release();
            m_thread_syncpoint.lock();
            EPRINTF("Failed getting task schedule parameters\n");
            return NULL;
        }

        policy = SCHED_FIFO;
        sched_attr.sched_priority = p->m_props.prio;
        if(pthread_setschedparam(tid, policy, &sched_attr) != 0) {
            m_thread_syncpoint.release();
            m_thread_syncpoint.unlock();
            EPRINTF("Failed setting task schedule parameters\n");
            EPRINTF("Did you remember sudo?\n");
            return NULL;
        }

        /* Make sure the thread is being scheduled at the right priority. Linux
         * requires that the application be run as root or permissions have
         * been set through PAM to allow use of real time thread priority
         * scheduling. Otherwise, the checks below will fail and we'll exit the
         * thread.
         */
        if(pthread_getschedparam(tid, &policy, &sched_attr) != 0) {
            m_thread_syncpoint.release();
            m_thread_syncpoint.unlock();
            EPRINTF("Failed getting task schedule parameters\n");
            return NULL;
        }

        if(SCHED_FIFO != policy) {
            m_thread_syncpoint.release();
            m_thread_syncpoint.unlock();
            EPRINTF("Failed to set real time scheduling policy\n");
            return NULL;
        }

        if(sched_attr.sched_priority != static_cast<int>(p->m_props.prio)) {
            m_thread_syncpoint.release();
            m_thread_syncpoint.unlock();
            EPRINTF("Failed to set real time priority for task %s\n",
                    p->m_name);
            return NULL;
        }

        DPRINTF("Successfully registered task %s at priority %d\n", p->m_name,
                sched_attr.sched_priority);

        units::Nanoseconds ref_time(0);

        p->m_operational = true;
        m_thread_syncpoint.release();
        m_thread_syncpoint.unlock();

        while(true) {
            units::Nanoseconds start_time(0);
            get_time(start_time);

            /* If this is a periodic tasks, wait to be scheduled.
            */
            if(p->m_impl->rategroup_sync) {
                if(p->m_impl->first_pass) {
                    /* We grab the lock and hold it while we're executing so no
                     * other task jumps in. One task at a time per
                     * rategroup!  The lock gets released once we get into the
                     * wait call.
                     */
                    p->m_impl->rategroup_sync->lock();

                    /* Compute a wake up time to be used on the first pass.
                    */
                    p->m_impl->expected_wake_time = get_reference_time();
                    p->m_impl->expected_wake_time -=
                        p->m_impl->expected_wake_time % p->m_props.period;

                    p->m_impl->first_pass = false;
                }

                /* We use reference time as a post condition for the wait. The
                 * reference time when we wake up should be later than the time
                 * at which we went to sleep. Otherwise, we've experienced a
                 * spurious wakeup.
                 */
                p->m_impl->expected_wake_time += p->m_props.period;
                DPRINTF("%s: expected wake time = %" PRId64 "\n", p->m_name,
                        int64_t(p->m_impl->expected_wake_time));

                while((true == p->m_operational) &&
                      (ref_time = get_reference_time()) <
                          p->m_impl->expected_wake_time) {
                    DPRINTF("%s: Tref = %" PRId64
                            ", expected_wake_time = %" PRId64 "\n",
                            p->m_name, int64_t(ref_time),
                            int64_t(p->m_impl->expected_wake_time));
                    if(false == p->m_impl->rategroup_sync->wait()) {
                        EPRINTF("%s: Error in periodic wait\n", p->m_name);
                        p->m_impl->rategroup_sync->unlock();
                        return NULL;
                    }
                    DPRINTF("%s:Woke up\n", p->m_name);
                }

                DPRINTF("%s: Tref = %" PRId64 ", expected_wake_time = %" PRId64
                        "\n",
                        p->m_name, int64_t(ref_time),
                        int64_t(p->m_impl->expected_wake_time));

                /* Wait for all of the tasks to be awoken and ready to run.
                 * This relies on testing against an inverted wait condition
                 * because we're not going to clear the condition until all the
                 * tasks are awake. The end of frame task is allowed to begin
                 * execution because it is the last task on the list (in
                 * priority order). The end of frame task signals all of the
                 * others that they may proceed.
                 */
                if(false == p->m_is_eof_task) {
                    p->m_impl->rategroup_sync->inverse_wait();
                }
            }

            if(false == p->m_operational) {
                DPRINTF("%s: No longer operational\n", p->m_name);
                if(p->m_impl->rategroup_sync) {
                    p->m_impl->rategroup_sync->unlock();
                }

                return NULL;
            }

            if(p->m_props.is_present_in_schedule(sched.get_schedule()) ||
               (0 == p->m_props.period)) {
                DPRINTF("Executing task %s\n", p->m_name);
                if(false == p->execute()) {
                    DPRINTF("Task %s exiting\n", p->m_name);
                    p->terminate();
                    if(p->m_impl->rategroup_sync) {
                        p->m_impl->rategroup_sync->unlock();
                    }
                    return NULL;
                }
                units::Nanoseconds end_time(0);
                get_time(end_time);

                p->m_props.last_runtime = end_time - start_time;
                if(p->m_props.last_runtime > p->m_props.max_runtime) {
                    p->m_props.max_runtime = p->m_props.last_runtime;
                }
                DPRINTF("%s last_runtime = %" PRId64 ", max_runtime = %" PRId64
                        "\n",
                        p->m_name, int64_t(p->m_props.last_runtime),
                        int64_t(p->m_props.max_runtime));
            }
        }

        return NULL;
    }

    bool Task::start_prep()
    {
        /* Set pthread attributes.
        */
        if(pthread_attr_setstacksize(&(m_impl->attr), m_props.stack_size) !=
           0) {
            EPRINTF("%s:Failed setting task stack size\n", m_name);
            return false;
        }
        if(pthread_attr_setinheritsched(&(m_impl->attr),
                                        PTHREAD_EXPLICIT_SCHED) != 0) {
            EPRINTF("%s:Failed setting task schedule inheritance policy\n",
                    m_name);
            return false;
        }

        /* Call the task's initialization routine.
        */
        if(false == init()) {
            WPRINTF("%s task returned false at initialization and will not be "
                    "scheduled.\n",
                    m_name);
            return false;
        }

        return true;
    }

    bool Task::spawn_thread()
    {
        Scheduler &sched = Scheduler::get_instance();

        /* If rategroup_sync is not NULL at this point, then the task has been
         * started previously and is already on the scheduler's list.
         */
        if(NULL != m_impl->rategroup_sync) {
            m_impl->first_pass = true;
        }
        else if(m_props.period && (this != &sched)) {
            m_impl->rategroup_sync = sched.add_task(*this);
            if(NULL == m_impl->rategroup_sync) {
                return false;
            }
        }

        /* Spawn the thread.
        */
        m_thread_syncpoint.lock();
        m_thread_syncpoint.condition_cleared();
        if(pthread_create(&(m_impl->tid), &(m_impl->attr), run,
                          reinterpret_cast<void *>(this)) != 0) {
            m_thread_syncpoint.unlock();
            EPRINTF("%s: Failed to spawn thread\n", m_name);
            return false;
        }

        /* We can't get the mutex back until the thread has released it. This
         * makes sure the the thread has completed it's initilization before
         * returning and allowing additional threads to be spawned.
         */
        m_thread_syncpoint.condition_cleared();
        m_thread_syncpoint.wait();
        m_thread_syncpoint.unlock();

        return true;
    }

    bool Task::start()
    {
        /* If construction was not successful, don't bother trying to start.
        */
        if(false == m_valid) {
            EPRINTF("%s:Invalid task\n", m_name);
            return false;
        }

        /* Get the task attributes.
        */
        if(false == m_prop_symbol->entry->read(m_props)) {
            EPRINTF("%s:Failed to get task properties\n", m_name);
            return false;
        }

        /* Make sure the task priority is valid.
        */
        if((m_props.prio < (MIN_PRIO + 1)) || (m_props.prio > (MAX_PRIO - 1))) {
            EPRINTF("%s:Invalid task priority\n", m_name);
            return false;
        }

        if(false == start_prep()) {
            return false;
        }

        /* Schedule the task.
        */
        Scheduler &sched = Scheduler::get_instance();
        sched.lock();
        bool rval = spawn_thread();
        sched.unlock();

        return rval;
    }

    void Task::stop()
    {
        m_operational = false;
        terminate();
    }

    priority_t Task::get_priority() const
    {
        return m_props.prio;
    }

    units::Nanoseconds Task::get_max_runtime() const
    {
        return m_props.max_runtime;
    }

    units::Nanoseconds Task::get_last_runtime() const
    {
        return m_props.last_runtime;
    }

    bool Task::is_present_in_schedule(unsigned int s) const
    {
        return m_props.is_present_in_schedule(s);
    }

    Task::~Task()
    {
        DPRINTF("%s: Exiting\n", m_name);
        m_valid = false;
        stop();

        if(m_impl) {
            if(m_impl->tid) {
                DPRINTF("%s: Joining thread; Waiting for termination\n",
                        m_name);
                void *res;
                int rval = pthread_join(m_impl->tid, &res);
                if((0 != rval) && (PTHREAD_CANCELED != res)) {
                    EPRINTF("%s:Error joining thread\n", m_name);
                }
                m_impl->tid = 0;

                DPRINTF("%s: Thread completed\n", m_name);
                pthread_attr_destroy(&(m_impl->attr));
            }

            delete(m_impl);
            m_impl = NULL;
        }

        DPRINTF("%s: Destroyed\n", m_name);
    }

    Syncpoint Task::m_thread_syncpoint;
} // namespace
