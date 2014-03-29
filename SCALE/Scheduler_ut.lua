require "lunatest"

function test_tasks()
    -- Set up the scheduler.
    s = Scheduler.new()
    tp = Task_properties.new()
    tp:set_prio(98)
    tp:set_period(0.5)

    assert_equal(1, s:set_properties(tp))

    -- Create a periodic task.
    tp:set_prio(90)
    tp:set_period(1.0)
    t1 = Test_task.new("Task1")
    assert_equal(1, t1:set_properties(tp))

    -- Start everything up.
    assert_equal(1, s:start())
    assert_equal(1, t1:start())

    -- Let this baby run for five seconds.
    os.execute("sleep " .. tonumber(5))

    -- Halt the task
    t1:stop()
    s:stop()
end

lunatest.run()
