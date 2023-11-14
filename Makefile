SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .c .o

SRCDIR = src
IDIR = $(SRCDIR)/include

CC = gcc
CFLAGS = -I$(IDIR)

BUILDDIR = ./build
APP_BUILDDIR = $(BUILDDIR)/app
OBJDIR = $(APP_BUILDDIR)/objects

DEPS := $(wildcard $(IDIR)/*.h)

OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.c))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

eesh: $(OBJS)
	$(CC) -o $(APP_BUILDDIR)/$@ $^ $(CFLAGS)

EXAMPLES_SRCDIR = ./examples
$(EXAMPLES_SRCDIR)/%: $(EXAMPLES_SRCDIR)/%.c
	$(CC) -o $(BUILDDIR)/$@ $@.c

.PHONY: clean
clean:
	rm -r $(BUILDDIR)

printdeps:
	echo $(DEPS)

printobjs:
	echo $(OBJS)
