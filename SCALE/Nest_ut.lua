local s = require "scheduler"

--------------------------------------------------------------------------------
-- Use the Lua interpreter to run the file natively and create an expected
--results file that we can compare against.
--------------------------------------------------------------------------------

TESTFILE = "domath.lua"
RESULTS = "results.out"
EXPECTED = "expected.out"

-- Run the script to get the expected results.
os.execute("lua " .. TESTFILE)
os.rename(RESULTS, EXPECTED)

--------------------------------------------------------------------------------
-- Start programming
--------------------------------------------------------------------------------

-- Create task properties and set an initial priority.
tp = Task_properties.new()
priority = tp:MAX_USER_TASK_PRIO()

-- Create the scheduler.
SCHEDULER_PERIOD = s.HZ_to_period(10)
scheduler = s.create(tp, SCHEDULER_PERIOD,  priority)
priority = priority - 1

-- Create task that will execute the nested Lua script.
nest = Nest.new("Nest", TESTFILE)
s.set_task_properties(nest, tp, 0, priority)
priority = priority - 1
nest:register_script(TESTFILE)

--------------------------------------------------------------------------------
-- Start the tasks.
--------------------------------------------------------------------------------

-- Start everything up.
print "Starting tasks..."
scheduler:start()
nest:start()

-- Let them run for a second...
os.execute("sleep 1")

--------------------------------------------------------------------------------
-- Halt the tasks
--------------------------------------------------------------------------------

-- Halt the task
nest:stop()
scheduler:stop()


--------------------------------------------------------------------------------
-- Create the execute the unit test.
--------------------------------------------------------------------------------
local lunatest = require "lunatest"

function test_results()
    print "Running test"
    lunatest.assert_equal(0, os.execute("diff " .. EXPECTED .. " " .. RESULTS))
    print "Test complete"
end

lunatest.run()


--------------------------------------------------------------------------------
-- Clean up the output files.
--------------------------------------------------------------------------------
os.remove(RESULTS)
os.remove(EXPECTED)
