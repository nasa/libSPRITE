#ifndef __SCALE_TEST_TASK_EXT_H__
#define __SCALE_TEST_TASK_EXT_H__

#include "SCALE/LuaWrapper.h"
#include "SCALE/Test_task.h"

namespace SCALE {
    class Test_task_ext {
      public:
        /**
         * The name regsitered with Lua to describe the class.
         */
        static const char class_name[];

        /**
         * The set of methods being exposed to Lua through the adapter class.
         */
        static luaL_Reg methods[];

        /**
         * Because the SRTX::Scheduler is a Singleton, we cannot use the
         * default constructor to allocate a Scheduler. This function wraps
         * the Scheduler::get_instance function into a new allocator for
         * the Lua adapter.
         * @param L Pointer to the Lua state.
         * @return A pointer to the Task.
         */
        static Test_task *allocator(lua_State *L)
        {
            return new Test_task(luaL_checkstring(L, 1));
        }

        /**
         * Ragister the contents of this class as an adapter between Lua
         * and C++ representations of SRTX::Task.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int register_class(lua_State *L)
        {
            luaW_register<Test_task>(L, "Test_task", NULL, methods, allocator);
            luaW_extend<Test_task, SRTX::Task>(L);
            return 0;
        }
    };

    const char Test_task_ext::class_name[] = "Test_task";

    luaL_Reg Test_task_ext::methods[] = { { NULL, NULL } };

} // namespace

#endif //__SCALE_TEST_TASK_EXT_H__
