CC = gcc
STD = gnu23
CFLAGS = -Wall -Wextra -Wmissing-prototypes -Wmissing-declarations
DFLAGS = -g -Og -DDEBUG


# Raylib library
LRAY = -lyaml -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

SRC = $(shell find bushido/src -name '*.c')
OBJ = $(SRC:.c=.o)

# Main program
MAIN = main

all: $(MAIN)

# Build main program
$(MAIN): $(OBJ)
	@mkdir -p bin
	@$(CC) -std=$(STD) $(CFLAGS) $(DFLAGS) $(OBJ) -o bin/$(MAIN) $(LRAY)

run: $(MAIN)
	@./bin/$(MAIN)

source:
	@find bushido/src -name '*.c'

header:
	@find bushido/include -name '*.h'

object:
	@find bushido/src -name '*.o'

%.o: %.c
	@echo "Compiling: $<"
	@$(CC) -std=$(STD) $(CFLAGS) $(DFLAGS) -Ibushido/include -c $< -o $@

clean:
	@echo "Removing files in 'bin' and object files."
	@rm -f bin/$(MAIN) $(OBJ)
	@echo "Done!"

install:
	@echo "Installing app files."

.PHONY: all run source header object clean install