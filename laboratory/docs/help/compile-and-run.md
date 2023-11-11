# Compiling and running C programs

## Using the `gcc` command

To compile program.c, run the command
```
gcc program.c
```
for the directory where program.c is located. This produces
an executable file.

To control the name and location of the executable being
produced by the compilation process, use the `-o` option
like so
```
gcc program.c -o my-favourite-place/my-executable
```
The executable will get the name `my-executable` and it will
be placed in the `my-favourite-place` directory (which in 
this case must a sub-directory of the parent directory 
of program.c).

The executable can be run using
```
./my-favourite-place/my-executable
```

## eesh conventions for locations of executables

For this project, the following convention has been chosen:
All executables are put in the directory **target** (on the
root level). The executable for the eesh application 
(i.e. what is built from the code under **src**) is put 
directly under **target**. Example executables (i.e. stuff 
built from code in the examples directory) is put
in **target/examples**.

As an example, the conventional way of compiling
the `pid_control.c` example source file is by using the
command
```
gcc examples/pid_control.c -o target/examples/pid_control
```
