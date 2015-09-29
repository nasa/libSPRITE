#include "SRTX/Message_ut.h"
#include "SRTX/Publication.h"
#include "SRTX/Subscription.h"
#include "SRTX/Scheduler.h"
#include "SRTX/Reference_time.h"
#include "units/Seconds.h"
#include <assert.h>
#include <unistd.h>

namespace SRTX {

    namespace {
        units::Nanoseconds sched_period(10 * units::MSEC);
        const priority_t highest_priority = 80;
        const priority_t higher_priority = highest_priority - 1;
        const priority_t lower_priority = higher_priority - 1;
        const priority_t lowest_priority = lower_priority - 1;
        const units::Nanoseconds pub_period(20 * units::MSEC);

        volatile bool pub_done;

        const unsigned int ntasks = 16;
        volatile bool done[ntasks];
    }

    Message_ut::Message_ut()
    {
    }

    Message_ut::~Message_ut()
    {
    }

    class Publisher : public Task {
      public:
        Publisher(const char *const name, const char *const pub_name,
                  int instance, int ncycles)
            : Task(name)
            , m_pub_name(pub_name)
            , m_instance(instance)
            , m_ip_msg(NULL)
            , m_cycle(ncycles)
        {
        }

        bool init()
        {
            m_ip_msg = new Publication<int>(m_pub_name, get_period());
            if((NULL == m_ip_msg) || (false == m_ip_msg->is_valid())) {
                return false;
            }

            /* Seed the initial publication value.
             */
            m_ip_msg->content = 0;
            return m_ip_msg->put();
        }

