SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .c .o

SRCDIR = src

IDIR = ./src/include
CC = gcc
CFLAGS = -I$(IDIR)

OBJDIR = ./obj

_DEPS = user_input.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJS = main.o user_input.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

BUILDDIR = ./target

eesh: $(OBJS)
	$(CC) -o $(BUILDDIR)/$@ $^ $(CFLAGS)

EXAMPLES_SRCDIR = ./examples
$(EXAMPLES_SRCDIR)/%: $(EXAMPLES_SRCDIR)/%.c
	$(CC) -o $(BUILDDIR)/$@ $@.c
