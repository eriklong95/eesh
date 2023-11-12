# Experiment #0: Process IDs

## Print a PID

Compile `pid_control.c` and run the resulting executable.
What output do you see?

Try stopping the program and running it again. Do you get the same output this time?

Modify the program so that it calls `getpid()` inside of
the `while` loop and reassigns the variable `pid` with the
return value. What output does the program produce now?

## The commands `top` and `ps`

From the commandline, try running the command

```
top
```

What do you see? Anything familiar.

Pick a number from the column `PID` in the table, quit `top`
and run

```
ps [PID]
```

What does the `TIME` column in the output
of `ps` mean?

Run the `pid_control` example. Open a separate terminal
window and run the `ps` command with the number from the
output of `pid_control`.

## The `kill` command

From the commandline, run

```
man kill
```

and read about the `kill` utility.

Run the `pid_control` example program and try to stop
it with the `kill` command from a different terminal
window.

Can you `kill` any process? Can you mess up your system
with `kill`?

## What's the `#include <unistd.h>` all about?

If you are on a Linux system, change directory
to **/usr/include**
and explore the content of the directory.

You should be able to find the file **unistd.h**.
This is a so-called _header file_.
Open the file in an text editor. Why does this file exist
on your system? What does it do?

You can find the declaration of `getpid()` in **unistd.h**,
but not the code the implements. How does this work?

Where can the file **unistd.h** be found on a macOS system?
