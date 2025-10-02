CC = gcc
STD = gnu23
CFLAGS = -Wall -Wextra -Wmissing-prototypes -Wmissing-declarations
DFLAGS = -g -Og -DDEBUG

# Raylib library
LRAY = -lyaml -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

SRC = $(shell find bushido/src -name '*.c')
OBJ = $(SRC:.c=.o)

all: bin main run

bin:
	@mkdir -p bin

main: bin $(OBJ)
	@$(CC) -std=$(STD) $(CFLAGS) $(DFLAGS) $(OBJ) -o bin/main $(LRAY)

run:
	@echo "-------"
	@./bin/main

s:
	@find bushido/src -name '*.c'

h:
	@find bushido/include -name '*.h'

o:
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