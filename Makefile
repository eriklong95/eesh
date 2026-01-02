CC = gcc

SRCDIR := src
SRCDIR_LIB := $(SRCDIR)/lib
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
OBJDIR_LIB := $(OBJDIR)/lib
TESTDIR := $(SRCDIR)/test
BUILDDIR_TEST := $(BUILDDIR)/test

lib_objects := $(patsubst $(SRCDIR_LIB)/%.c,$(OBJDIR_LIB)/%.o,$(wildcard $(SRCDIR_LIB)/*.c))
tests := $(patsubst $(TESTDIR)/%.c,$(BUILDDIR_TEST)/%,$(wildcard $(TESTDIR)/*.c))

$(BUILDDIR)/eesh: $(SRCDIR)/main.c $(lib_objects) | $(BUILDDIR)
	$(CC) -g -o $@ $^

$(lib_objects): $(OBJDIR_LIB)/%.o: $(SRCDIR_LIB)/%.c | $(OBJDIR_LIB)
	$(CC) -g -c -o $@ $^

$(OBJDIR_LIB): $(OBJDIR)
	mkdir -p $@

$(OBJDIR): $(BUILDDIR)
	mkdir -p $@

$(BUILDDIR):
	mkdir -p $@

$(tests): $(BUILDDIR_TEST)/%: $(TESTDIR)/%.c $(lib_objects) | $(BUILDDIR_TEST)
	$(CC) -g -o $@ $^

$(BUILDDIR_TEST):
	mkdir -p $(BUILDDIR_TEST)

.PHONY: clean
clean:
	rm -fr $(BUILDDIR)

.PHONY: run
run: $(BUILDDIR)/eesh
	$<

