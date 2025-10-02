CC = gcc
STD = gnu23
CFLAGS = -Wall -Wextra -Wmissing-prototypes -Wmissing-declarations
DFLAGS = -g -Og -DDEBUG

.PHONY: all run source header object clean install

# Raylib library
LRAY = -lyaml -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

SRC = $(shell find bushido/src -name '*.c')
OBJ = $(SRC:.c=.o)

all: bin main

bin:
	@mkdir -p bin

main: bin $(OBJ)
	@$(CC) -std=$(STD) $(CFLAGS) $(DFLAGS) $(OBJ) -o bin/main $(LRAY)

run: main
	@echo "-------"
	@./bin/main

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
	@rm -f bin/main $(OBJ)
	@echo "Done!"

install:
	@echo "Installing app files."