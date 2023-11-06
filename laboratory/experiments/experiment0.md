Compile `print_pid.c` and run resulting executable.
What output do you see?
Try stopping the program and running it again. Do you get the same output this time?

Modify the program so that it calls `getpid()` inside of
the `while` loop and reassigns the variable `pid` with the
return value. What output does the program produce now?


## `top` and `ps`
try running `top` from the commandline
you will see a list of running processes
pick a PID, quit `top` and run `ps <PID>`
what process has PID = 1?

## `kill`
run `man kill` and read about the kill utility
start print_pid.c
try to stop it from a different terminal window

## `<unistd.h>`
If you are on a Linux system, `cd` to /usr/include
and explore the content of the directory

You should be able to find the header file unistd.h
Open it

the `getpid()` function is declared here

unistd.h is a header file. where is the implementation?
