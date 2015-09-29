
#include "SCALE/Scale_if.h"
#include "SCALE/Scale_if_ut.h"
#include "SCALE/Test_task_ext.h"
#include "SCALE/Nest_lua.h"

namespace SCALE {

    void Scale_if_ut::setUp()
    {
    }

    void Scale_if_ut::tearDown()
    {
    }

    void Scale_if_ut::test_task_properties()
    {
        Scale_if &scale = Scale_if::get_instance();

        CPPUNIT_ASSERT(scale.run_script("Task_properties_ut.lua"));
    }

    void Scale_if_ut::test_scheduler()
    {
        Scale_if &scale = Scale_if::get_instance();

        /* Register my test task with with the Lua executive.
         */
        Test_task_ext::register_class(scale.state());
        Nest_lua::register_class(scale.state());

        CPPUNIT_ASSERT(scale.run_script("Scheduler_ut.lua"));
    }

    void Scale_if_ut::test_nesting()
    {
        Scale_if &scale = Scale_if::get_instance();

        /* Register my test task with with the Lua executive.
         */
        Test_task_ext::register_class(scale.state());

        CPPUNIT_ASSERT(scale.run_script("Nest_ut.lua"));
    }
} // namespace
