# Using `make` to facilitate the build process

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
