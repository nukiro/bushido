CC = gcc
STD = gnu23
CFLAGS = -Wall -Wextra -Wmissing-prototypes -Wmissing-declarations
DFLAGS = -g -Og -DDEBUG
DEPFLAGS = -MMD -MP

# Raylib library
LRAY = -lyaml -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

SRC   = $(shell find bushido/src -name '*.c')
OBJ   = $(SRC:.c=.o)
DEPS  = $(OBJ:.o=.d)

# Main program
MAIN = main

all: $(MAIN)

# Build main program
$(MAIN): $(OBJ)
	@$(CC) -std=$(STD) $(CFLAGS) $(DFLAGS) $(OBJ) -o $(MAIN) $(LRAY)

run: $(MAIN)
	@./$(MAIN)

source:
	@find bushido/src -name '*.c'

header:
	@find bushido/include -name '*.h'

object:
	@find bushido/src -name '*.o'

%.o: %.c
	@echo "Compiling: $<"
	@$(CC) -std=$(STD) $(CFLAGS) $(DFLAGS) $(DEPFLAGS) -Ibushido/include -c $< -o $@

-include $(DEPS)

clean:
	@echo "Removing exe and object files."
	@rm -f $(MAIN) $(OBJ) $(DEPS)
	@echo "Done!"

install:
	@echo "Installing app files."

.PHONY: all run source header object clean install