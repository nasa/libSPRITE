local scheduler = {}

--------------------------------------------------------------------------------
-- Useful utility function to convert Hz to period.
--------------------------------------------------------------------------------

-- Convert number of HZ to a period that can be used to schedule a task.
function scheduler.HZ_to_period(hz)
    return 1/hz
end


--------------------------------------------------------------------------------
-- Create the scheduler
--------------------------------------------------------------------------------
function scheduler.create(tp, period, task_prio)
    sched = Scheduler.new()
    tp:set_period(period)
    tp:set_prio(task_prio)
    sched:set_properties(tp)

    return sched
end


--------------------------------------------------------------------------------
-- Utility function to set task properties.
--------------------------------------------------------------------------------
function scheduler.set_task_properties(task, tp, period, priority)
    tp:set_period(period)
    tp:set_prio(priority)
    priority = priority - 1
    task:set_properties(tp)
end

return scheduler
