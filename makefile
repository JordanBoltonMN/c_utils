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
SRC_DIR  = src
OBJ_DIR  = obj
BIN_DIR  = bin

SOURCES  := $(wildcard $(SRC_DIR)/*.c)
INCLUDES := $(wildcard $(SRC_DIR)/*.h)
OBJECTS  := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
rm       = rm -f

.PHONY: clean remove tests run-tests

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@$(rm) $(OBJECTS)
	cd ./tests && make clean
	@echo "Cleanup complete!"

remove: clean
	@$(rm) $(BIN_DIR)/$(TARGET)
	cd ./tests && make remove
	@echo "Executable(s) removed!"

tests:
	cd ./tests && make

run-tests:
	cd ./tests && make run
