# Experiment 4: Redirecting output
 
**unistd.h** defines three standard *file descriptors*, namely
`STDIN_FILENO`, `STDOUT_FILENO` and `STDERR_FILENO`. What are
their values?

## Writing to `stdout`
In **redirectly.c**, the symbol `STDOUT_FILENO` is used by the
system call `write` in the beginning of the program. What does
this call do? What happens if you exchange `STDOUT_FILENO` for
`STDERR_FILENO` or `STDIN_FILENO`?

## Manipulating file descriptors
In the code, that will be executed by the child process, we call
`close(STDOUT_FILENO)`. You could argue that this line of code is
self-explanatory, but what happens concretely? What happens
with output produced by subsequent calls? E.g. consider the statement
```
printf("Can anybody hear me?\n");
```
Do you see the output from this call in you terminal window?
What if you move the statement somewhere else in the code?