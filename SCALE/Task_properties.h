#ifndef __SCALE_TASK_PROPERTIES_H__
#define __SCALE_TASK_PROPERTIES_H__

#include "SCALE/LuaWrapper.h"
#include "SRTX/Task_properties.h"
#include "units/Seconds.h"

namespace SCALE {
    class Task_properties {
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
         * and C++ representations of SRTX::Task_properties.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int register_class(lua_State *L)
        {
            luaW_register<SRTX::Task_properties>(L, "Task_properties", NULL,
                                                 methods);
            return 0;
        }

        /**
         * Initialize the task properties from a variable length list of
         * arguments.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int init(lua_State *L)
        {
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 1);
            switch(lua_gettop(L) - 1) {
            case 4:
                p->stack_size =
                    static_cast<unsigned int>(luaL_checknumber(L, 5));
            // Intentional fallthrough
            case 3:
                p->schedule_presence = static_cast<SRTX::schedule_presence_t>(
                    luaL_checknumber(L, 4));
            // Intentional fallthrough
            case 2:
                p->period =
                    units::Nanoseconds(units::Seconds(luaL_checknumber(L, 3)));
            // Intentional fallthrough
            case 1:
                p->prio = static_cast<SRTX::priority_t>(luaL_checknumber(L, 2));
                break;
            default:
                // Do nothing
                break;
            };

            return 0;
        }

        /**
         * Return the maximum available task user priority.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int MAX_USER_TASK_PRIO(lua_State *L)
        {
            lua_pushnumber(L, SRTX::MAX_PRIO - 1);
            return 1;
        }

        /**
         * Return the minimum available task user priority.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int MIN_USER_TASK_PRIO(lua_State *L)
        {
            lua_pushnumber(L, SRTX::MIN_PRIO + 1);
            return 1;
        }

        /**
         * Get the task priority from within Lua.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int get_prio(lua_State *L)
        {
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 1);
            lua_pushnumber(L, p->prio);
            return 1;
        }

        /**
         * Set the task priority from within Lua.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int set_prio(lua_State *L)
        {
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 1);
            p->prio = static_cast<SRTX::priority_t>(luaL_checknumber(L, 2));
            return 0;
        }

        /**
         * Get the task period (in units of seconds) from within Lua.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int get_period(lua_State *L)
        {
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 1);
            lua_pushnumber(L, units::Seconds(p->period));
            return 1;
        }

        /**
         * Set the task period (provided in seconds) from within Lua.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int set_period(lua_State *L)
        {
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 1);
            p->period =
                units::Nanoseconds(units::Seconds(luaL_checknumber(L, 2)));
            return 0;
        }

        /**
         * Get the schedule presence bitmask for the task from within Lua.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int get_schedule_presence(lua_State *L)
        {
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 1);
            lua_pushnumber(L, p->schedule_presence);
            return 1;
        }

        /**
         * Set the task schedule presence bitmask from within Lua.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int set_schedule_presence(lua_State *L)
        {
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 1);
            p->schedule_presence =
                static_cast<SRTX::schedule_presence_t>(luaL_checknumber(L, 2));
            return 0;
        }

        /**
         * Get the stack size from within Lua.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int get_stack_size(lua_State *L)
        {
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 1);
            lua_pushnumber(L, p->stack_size);
            return 1;
        }

        /**
         * Set the set stack size from within Lua.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua stack.
         */
        static int set_stack_size(lua_State *L)
        {
            SRTX::Task_properties *p = luaW_check<SRTX::Task_properties>(L, 1);
            p->stack_size = static_cast<unsigned int>(luaL_checknumber(L, 2));
            return 0;
        }
    };

    const char Task_properties::class_name[] = "Task_properties";

    luaL_Reg Task_properties::methods[] = {
        { "init", Task_properties::init },
        { "MAX_USER_TASK_PRIO", Task_properties::MAX_USER_TASK_PRIO },
        { "MIN_USER_TASK_PRIO", Task_properties::MIN_USER_TASK_PRIO },
        { "get_prio", Task_properties::get_prio },
        { "set_prio", Task_properties::set_prio },
        { "get_period", Task_properties::get_period },
        { "set_period", Task_properties::set_period },
        { "get_schedule_presence", Task_properties::get_schedule_presence },
        { "set_schedule_presence", Task_properties::set_schedule_presence },
        { "get_stack_size", Task_properties::get_stack_size },
        { "set_stack_size", Task_properties::set_stack_size },
        { NULL, NULL }
    };

} // namespace

#endif //__SCALE_TASK_PROPERTIES_H__
