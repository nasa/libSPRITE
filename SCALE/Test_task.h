#ifndef __SCALE_TEST_TASK_H__
#define __SCALE_TEST_TASK_H__

#include "SRTX/Task.h"

namespace SCALE {
    class Test_task : public SRTX::Task {
      public:
        /**
         * Constructor.
         * @param name Task name.
         */
        Test_task(const char *const name);

        /**
         * Function to execute when the task is released.
         * @return True if the task should continue running or false to
         * halt the task.
         */
        bool execute();
    };

} // namespace

#endif //__SCALE_TEST_TASK_H__
