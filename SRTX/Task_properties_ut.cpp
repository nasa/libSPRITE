#include "Task_properties_ut.h"
#include "Task_properties.h"

namespace SRTX {

    void Task_properties_ut::setUp()
    {
    }

    void Task_properties_ut::tearDown()
    {
    }

    void Task_properties_ut::test_get_priority()
    {
        Task_properties sp;

        CPPUNIT_ASSERT(0 == sp.prio);
    }

    void Task_properties_ut::test_get_period()
    {
        Task_properties sp;

        CPPUNIT_ASSERT(0 == sp.period);
    }

    void Task_properties_ut::test_get_schedule_presence()
    {
        Task_properties sp;

        /* By default, the task is in all of the schedules.
         */
        for(unsigned int i = 0; i < sizeof(schedule_presence_t) * 8; ++i) {
            CPPUNIT_ASSERT(true == sp.is_present_in_schedule(i));
        }

        /* If we try a schedule greater than the number of allowable schedules
         * we should get a false return value.
         */
        CPPUNIT_ASSERT(false == sp.is_present_in_schedule(
                                    sizeof(schedule_presence_t) * 8 + 1));

        /* Nothing changed, just explicitly set the schedule presence
         * mask to be zeroes.
         * ex: HEX:0x0...0 -> BIN:0000...0000
         */
        sp.schedule_presence = 0x00000000;

        for(int i = 0; i < 32; ++i) {
            CPPUNIT_ASSERT_EQUAL(false, sp.is_present_in_schedule(i));
        }

        /* Explicitly set schedule presence to be true for all schedules.
         * ex: HEX:F...F -> BIN:1111...1111
         */
        sp.schedule_presence = 0xFFFFFFFF;

        for(int i = 0; i < 32; ++i) {
            CPPUNIT_ASSERT_EQUAL(true, sp.is_present_in_schedule(i));
        }

        /* Alternate the schedule presence with LSB as zero
         * ex: HEX:0xA...A -> BIN:1010...1010
         */
        sp.schedule_presence = 0xAAAAAAAA;

        for(int i = 0; i < 32; ++i) {
            if(0 == i % 2) {
                CPPUNIT_ASSERT_EQUAL(false, sp.is_present_in_schedule(i));
            } else {
                CPPUNIT_ASSERT_EQUAL(true, sp.is_present_in_schedule(i));
            }
        }

        /* Alternate the schedule presence with LSB as one
         * ex: HEX:0x5...5 -> BIN:0101...0101
         */
        sp.schedule_presence = 0x55555555;

        for(int i = 0; i < 32; ++i) {
            if(0 == i % 2) {
                CPPUNIT_ASSERT_EQUAL(true, sp.is_present_in_schedule(i));
            } else {
                CPPUNIT_ASSERT_EQUAL(false, sp.is_present_in_schedule(i));
            }
        }
    }

} // namespace
