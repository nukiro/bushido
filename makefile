SHELL=/bin/bash

# Project Variables
PROJECT := bushido
# Build Variables
TARGET := main
BUILD := ./build
SOURCE := ./$(PROJECT)/src
# Compiler Flags
CC = gcc
STD = gnu23
CFLAGS = -Wall -Wextra -Wmissing-prototypes -Wmissing-declarations
DFLAGS = -g -Og -DDEBUG
# Libraries
LDFLAGS = -lyaml -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

# Find all C files in source folder
SRCS := $(shell find $(SOURCE) -name '*.c')
# Prepends BUILD and appends .o to every src file
# As an example, ./your_dir/hello.c turns into ./build/./your_dir/hello.c.o
OBJS := $(SRCS:%=$(BUILD)/%.o)
# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)
# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := -I$(PROJECT)/include -MMD -MP

# The final build step.
$(BUILD)/$(TARGET): $(OBJS)
	@$(CC) -std=$(STD) $(CFLAGS) $(DFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD)/%.c.o: %.c
	@echo "Compiling: '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -std=$(STD) $(CPPFLAGS) $(DFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@rm -r $(BUILD)
	@echo "build folder deleted"

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up
-include $(DEPS)