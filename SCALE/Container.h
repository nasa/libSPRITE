#ifndef __SCALE_CONTAINER_H__
#define __SCALE_CONTAINER_H__

#include "SCALE/LuaWrapper.h"
#include "SRTX/Container.h"

namespace SCALE {

    class Container {
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
        static SRTX::Container *allocator(lua_State *L)
        {
            return new SRTX::Container(luaL_checkstring(L, 1),
                                       luaL_checkstring(L, 2));
        }

        /**
         * Ragister the contents of this class as an adapter between Lua
         * and C++ representations of SRTX::Task.
         * @param L Pointer to the Lua state.
         * @return Number of elements being passed back through the Lua
         * stack.
         */
        static int register_class(lua_State *L)
        {
            SCALE::luaW_register<SRTX::Container>(L, "Container", NULL, methods,
                                                  allocator);
            SCALE::luaW_extend<SRTX::Container, SRTX::Task>(L);
            return 0;
        }
    };

    const char Container::class_name[] = "Container";

    luaL_Reg Container::methods[] = { { NULL, NULL } };

} // namespace

#endif // __SCALE_CONTAINER_H__
