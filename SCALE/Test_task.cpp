#include "SCALE/Test_task.h"

namespace SCALE {

    Test_task::Test_task(const char *const name) : SRTX::Task(name)
    {
    }

    bool Test_task::execute()
    {
        printf("Running %s\n", m_name);
        return true;
    }
}
