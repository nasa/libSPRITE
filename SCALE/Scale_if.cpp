#include <stdlib.h>
#include "SCALE/Scale_if.h"
#include "SCALE/Scheduler.h"
#include "SCALE/Task_properties.h"
#include "SCALE/Task.h"

namespace SCALE {

    static bool dofile(lua_State *L, const char *name)
    {
        if(luaL_loadfile(L, name) || lua_pcall(L, 0, LUA_MULTRET, 0)) {
            luaL_error(L, "Cannot run Lua file: %s", lua_tostring(L, -1));
            return false;
        }

        return true;
    }

#if 0
    static int dostring (lua_State *L, const char *s, const char *name)
    {
        if(luaL_loadbuffer(L, s, strlen(s), name) ||
                lua_pcall(L, 0, LUA_MULTRET, 0))
        {
            luaL_error(L, "Failed executing string: %s", lua_tostring(L, -1));
            return false;
        }

        return true;
    }
#endif

    Scale_if::Scale_if() : m_L(luaL_newstate())
    {
        if(NULL == m_L) {
            return;
        }

        luaL_openlibs(m_L);

        /* Register the SCALE methods with the new Lua global state.
         */
        Task_properties::register_class(m_L);
        Task::register_class(m_L);
        Scheduler::register_class(m_L);
    }

    bool Scale_if::run_script(const char *script_name)
    {
        return dofile(m_L, script_name);
        // return __run_script(script_name);
    }

} // end namespace
