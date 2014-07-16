TESTFILE = "results.out"

file = io.open(TESTFILE, "w")

a = 5

for i = 0, 50, 5 do
    file:write("Value = ", a*i, "\n")
end

io.close(file)
