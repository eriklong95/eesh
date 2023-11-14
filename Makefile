SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .c .o

SRCDIR = ./src
IDIR = $(SRCDIR)/include

CC = gcc
CFLAGS = -I$(IDIR)

BUILDDIR = ./build
APP_BUILDDIR = $(BUILDDIR)/app
OBJDIR = $(APP_BUILDDIR)/objects

DEPS := $(wildcard $(IDIR)/*.h)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.c))

eesh: $(OBJS)
	$(CC) -o $(APP_BUILDDIR)/$@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS) | $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

EXAMPLES_SRCDIR = ./examples
EXAMPLES_BUILDDIR = $(BUILDDIR)/examples

$(EXAMPLES_SRCDIR)/%: $(EXAMPLES_SRCDIR)/%.c | $(EXAMPLES_BUILDDIR)
	$(CC) -o $(BUILDDIR)/$@ $@.c

$(EXAMPLES_BUILDDIR):
	mkdir -p $(EXAMPLES_BUILDDIR)

.PHONY: clean
clean:
	rm -r $(BUILDDIR)

printdeps:
	echo $(DEPS)

printobjs:
	echo $(OBJS)
