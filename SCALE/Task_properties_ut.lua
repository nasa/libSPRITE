local lunatest = require "lunatest"

-- Test get/set the priority method.
function sg_prio(t)
    t:set_prio(10)
    lunatest.assert_equal(10, t:get_prio())
    lunatest.assert_not_equal(0, t:MAX_USER_TASK_PRIO());
    lunatest.assert_not_equal(0, t:MIN_USER_TASK_PRIO());
end

-- Test the period set/get routines
function sg_period(t)
    t:set_period(0.050)
    lunatest.assert_equal(0.050, t:get_period())
end

-- Test the schedule_presence set/get routines
function sg_schedule_presence(t)
    t:set_schedule_presence(0x10)
    lunatest.assert_equal(0x10, t:get_schedule_presence())
end

-- Test the period set/get routines
function sg_stack_size(t)
    t:set_period(0x4000)
    lunatest.assert_equal(0x4000, t:get_period())
end

-- Create a task with a variable number of arguments, then verify that if
-- parameters were specified, that they actually got set in the constructor.
function task_setup(...)
    t=Task_properties.new()
    t:init(unpack(arg))
    nargs = #arg
    if nargs >= 1 then
        lunatest.assert_equal(arg[1], t:get_prio())
    end
    if nargs >= 2 then
        lunatest.assert_equal(arg[2], t:get_period())
    end
    if nargs >= 3 then
        lunatest.assert_equal(arg[3], t:get_schedule_presence())
    end
    if nargs >= 4 then
        lunatest.assert_equal(arg[4], t:get_stack_size())
    end
    return t
end

-- Test the task properties by creating the task with the default set of
-- properties.
function test_defaults()
    t = task_setup()
    sg_prio(t)
    sg_period(t)
    sg_schedule_presence(t)
    sg_stack_size(t)
end

-- Test the task properties by creating the task with an initial value for
-- priority.
function test_1()
    t = task_setup(30)
end

-- Test the task properties by creating the task with an initial values for
-- priority and period.
function test_2()
    t = task_setup(40, 0.020)
end

-- Test the task properties by creating the task with an initial values for
-- priority period and schedule presence bitmask.
function test_3()
    t = task_setup(40, .020, 0x0F)
end

-- Test the task properties by creating the task with an initial values for
-- priority period, schedule presence bitmask and stack size.
function test_4()
    t = task_setup(40, .020, 0x0F, 0x10000)
end

lunatest.run()