        bool execute()
        {
            DPRINTF("Running %s\n", m_name);

            ++m_ip_msg->content;
            if(false == m_ip_msg->put()) {
                EPRINTF("%s failed put()\n", m_name);
                done[m_instance] = true;
                return false;
            }

            /* Have we completed the requested number of cycles?
             */
            if((--m_cycle) <= 0) {
                done[m_instance] = true;
                return false;
            }

            DPRINTF("Finished running %s\n", m_name);

            return true;
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Publisher(const Publisher &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Publisher &operator=(const Publisher &);

        const char *const m_pub_name;
        int m_instance;
        Publication<int> *m_ip_msg;
        int m_cycle;
    };

    class Aperiodic_publisher : public Task {
      public:
        Aperiodic_publisher(const char *const name, const char *const pub_name,
                            int instance, int ncycles)
            : Task(name)
            , m_pub_name(pub_name)
            , m_instance(instance)
            , m_ip_msg(NULL)
            , m_cycle(ncycles)
        {
        }

        bool init()
        {
            m_ip_msg = new Publication<int>(m_pub_name, get_period());
            if((NULL == m_ip_msg) || (false == m_ip_msg->is_valid())) {
                return false;
            }

            /* Seed the initial publication value.
             */
            m_ip_msg->content = 0;
            return m_ip_msg->put();
        }

        bool execute()
        {
            DPRINTF("Running %s\n", m_name);

            sleep(units::Nanoseconds(30 * units::MSEC));

            ++m_ip_msg->content;
            if(false == m_ip_msg->put()) {
                EPRINTF("%s failed put()\n", m_name);
                done[m_instance] = true;
                return false;
            }

            /* Have we completed the requested number of cycles?
             */
            if(--m_cycle <= 0) {
                done[m_instance] = true;
                return false;
            }

            DPRINTF("Finished running %s\n", m_name);

            return true;
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Aperiodic_publisher(const Aperiodic_publisher &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Aperiodic_publisher &operator=(const Aperiodic_publisher &);

        const char *const m_pub_name;
        int m_instance;
        Publication<int> *m_ip_msg;
        int m_cycle;
    };

    class Subscriber : public Task {
      public:
        Subscriber(const char *const name, const char *const sub_name,
                   int instance, int ncycles)
            : Task(name)
            , m_is_msg(NULL)
            , m_sub_name(sub_name)
            , m_instance(instance)
            , m_cycle(ncycles)
            , m_ex(0)
        {
        }

        bool init()
        {
            m_is_msg = new Subscription<int>(m_sub_name, get_period());
            if((NULL == m_is_msg) || (false == m_is_msg->is_valid())) {
                return false;
            }

            return true;
        }

        bool execute()
        {
            DPRINTF("Running %s\n", m_name);

            if(false == m_is_msg->get()) {
                EPRINTF("%s failed get()\n", m_name);
                done[m_instance] = true;
                return false;
            }

            if(false == m_is_msg->was_updated()) {
                EPRINTF("%s did not get an updated message\n", m_name);
                done[m_instance] = true;
                return false;
            }

            /* Determine the expected count value.
             */
            if(++m_ex != m_is_msg->content) {
                EPRINTF("%s expected %d, received %d\n", m_name, m_ex,
                        m_is_msg->content);
                done[m_instance] = true;
                return false;
            }

            /* Test the message latency. It should be less than the
             * publisher's period.
             */
            units::Nanoseconds now;
            if(false == get_time(now)) {
                EPRINTF("%s failed get_time()\n", m_name);
                done[m_instance] = true;
                return false;
            }
            units::Nanoseconds latency = now - m_is_msg->get_publication_time();
            if(latency >= pub_period) {
                EPRINTF("%s latency >= pub_period\n", m_name);
                done[m_instance] = true;
                return false;
            }

            /* Have we completed the requested number of cycles?
             */
            if(--m_cycle <= 0) {
                done[m_instance] = true;
                return false;
            }

            DPRINTF("Finished running %s\n", m_name);

            return true;
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Subscriber(const Subscriber &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Subscriber &operator=(const Subscriber &);

        Subscription<int> *m_is_msg;
        const char *const m_sub_name;
        int m_instance;
        int m_cycle;
        int m_ex;
    };

    class Aperiodic_subscriber : public Task {
      public:
        Aperiodic_subscriber(const char *const name, const char *const sub_name,
                             int instance, int ncycles)
            : Task(name)
            , m_is_msg(NULL)
            , m_sub_name(sub_name)
            , m_instance(instance)
            , m_cycle(ncycles)
            , m_run_count(0)
        {
        }

        bool init()
        {
            m_is_msg = new Subscription<int>(m_sub_name, get_period());
            if((NULL == m_is_msg) || (false == m_is_msg->is_valid())) {
                return false;
            }

            return true;
        }

        bool execute()
        {
            DPRINTF("Running %s\n", m_name);

            DPRINTF("%s, waiting for message\n", m_name);
            if(false == m_is_msg->get_blocking()) {
                EPRINTF("%s failed get_blocking()\n", m_name);
                /* We did not get the message. Terminate this frame, but let
                 * the task get rescheduled so it can try blocking on the
                 * message again.
                 */
                return true;
            }
            DPRINTF("%s, got message\n", m_name);

            if(m_is_msg->was_updated()) {
                ++m_run_count;
            }

            /* Have we completed the requested number of cycles?
             */
            if(m_is_msg->content >= m_cycle) {
                /* We're done. Mark the task done and end execution.
                 */
                done[m_instance] = true;
                return false;
            }

            DPRINTF("Finished running %s\n", m_name);

            return true;
        }

        void terminate()
        {
            DPRINTF("Terminating aperiodic subscriber %d\n", m_instance);
            if(m_is_msg) {
                m_is_msg->abort_get();
            }
        }

        int get_run_count() const
        {
            DPRINTF("Aperiodic subsciber %d run count = %d\n", m_instance,
                    m_run_count);
            return m_run_count;
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Aperiodic_subscriber(const Aperiodic_subscriber &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Aperiodic_subscriber &operator=(const Aperiodic_subscriber &);

        Subscription<int> *m_is_msg;
        const char *const m_sub_name;
        int m_instance;
        int m_cycle;
        int m_run_count;
    };

    class Slow_subscriber : public Task {
      public:
        Slow_subscriber(const char *const name, const char *const sub_name,
                        int instance, int ncycles)
            : Task(name)
            , m_is_msg(NULL)
            , m_sub_name(sub_name)
            , m_instance(instance)
            , m_cycle(ncycles)
            , m_first_pass(true)
            , m_ex(0)
        {
        }

        bool init()
        {
            m_is_msg = new Subscription<int>(m_sub_name, get_period());
            if((NULL == m_is_msg) || (false == m_is_msg->is_valid())) {
                return false;
            }

            return true;
        }

        bool execute()
        {
            DPRINTF("Running %s\n", m_name);

            if(false == m_is_msg->get()) {
                EPRINTF("%s failed get()\n", m_name);
                return false;
            }
            if(false == m_is_msg->was_updated()) {
                EPRINTF("%s received message was not updated\n", m_name);
            }

            if(m_first_pass) {
                m_ex = m_is_msg->content;
                m_first_pass = false;
            } else {
                /* Determine the expected count value.
                 */
                m_ex += 2;
                if(m_ex != m_is_msg->content) {
                    EPRINTF("%s expected %d but received %d\n", m_name, m_ex,
                            m_is_msg->content);
                    done[m_instance] = true;
                    return false;
                }
            }

            /* Test the message latency.
             */
            units::Nanoseconds now;
            if(false == get_time(now)) {
                EPRINTF("%s failed get_time()\n", m_name);
                return false;
            }
            units::Nanoseconds latency = now - m_is_msg->get_publication_time();
            if(latency >= 2 * get_period()) {
                EPRINTF("%s latency >= 2 * pub_period\n", m_name);
                return false;
            }

            /* Have we completed the requested number of cycles?
             */
            if(--m_cycle <= 0) {
                done[m_instance] = true;
                return false;
            }

            DPRINTF("Finished running %s\n", m_name);

            return true;
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Slow_subscriber(const Slow_subscriber &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Slow_subscriber &operator=(const Slow_subscriber &);

        Subscription<int> *m_is_msg;
        const char *const m_sub_name;
        int m_instance;
        int m_cycle;
        bool m_first_pass;
        int m_ex;
    };

    class Fast_subscriber : public Task {
      public:
        Fast_subscriber(const char *const name, const char *const sub_name,
                        int instance, int ncycles)
            : Task(name)
            , m_is_msg(NULL)
            , m_sub_name(sub_name)
            , m_instance(instance)
            , m_cycle(ncycles)
            , m_first_pass(true)
            , m_ex(0)
        {
        }

        bool init()
        {
            m_is_msg = new Subscription<int>(m_sub_name, get_period());
            if((NULL == m_is_msg) || (false == m_is_msg->is_valid())) {
                return false;
            }

            return true;
        }

        bool execute()
        {
            DPRINTF("Running %s\n", m_name);

            units::Nanoseconds rtime = get_reference_time();
            if(m_first_pass) {
                if(0 == (rtime % pub_period)) {
                    m_is_msg->get();
                    m_ex = m_is_msg->content;
                    m_first_pass = false;
                }

                return true;
            } else {
                if(false == m_is_msg->get()) {
                    EPRINTF("%s failed get()\n", m_name);
                    done[m_instance] = true;
                    return false;
                }

                /* Determine the expected count value.
                 */
                units::Nanoseconds rtime = get_reference_time();
                if(0 == (rtime % pub_period)) {
                    ++m_ex;
                }

                if(m_ex != m_is_msg->content) {
                    EPRINTF("%s expected %d but received %d\n", m_name, m_ex,
                            m_is_msg->content);
                    done[m_instance] = true;
                    return false;
                }
            }

            /* Test the message latency.
             */
            units::Nanoseconds now;
            if(false == get_time(now)) {
                EPRINTF("%s failed get_time()\n", m_name);
                done[m_instance] = true;
                return false;
            }
            units::Nanoseconds latency = now - m_is_msg->get_publication_time();
            if(latency >= 2 * pub_period) {
                EPRINTF("%s latency >= 2 * pub_period\n", m_name);
                done[m_instance] = true;
                return false;
            }

            /* Have we completed the requested number of cycles?
             */
            if(--m_cycle <= 0) {
                done[m_instance] = true;
                return false;
            }

            DPRINTF("Finished running %s\n", m_name);

            return true;
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Fast_subscriber(const Fast_subscriber &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Fast_subscriber &operator=(const Fast_subscriber &);

        Subscription<int> *m_is_msg;
        const char *const m_sub_name;
        int m_instance;
        int m_cycle;
        bool m_first_pass;
        int m_ex;
    };

    void Message_ut::setUp()
    {
        Scheduler &sched = Scheduler::get_instance();
        Task_db::value_t task_props;

        task_props.period = sched_period;
        if(false == sched.set_properties(task_props)) {
            EPRINTF("Error setting scheduler properties\n");
            return;
        }

        if(false == sched.start()) {
            EPRINTF("Error starting the scheduler\n");
            return;
        }
    }

    void Message_ut::tearDown()
    {
        DPRINTF("Begin tearDown\n");

        Scheduler &sched = Scheduler::get_instance();
        sched.stop();

        DPRINTF("tearDown complete\n");
    }

    void Message_ut::test_Message()
    {
        IPRINTF("\nStart %s\n", __func__);
        Publication<int> ip_msg("i_msg");
        Subscription<int> is_msg("i_msg");

        CPPUNIT_ASSERT_EQUAL(true, ip_msg.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, is_msg.is_valid());

        ip_msg.content = 3;

        /* No put yet, so the get() should fail and the message should be
         * marked as not current.
         */
        CPPUNIT_ASSERT_EQUAL(false, is_msg.get());
        CPPUNIT_ASSERT(-1 == is_msg.get_publication_time());

        /* Put the message from the publication then get it from the
         * subscription and test the value.
         */
        CPPUNIT_ASSERT_EQUAL(true, ip_msg.put());
        CPPUNIT_ASSERT_EQUAL(true, is_msg.get());
        CPPUNIT_ASSERT_EQUAL(3, is_msg.content);

        /* Test that the message latency tests work.
         */
        Subscription<int> isl_msg("i_msg");
        CPPUNIT_ASSERT_EQUAL(true, isl_msg.get());
        CPPUNIT_ASSERT_EQUAL(3, isl_msg.content);

        sleep(units::SEC);

        /* The message latency test should fail here.
         */
        CPPUNIT_ASSERT_EQUAL(true, isl_msg.get());
        CPPUNIT_ASSERT_EQUAL(3, isl_msg.content);
        IPRINTF("Complete %s\n", __func__);
    }

    void Message_ut::test_pub_sub()
    {
        IPRINTF("\nStart %s\n", __func__);
        const int ncycles = 6;

        const char *const msg1_name = "msg1_";
        const char *const msg2_name = "msg2_";
        const char *const msg3_name = "msg3_";
        unsigned int instance = 0;

        /* Construct the publishers.
         */
        Task_properties props;
        props.period = pub_period;
        props.prio = higher_priority;
        Publisher pub1("Publisher 1", msg1_name, instance++, ncycles * 10); // 0
        CPPUNIT_ASSERT_EQUAL(true, pub1.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, pub1.set_properties(props));

        Publisher pub2("Publisher 2", msg2_name, instance++, ncycles * 10); // 1
        CPPUNIT_ASSERT_EQUAL(true, pub2.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, pub2.set_properties(props));

        props.period = units::Nanoseconds(0);
        Aperiodic_publisher pub3("Aperiodic_publisher", msg3_name, instance++,
                                 ncycles * 10); // 2
        CPPUNIT_ASSERT_EQUAL(true, pub3.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, pub3.set_properties(props));

        /* Construct the subscribers.
         */
        props.prio = lower_priority;
        props.period = pub_period;
        Subscriber sub1("Subscriber 1", msg1_name, instance++, ncycles); // 3
        CPPUNIT_ASSERT_EQUAL(true, sub1.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub1.set_properties(props));

        Subscriber sub2("Subscriber 2", msg1_name, instance++, ncycles); // 4
        CPPUNIT_ASSERT_EQUAL(true, sub2.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub2.set_properties(props));

        Subscriber sub7("Subscriber 3", msg2_name, instance++, ncycles); // 5
        CPPUNIT_ASSERT_EQUAL(true, sub7.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub7.set_properties(props));

        props.prio = lowest_priority;
        props.period = units::Nanoseconds(pub_period * 2);
        Slow_subscriber sub3("Slow_subscriber 1", msg1_name, instance++,
                             ncycles / 2); // 6
        CPPUNIT_ASSERT_EQUAL(true, sub3.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub3.set_properties(props));

        Slow_subscriber sub5("Slow_subscriber 2", msg1_name, instance++,
                             ncycles / 2); // 7
        CPPUNIT_ASSERT_EQUAL(true, sub5.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub5.set_properties(props));
        Slow_subscriber sub8("Slow_subscriber 3", msg2_name, instance++,
                             ncycles / 2); // 8
        CPPUNIT_ASSERT_EQUAL(true, sub8.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub8.set_properties(props));

        props.prio = highest_priority;
        props.period = units::Nanoseconds(pub_period / 2);
        Fast_subscriber sub4("Fast_subscriber 1", msg1_name, instance++,
                             ncycles * 2); // 9
        CPPUNIT_ASSERT_EQUAL(true, sub4.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub4.set_properties(props));

        Fast_subscriber sub6("Fast_subscriber 2", msg1_name, instance++,
                             ncycles * 2); // 10
        CPPUNIT_ASSERT_EQUAL(true, sub6.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub6.set_properties(props));

        Fast_subscriber sub9("Fast_subscriber 3", msg2_name, instance++,
                             ncycles * 2); // 11
        CPPUNIT_ASSERT_EQUAL(true, sub9.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub9.set_properties(props));

        props.prio = lowest_priority;
        props.period = units::Nanoseconds(0);
        Aperiodic_subscriber sub10("Aperiodic_subscriber 1", msg1_name,
                                   instance++, ncycles); // 12
        CPPUNIT_ASSERT_EQUAL(true, sub10.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub10.set_properties(props));

        Aperiodic_subscriber sub11("Aperiodic_subscriber 2", msg1_name,
                                   instance++, ncycles); // 13
        CPPUNIT_ASSERT_EQUAL(true, sub11.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub11.set_properties(props));

        Aperiodic_subscriber sub12("Aperiodic_subscriber 3", msg3_name,
                                   instance++, ncycles); // 14
        CPPUNIT_ASSERT_EQUAL(true, sub12.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub12.set_properties(props));

        Aperiodic_subscriber sub13("Aperiodic_subscriber 4", msg3_name,
                                   instance++, ncycles); // 15
        CPPUNIT_ASSERT_EQUAL(true, sub13.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub13.set_properties(props));

        /* If the following assertion is not true, the test will hang or may
         * not wait for all tasks to complete.
         */
        assert(instance == ntasks);

        for(unsigned int i = 0; i < ntasks; ++i) {
            done[i] = false;
        }
        CPPUNIT_ASSERT_EQUAL(true, sub12.start());
        CPPUNIT_ASSERT_EQUAL(true, sub11.start());
        CPPUNIT_ASSERT_EQUAL(true, sub1.start());
        CPPUNIT_ASSERT_EQUAL(true, sub5.start());
        CPPUNIT_ASSERT_EQUAL(true, pub1.start());
        CPPUNIT_ASSERT_EQUAL(true, pub2.start());
        CPPUNIT_ASSERT_EQUAL(true, pub3.start());
        CPPUNIT_ASSERT_EQUAL(true, sub2.start());
        CPPUNIT_ASSERT_EQUAL(true, sub3.start());
        CPPUNIT_ASSERT_EQUAL(true, sub4.start());
        CPPUNIT_ASSERT_EQUAL(true, sub6.start());
        CPPUNIT_ASSERT_EQUAL(true, sub7.start());
        CPPUNIT_ASSERT_EQUAL(true, sub8.start());
        CPPUNIT_ASSERT_EQUAL(true, sub9.start());
        CPPUNIT_ASSERT_EQUAL(true, sub10.start());
        CPPUNIT_ASSERT_EQUAL(true, sub13.start());

        /* Now that the properties are set, start the task.
         */
        Subscription<int> msg(msg1_name, pub_period);
        // Get the initial value and syncronized with the publisher.
        CPPUNIT_ASSERT_EQUAL(true, msg.get_blocking());
        int ex = msg.content;
        units::Nanoseconds now;
        // Should timeout and therefore, the value should not be updated.
        get_time(now);
        CPPUNIT_ASSERT_EQUAL(true,
                             msg.get_blocking(now + units::Nanoseconds(100)));
        CPPUNIT_ASSERT_EQUAL(false, msg.was_updated());
        CPPUNIT_ASSERT_EQUAL(ex, msg.content);
        // Should be updated before the timeout.
        get_time(now);
        CPPUNIT_ASSERT_EQUAL(true, msg.get_blocking(now + pub_period));
        CPPUNIT_ASSERT_EQUAL(true, msg.was_updated());
        CPPUNIT_ASSERT_EQUAL(++ex, msg.content);

        /* Test subcription timeouts here in the main loop while the tasks
         * are running.
         */
        bool test_done;
        do {
            test_done = true;
            for(unsigned int i = 0; i < ntasks; ++i) {
                test_done = test_done && done[i];
            }
        } while(!test_done);
        IPRINTF("Completed %s\n", __func__);
    }

    /**
     * This test was added after finding an error (Mantis issue #1244) where an
     * aperiodic task that should be blocked on a message (using get_blocking)
     * gets released to run if a publisher exists, even if the publisher did
     * not do a put(). This test exists to prove absence of this error in
     * future releases.
     * We also found a deadlock condition where the aperiodic task get hung
     * blocked waiting to get a subscription (Mantis issue #1245) that is
     * tested for by this test case.
     */
    void Message_ut::test_async()
    {
        IPRINTF("\nStarted %s\n", __func__);
        const char *const msg1_name = "amsg_";

        IPRINTF("\nTesting asyncronous subscribers\n");

        Task_properties props;
        props.period = pub_period;
        props.prio = lower_priority;
        Publisher pub1("test_async Publisher 1", msg1_name, 0, 100);
        CPPUNIT_ASSERT_EQUAL(true, pub1.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, pub1.set_properties(props));

        props.prio = higher_priority;
        props.period = units::Nanoseconds(0);
        Aperiodic_subscriber sub1("Asub 1", msg1_name, 0, 10);
        CPPUNIT_ASSERT_EQUAL(true, sub1.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub1.set_properties(props));

        Aperiodic_subscriber sub2("Asub 2", msg1_name, 1, 10);
        CPPUNIT_ASSERT_EQUAL(true, sub2.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, sub2.set_properties(props));

        IPRINTF("We expect the Asub tasks to report an error here\n");
        CPPUNIT_ASSERT_EQUAL(true, sub1.start());
        CPPUNIT_ASSERT_EQUAL(true, pub1.start());
        CPPUNIT_ASSERT_EQUAL(true, sub2.start());

        sleep(units::SEC);

        sub1.stop();
        pub1.stop();
        sub2.stop();

        /* Becaues the subscribers run aperiodically and the second is started
         * after the publisher, there will be variations in the number of times
         * they run, but it should be between 0 and 100.
         */
        int run_count = sub1.get_run_count();
        CPPUNIT_ASSERT(run_count > 0);
        CPPUNIT_ASSERT(run_count < 101);
        run_count = sub2.get_run_count();
        CPPUNIT_ASSERT(run_count > 0);
        CPPUNIT_ASSERT(run_count < 12);

        IPRINTF("Completed %s\n", __func__);
    }

} // namespace
