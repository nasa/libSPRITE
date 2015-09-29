local lunatest = require "lunatest"

function test_tasks()

    -- Set up the scheduler.
    s = Scheduler.new()
    tp = Task_properties.new()
    priority = tp:MAX_USER_TASK_PRIO()
    tp:set_prio(priority)
    tp:set_period(0.5)
    priority = priority - 1

    lunatest.assert_equal(1, s:set_properties(tp), "Failed setting scheduler properties")

    -- Create a periodic task.
    tp:set_prio(priority)
    tp:set_period(1.0)
    t1 = Test_task.new("Task1")
    lunatest.assert_equal(1, t1:set_properties(tp), "Failed setting task properties")

    -- Start everything up.
    lunatest.assert_equal(1, s:start(), "Failed starting scheduler")
    lunatest.assert_equal(1, t1:start(), "Failed starting task")

    -- Let this baby run for five seconds.
    os.execute("sleep " .. tonumber(5))

    -- Halt the task
    t1:stop()
    s:stop()
end

lunatest.run()
