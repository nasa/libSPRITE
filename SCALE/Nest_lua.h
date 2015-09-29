
#ifndef __SCALE_NEST_LUA_H__
#define __SCALE_NEST_LUA_H__

#include "SCALE/LuaWrapper.h"
#include "SCALE/Nest.h"

namespace SCALE {

    class Nest_lua {
      public:
        /**
         * The name regsitered with Lua to describe the class.
         */
        static const char class_name[];

        /**
         * The set of methods being exposed to Lua through the adapter
         * class.
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
        static Nest *allocator(lua_State *L)
        {
            return new Nest(luaL_checkstring(L, 1));
        }

        /**
         * Give the task a script to run.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua
         * stack.
         */
        static int register_script(lua_State *L)
        {
            Nest *n = luaW_check<Nest>(L, 1);
            n->register_script(const_cast<char *>(luaL_checkstring(L, 2)));
            return 0;
        }

        /**
         * Register the contents of this class as an adapter between Lua
         * and C++ representations of SRTX::Task.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua
         * stack.
         */
        static int register_class(lua_State *L)
        {
            luaW_register<Nest>(L, "Nest", NULL, methods, allocator);
            luaW_extend<Nest, SRTX::Task>(L);
            return 0;
        }
    };

    const char Nest_lua::class_name[] = "Nest";

    luaL_Reg Nest_lua::methods[] = {
        { "register_script", Nest_lua::register_script }, { NULL, NULL }
    };

} // namespace

#endif // __SCALE_NEST_LUA_H__
