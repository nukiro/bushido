#! bin/bash
set -e

gcc -std=gnu23 -Wall -Wextra -Werror -g -O0 main.c -o main -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
./main