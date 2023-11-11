# Experiment #3: Executing programs in a process

In this experiment, we will use the program defined by `execute_svp.c`.
Run the program and try to figure out what the `execvp` function does.

What output do you see?
Does the print statement after the `execvp` call get executed?
How many processes are created by the program in total?

## What if ...

As we have now seen, the child process can execute its own programs.
Let's explore this a bit more.

First, try making the child process execute other well-known
programs e.g. `ls`. Try passing options too e.g. `ls -l`.
What about trying make the child process run an executable
that does not exist?

Next, recall that we have seen that you can terminate a process
using `kill [PID]`. Try making the child process terminate the parent process.

Finally, consider that the executable that we have compiled from `execute_svp.c`
is also an honest-to-God program. So, we could make the child process execute that.
What do you think will happen? Will the program terminate? When?
