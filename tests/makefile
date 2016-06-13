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

# project name (generate executable with this name)
TARGET   = c_utils

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall -Wextra -I.

LINKER   = gcc -o
# linking flags here
LFLAGS   = -std=c99 -Wall -Wextra -I. -lm

# change these to set the proper directories where each files should be
ROOT_DIR     = ..
ROOT_SRC_DIR = $(ROOT_DIR)/src
ROOT_OBJ_DIR = $(ROOT_DIR)/obj
SRC_DIR      = src
OBJ_DIR      = obj
BIN_DIR      = bin

BIN_PREFIX = $(BIN_DIR)/$(TARGET)_
TEST_MACROS = $(OBJ_DIR)/$(TARGET)_macros.o

SOURCES      := $(wildcard $(ROOT_SRC_DIR)/*.c)
INCLUDES     := $(wildcard $(ROOT_SRC_DIR)/*.h)
OBJECTS      := $(SOURCES:$(ROOT_SRC_DIR)/%.c=$(ROOT_OBJ_DIR)/%.o)
TEST_OBJECTS := $(filter-out $(ROOT_OBJ_DIR)/main.o, $(OBJECTS)) $(OBJ_DIR)/$(TARGET)_macros.o
rm           = rm -f

TESTS := $(BIN_DIR)/$(TARGET)_test_dbl_ll
TESTS += $(BIN_DIR)/$(TARGET)_test_str

$(OBJECTS):
	cd .. && make

clean:
	@$(rm) $(TEST_OBJECTS)
	@echo "Cleanup complete!"

remove: clean
	@$(rm) $(BIN_DIR)/$(TARGET)/*
	@echo "Executable(s) removed!"

run: tests
	@echo "Starting tests."
	$(foreach test, $(TESTS), ./$(test);)
	@echo "Done."

tests: $(TESTS)

$(BIN_DIR)/$(TARGET)_test_str: $(TEST_OBJECTS) $(SRC_DIR)/test_str.c
	@$(LINKER) $@ $(LFLAGS) $^
	@echo "Compiled "$@" successfully!"

$(BIN_DIR)/$(TARGET)_test_dbl_ll: $(TEST_OBJECTS) $(SRC_DIR)/test_dbl_ll.c
	@$(LINKER) $@ $(LFLAGS) $^
	@echo "Compiled "$@" successfully!"

$(OBJ_DIR)/$(TARGET)_macros.o: $(SRC_DIR)/macros.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"
