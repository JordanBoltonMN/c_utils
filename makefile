# Modified from:
# http://stackoverflow.com/questions/7004702/how-can-i-create-a-makefile-for-c-projects-with-src-obj-and-bin-subdirectories

# ------------------------------------------------
# Generic Makefile
#
# Author: yanick.rochon@gmail.com
# Date  : 2011-08-10
#
# Changelog :
#   2010-11-05 - first version
#   2011-08-10 - added structure : sources, objects, binaries
#                thanks to http://stackoverflow.com/users/128940/beta
# ------------------------------------------------

dirname = $(patsubst %/,%,$(dir $1))

# project name (generate executable with this name)
TARGET   = c_utils

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall -Wextra -I.

LINKER   = gcc -o
# linking flags here
LFLAGS   = -std=c99 -Wall -Wextra -I. -lm

# change these to set the proper directories where each files should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TESTDIR  = tests

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

# each test has their own main method
TEST_SOURCES := $(wildcard $(TESTDIR)/test_*.c)
TEST_OBJECTS  := $(filter-out $(OBJDIR)/main.o, $(OBJECTS)) $(TESTDIR)/test.o
TESTS = $(TESTDIR)/test_str $(TESTDIR)/test_dbl_ll
TESTS = $(TESTDIR)/$(TARGET)/test_str $(TESTDIR)/$(TARGET)/test_dbl_ll

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@$(rm) $(TEST_OBJECTS)
	@echo "Cleanup complete!"

remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@$(foreach test, $(TESTS), $(rm) $(test);)
	@echo "Executable(s) removed!"

run_tests: $(TESTS)
	$(foreach test, $(TESTS), ./$(TESTDIR)/$(TARGET)/$(test);)

tests: $(TESTS)

$(TESTDIR)/$(TARGET)/test_%: $(TEST_OBJECTS) tests/test_str.c
	@$(LINKER) $@ $(LFLAGS) $^
	@echo "Compiled "$@" successfully!"

$(TESTDIR)/test.o: $(TESTDIR)/test.c
	@$(CC) $(CFLAGS) -c $< -o $@
