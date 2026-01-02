CC = gcc

SRCDIR := src
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
TESTDIR := tests
BUILDDIR_TEST := $(BUILDDIR)/tests

objects := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.c))

$(BUILDDIR)/eesh: $(objects) | $(BUILDDIR)
	$(CC) -g -o $@ $^

$(objects): $(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -g -c -o $@ $^

$(OBJDIR): $(BUILDDIR)
	mkdir -p $(OBJDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR_TEST)/%: $(TESTDIR)/%.c $(OBJDIR)/csapp.o $(OBJDIR)/lib.o $(BUILDDIR_TEST)
	$(CC) -g -o $@ $(OBJDIR)/csapp.o $(OBJDIR)/lib.o $<

$(BUILDDIR_TEST):
	mkdir -p $(BUILDDIR_TEST)

.PHONY: clean
clean:
	rm -r $(BUILDDIR)

.PHONY: run
run: $(BUILDDIR)/eesh
	$<

