# Compiling and running C programs

To compile the C source file **program.c**, run the command

```
gcc program.c
```

from the directory where program.c is located.
This produces an executable file.

To control the name and location of the executable being
produced, use the `-o` option
like so

```
gcc program.c -o my-favourite-place/my-executable
```

The executable will get the name `my-executable` and it will
be placed in the `my-favourite-place` directory (which in
this case must a sub-directory of the parent directory
of **program.c**).

The executable can be run using

```
./my-favourite-place/my-executable
```

If you have read this far, you have all you need to get
started working with the experiments. Read on [here](using-make.md), if you
want some hints on using the `make` utility for this
project.
