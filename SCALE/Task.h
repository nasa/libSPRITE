#ifndef __SCALE_TASK_H__
#define __SCALE_TASK_H__

#include "SCALE/LuaWrapper.h"
#include "SRTX/Task.h"

namespace SCALE {
    class Task {
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
         * Ragister the contents of this class as an adapter between Lua
         * and C++ representations of SRTX::Task.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int register_class(lua_State *L)
        {
            luaW_register<SRTX::Task>(L, "Task", NULL, methods, NULL);
            return 0;
        }

        /**
         * Task initialization routine.
         * This method may be overriden by a derived task class. It is
         * invoked by start().
         * @param L Pointer to the Lua state.
         * @return true on success or false on failure.
         */
        static bool init(lua_State *L)
        {
            SRTX::Task *t = luaW_check<SRTX::Task>(L, 1);
            return t->init();
        }

        /**
         * This is the function that a task runs when invoked by the
         * scheduler.
         * @param L Pointer to the Lua state.
         * @return true on success or false on failure.
         */
        static bool execute(lua_State *L)
        {
            SRTX::Task *t = luaW_check<SRTX::Task>(L, 1);
            return t->execute();
        }

        /**
         * Task termination.
         * This method may be overriden by a derived task class. It is
         * invoked by the when stop() is called.
         * @param L Pointer to the Lua state.
         */
        static void terminate(lua_State *L)
        {
            SRTX::Task *t = luaW_check<SRTX::Task>(L, 1);
            t->terminate();
        }

        /**
         * Set the scheduler properties.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int set_properties(lua_State *L)
        {
            SRTX::Task *t = luaW_check<SRTX::Task>(L, 1);
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 2);
            lua_pushnumber(L, (t->set_properties(*p)) ? 1 : -1);
            return 1;
        }

        /**
         * Start the task.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int start(lua_State *L)
        {
            SRTX::Task *t = luaW_check<SRTX::Task>(L, 1);
            lua_pushnumber(L, (t->start()) ? 1 : -1);
            return 1;
        }

        /**
         * Stop the task.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int stop(lua_State *L)
        {
            SRTX::Task *t = luaW_check<SRTX::Task>(L, 1);
            t->stop();
            return 0;
        }

        /**
         * Test if the task is valid.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int is_valid(lua_State *L)
        {
            SRTX::Task *t = luaW_check<SRTX::Task>(L, 1);
            lua_pushnumber(L, (t->is_valid()) ? 1 : -1);
            return 1;
        }

        /**
         * Test if the task is operational.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int is_operational(lua_State *L)
        {
            SRTX::Task *t = luaW_check<SRTX::Task>(L, 1);
            lua_pushnumber(L, (t->is_operational()) ? 1 : -1);
            return 1;
        }
    };

    const char Task::class_name[] = "Task";

    luaL_Reg Task::methods[] = { { "start", Task::start },
                                 { "stop", Task::stop },
                                 { "set_properties", Task::set_properties },
                                 { "is_valid", Task::is_valid },
                                 { "is_operational", Task::is_operational },
                                 { NULL, NULL } };

} // namespace

#endif //__SCALE_TASK_H__
