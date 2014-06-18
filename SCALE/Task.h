#ifndef __SCALE_TASK_H__
#define __SCALE_TASK_H__

#include "SCALE/LuaWrapper.h"
#include "SRTX/Task.h"

namespace SCALE
{
    class Task
    {
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
            static int register_class(lua_State* L)
            {
                luaW_register<SRTX::Task>(L, "Task", NULL, methods, NULL);
                return 0;
            }

            /**
             * Task initialization routine.
             * This method may be overriden by a derived task class. It is
             * invoked by start().
             */
            static bool init(lua_State* L)
            {
                SRTX::Task* t = luaW_check<SRTX::Task>(L, 1);
                return t->init();
            }

            /**
             * This is the function that a task runs when invoked by the
             * scheduler.
             * @return true on success or false on failure.
             */
            static bool execute(lua_State* L)
            {
                SRTX::Task* t = luaW_check<SRTX::Task>(L, 1);
                return t->execute();
            }

            /**
             * Task termination.
             * This method may be overriden by a derived task class. It is
             * invoked by the when stop() is called.
             */
            static void terminate(lua_State* L)
            {
                SRTX::Task* t = luaW_check<SRTX::Task>(L, 1);
                t->terminate();
            }

            /**
             * Set the scheduler properties.
             * @param props Task properties for the scheduler.
             */
            static int set_properties(lua_State* L)
            {
                SRTX::Task* t = luaW_check<SRTX::Task>(L, 1);
                SRTX::Task_properties* p = luaW_check<SRTX::Task_properties>(L, 2);
                lua_pushnumber(L, (t->set_properties(*p)) ? 0 : -1);
                return 1;
            }

            /**
             * Start the task.
             */
            static int start(lua_State* L)
            {
                SRTX::Task* t = luaW_check<SRTX::Task>(L, 1);
                lua_pushnumber(L, t->start());
                return 1;
            }

            /**
             * Stop the task.
             */
            static int stop(lua_State* L)
            {
                SRTX::Task* t = luaW_check<SRTX::Task>(L, 1);
                t->stop();
                return 0;
            }

    };

    const char Task::class_name[] = "Task";

    luaL_Reg Task::methods[] =
    {
        {"start", Task::start},
        {"stop", Task::stop},
        {"set_properties", Task::set_properties},
        {NULL, NULL}
    };

} //namespace

#endif //__SCALE_TASK_H__
