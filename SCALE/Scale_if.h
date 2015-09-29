#ifndef __SCALE_SCALE_IF_H__
#define __SCALE_SCALE_IF_H__

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace SCALE {
    class Scale_if {
      public:
        /**
         * Get and instance to the Scale_if Lua interpreter state
         */
        static Scale_if &get_instance()
        {
            static Scale_if instance;
            return instance;
        }

        /**
         * Get a pointer to the Lua state.
         */
        lua_State *state() const
        {
            return m_L;
        }

        /**
         * Run a Lua script.
         * @param script_name The script name.
         * @return True if the script ran successfully, else false.
         */
        bool run_script(const char *script_name);

        /**
         * Destructor.
         */
        ~Scale_if()
        {
            lua_close(m_L);
        }

      private:
        /**
         * The Lua state.
         */
        lua_State *m_L;

        /**
         * Constructor.
         * The constructor is made private as part of the singleton
         * pattern.
         */
        Scale_if();

        /**
         * Copy constructor.
         * The copy constructor is made private as part of the singleton
         * pattern.
         */
        Scale_if(const Scale_if &);

        /**
         * Assignment operator.
         * The assignment operator is made private as part of the singleton
         * pattern.
         */
        Scale_if &operator=(const Scale_if &);
    };

} // namespace

#endif // __SCALE_SCALE_IF_H__
