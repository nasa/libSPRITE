#include "SRTX/Container.h"
#include "base/XPRINTF.h"
#include <dlfcn.h>

namespace SRTX {

    Container::Container(const char *const name, const char *const appname)
        : Task(name)
        , m_appname(appname)
        , m_dll(NULL)
        , m_init(NULL)
        , m_execute(NULL)
        , m_terminate(NULL)
    {
    }

    bool Container::init()
    {
        DPRINTF("Task %s, init\n", m_name);

        m_dll = dlopen(m_appname, RTLD_LAZY);
        if(NULL == m_dll) {
            EPRINTF("Error loading %s\n\t%s\n", m_appname, dlerror());
            return false;
        }

        m_init = reinterpret_cast<bfunc_t>(dlsym(m_dll, "init"));
        if(NULL == m_init) {
            EPRINTF("Error finding init() function\n");
            return false;
        }

        m_execute = reinterpret_cast<bfunc_t>(dlsym(m_dll, "execute"));
        if(NULL == m_execute) {
            EPRINTF("Error finding execute() function\n");
            return false;
        }

        m_terminate = reinterpret_cast<vfunc_t>(dlsym(m_dll, "terminate"));
        if(NULL == m_terminate) {
            EPRINTF("Error finding terminate() function\n");
            return false;
        }

        return m_init();
    }

    bool Container::execute()
    {
        return m_execute();
    }

    void Container::terminate()
    {
        DPRINTF("Task %s, terminate\n", m_name);

        if(m_terminate) {
            m_terminate();
        }
        m_init = NULL;
        m_execute = NULL;
        m_terminate = NULL;

        if(m_dll) {
            dlclose(m_dll);
        }
        m_dll = NULL;
    }

} // namespace
