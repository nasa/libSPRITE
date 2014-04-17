#ifndef __SCALE_SCHEDULER_H__
#define __SCALE_SCHEDULER_H__

#include "SCALE/LuaWrapper.h"
#include "SRTX/Scheduler.h"

namespace SCALE
{
    class Scheduler
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
             * Because the SRTX::Scheduler is a Singleton, we cannot use the
             * default constructor to allocate a Scheduler. This function wraps
             * the Scheduler::get_instance function into a new allocator for
             * the Lua adapter.
             * @param L Pointer to the Lua state.
             * @return A pointer to the scheduler.
             */
            static SRTX::Scheduler* allocator(lua_State* L)
            {
                return &SRTX::Scheduler::get_instance();
            }

            /**
             * Because the SRTX::Scheduler is a Singleton, we cannot use the
             * default destructor. Instead, we provide our own deallocation
             * function that does nothering.
             * @param L Pointer to the Lua state.
             * @param s A pointer to the scheduler.
             */
            static void deallocator(lua_State* L, SRTX::Scheduler* s)
            {
                 // do nothing.
            }

            /**
             * Ragister the contents of this class as an adapter between Lua
             * and C++ representations of SRTX::Task.
             * @param L Pointer to the Lua state.
             * @return Number of elements being passed back through the Lua stack.
             */
            static int register_class(lua_State* L)
            {
                luaW_register<SRTX::Scheduler>(L, "Scheduler", NULL, methods,
                        allocator, deallocator);
                luaW_extend<SRTX::Scheduler, SRTX::Task>(L);
                return 0;
            }

            /**
             * Start the task.
             */
            static int start(lua_State* L)
            {
                SRTX::Scheduler* s = luaW_check<SRTX::Scheduler>(L, 1);
                lua_pushnumber(L, s->start());
                return 1;
            }

    };

    const char Scheduler::class_name[] = "Scheduler";

    luaL_Reg Scheduler::methods[] =
    {
        {"start", Scheduler::start},
        {NULL, NULL}
    };

} //namespace

#endif //__SCALE_SCHEDULER_H__
