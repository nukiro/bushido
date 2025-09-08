#! bin/bash
set -e

gcc -std=gnu23 -Wall -Wextra -Werror -g -O0 main.c -o main
./main