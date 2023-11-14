SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .c .o

SRCDIR = src
IDIR = $(SRCDIR)/include

CC = gcc
CFLAGS = -I$(IDIR)

BUILDDIR = ./build
OBJDIR = $(BUILDDIR)/app/objects

_DEPS = user_input.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJS = main.o user_input.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

eesh: $(OBJS)
	$(CC) -o $(BUILDDIR)/app/$@ $^ $(CFLAGS)

EXAMPLES_SRCDIR = ./examples
$(EXAMPLES_SRCDIR)/%: $(EXAMPLES_SRCDIR)/%.c
	$(CC) -o $(BUILDDIR)/$@ $@.c
