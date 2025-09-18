#! bin/bash
set -e

COMMAND=$1

STD="-std=gnu23"
CFLAGS="-Wall -Wextra -Werror -g -O0"
DDEBUG=-DDEBUG
DTEST=-DTEST
LRAYLIB="-lraylib -lm -ldl -lpthread -lGL -lrt -lX11"

INCLUDE=bushido/include
SOURCE=bushido/src
TESTS=bushido/tests

case "$COMMAND" in
  dev)
    echo "Running dev..."
    echo ""
    gcc $STD $CFLAGS $DDEBUG -I$INCLUDE $SOURCE/*.c bushido/main.c -o dist/main $LRAYLIB
    ./dist/main
    ;;
  build)
    echo "Running build..."
    echo ""
    gcc $STD $CFLAGS -I$SOURCE bushido/main.c -o dist/build $LRAYLIB
    ./dist/main
    ;;
  test)
    echo "Compiling tests..."
    gcc $STD $CFLAGS $DTEST $DDEBUG -I$INCLUDE -I$TESTS $SOURCE/*.c $TESTS/runner.c -o dist/tests $LRAYLIB
    echo "Running tests..."
    echo ""
    ./dist/tests
    ;;
  clean)
    echo "Cleaning..."
    ;;
  *)
    echo "Unknown command: $COMMAND"
    exit 1
    ;;
esac

# gcc -std=gnu23 -Wall -Wextra -Werror -g -O0 bushido/main.c -o main -lraylib -lm -ldl -lpthread -lGL -lrt -lX11 -DDEBUG
# gcc -std=gnu23 -g -O0 -Ibushido/src bushido/main.c -o main -lraylib -lm -ldl -lpthread -lGL -lrt -lX11 -DDEBUG
# ./main