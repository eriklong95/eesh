# Experiment #3: Executing programs in a process

In this experiments, we will use the program defined by `execute_svp.c`.

What happens at the call to `execvp()`?
Will the print statement after the `execvp` call be executed?

## What if ...

As we have now seen, the child process can execute its own programs.
Let's explore this a bit more.

First, try making the child process execute other well-known
programs e.g. `ls`. Try passing options too e.g. `ls -l`.

Finally, consider that the executable that we have compiled from `execute_svp.c`
is also an honest-to-God program. So, we could make the child process execute that.
What do you think will happen? Will the program terminate? When?

Can the child process kill the parent process?
