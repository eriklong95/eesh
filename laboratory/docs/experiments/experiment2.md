# Experiment #2: Waiting for a process

The example program `wait_for_me.c` uses the function `wait`.
Run the program and observe the output. As you might have guessed,
the `wait` function will make the parent process _wait_ for the
child process to finish before it proceeds.

Experiment with putting the `wait(NULL)` statement different places in the code.

In `wait_for_me.c`, we pass `NULL` to `wait`. What effect does the argument
passed to `wait` have? How does the `wait` function know which process to wait for?
