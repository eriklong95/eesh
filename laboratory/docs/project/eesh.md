# Project: Building `eesh`

Are you ready for a challenge? Then you have
come to the right place!

## An Inspirational Quote

Consider the following statement

> ... the separation of `fork()` and `exec()` is
> essential in building a UNIX shell, because it
> lets the shell run code *after* the call to `fork()`
> but *before* the call to `exec()`...
>
> *Operating Systems: Three Easy Pieces*:
> R. H. Arpaci-Dusseau, A. C Arpaci-Dusseau

Take the ideas from this quote and turn them into 
REALITY! That is, make a shell program using your
knowledge about UNIX system calls. Some starting
code is in **src** directory of the **eesh**
repository.

## Any good shell should...

The shell should accept input from the user
treat it as

Apart this fundamental functionality, you can try
to implement additional features:

#### Displaying current directory

Many shells display the current directory at the prompt so that the user knows where *he is (in case *he forgot).

#### Reading input from a file, redirecting output
The command line
```
prog <input >output
```
means "Run the program `prog` but instead reading input
from `stdin`, read it from the file **input**, and
instead printing output to `stdout`, write it to the file
**output**".

#### Piping
Using the symbol `|`, you can *pipe* the output of one
program into another. As an example, consider the command
line
```
ls | grep important
```
will give you all the files and directories in the
current working directory whose name contains the string
"important".

There is a system call `pipe()` declared in **unistd.h**.
Can you use this to make your shell support piping.
