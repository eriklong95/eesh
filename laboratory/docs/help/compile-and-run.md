# Compiling and running C programs

## Using the `gcc` command

To compile the C source file **program.c**, run the command

```
gcc program.c
```

from the directory where program.c is located.
This produces an executable file.

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

If you have read this far, you have all you need to get
started working with the experiments. Read on, if you
want some hints on using the `make` utility for this
project.

## Using `make` to facilitate the build process

When working with C programs, the `make` utility is often
used to make compiling and related tasks easier for the developer.

The **Makefile** at the root directory of the project defines
several useful commands or _targets_. Running

```
make
```

will compile the **eesh** app and

```
make run
```

will run it. `make run` will compile first if needed.
Use `make clean` to remove all generated
compilation output.

Targets for compiling the example programs have
also been defined.

```
make examples/pid_control
```

will compile the **examples/pid_control.c** example program
and put the resulting executable at **build/examples/pid_control**.
