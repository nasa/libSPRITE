#ifndef __SCALE_NEST_H__
#define __SCALE_NEST_H__

#include "SRTX/Task.h"
#include "SCALE/Scale_if.h"

namespace SCALE {

    /**
     * This class is a SRTX task that loads and runs a Lua script.
     */
    class Nest : public SRTX::Task {

      public:
        /**
         * Constructor.
         * @param name Task name.
         */
        Nest(const char *const name);

        /**
         * Initialization routine.
         * @return true on success or false on failure.
         */
        bool init();

        /**
         * This the the function that gets executed on a periodic basis
         * each time this task is scheduler to run.
         * @return Return true to continue execution or false to terminate
         * the task.
         */
        bool execute();

        /**
         * Terminate routine.
         */
        void terminate();

        /**
         * Tell the task what script you want it to run.
         */
        void register_script(char *scriptname)
        {
            m_scriptname = scriptname;
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Nest(const Nest &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Nest &operator=(const Nest &);

        char *m_scriptname;

        /**
         * Interface to the SCALE engine.
         */
        Scale_if &m_scale;
    };

} // namespace

#endif // __SCALE_NEST_H__
