#ifndef __SRTX_CONTAINER_H__
#define __SRTX_CONTAINER_H__

#include "SRTX/Task.h"

namespace SRTX {

    /**
     * This class acts as a container for shared object libraries that
     * implement the heart of the tasks functionality.
     */
    class Container : public SRTX::Task {

      public:
        /**
         * Constructor.
         * @param name Task name.
         * @param appname Pathname of the shared object library containing
         * the application code to be run.
         */
        Container(const char *const name, const char *const appname);

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

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Container(const Container &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Container &operator=(const Container &);

        /**
         * Shared object library pathname.
         */
        const char *const m_appname;

        /**
         * Pointer the the shared library application
         */
        void *m_dll;

        /**
         * Define function pointers.
         */
        typedef void (*vfunc_t)(void);
        typedef bool (*bfunc_t)(void);
        typedef int (*ifunc_t)(void);

        /**
         * Pointers to the application functions
         */
        bfunc_t m_init;
        bfunc_t m_execute;
        vfunc_t m_terminate;
    };

} // namespace

#endif // __SRTX_CONTAINER_H__
