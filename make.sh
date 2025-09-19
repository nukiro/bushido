#! bin/bash
set -euo pipefail

COMMAND=$1

STD="-std=gnu23"
CFLAGS="-Wall -Wextra -Werror -g -O0"
DDEBUG="-DDEBUG"
DTEST="-DTEST"
LDFLAGS="-lraylib -lm -ldl -lpthread -lGL -lrt -lX11"

INCLUDE="bushido/include"
SOURCE="bushido/src"
TESTS="bushido/tests"

APPDIR="$HOME/.local/share/applications"
DESKTOP="$APPDIR/bushido.desktop"
ICONDIR="$HOME/.local/share/icons/hicolor/256x256/apps"
ICON="$ICONDIR/samurai.png"

case "$COMMAND" in
  dev)
    echo "Running dev..."
    echo ""
    gcc $STD $CFLAGS $DDEBUG -I$INCLUDE $SOURCE/*.c bushido/main.c -o dist/dev $LDFLAGS
    
    mkdir -p "$APPDIR"

    if [[ ! -f "$DESKTOP" ]]; then
      cp --update=none "bushido.desktop" $DESKTOP
      chmod 0644 "$DESKTOP"
      echo "Installed: $DESKTOP"
    else
      echo "Desktop entry exists, not overwriting: $DESKTOP"
    fi

    if [[ -f "samurai.png" ]]; then
      if [[ ! -f "$ICON" ]]; then
        mkdir -p "$ICONDIR"
        cp --update=none "samurai.png" "$ICON"
        echo "Installed icon: $ICON"
        # harmless if not needed
        gtk-update-icon-cache "$HOME/.local/share/icons" >/dev/null 2>&1 || true
      else
        echo "Icon exists, not overwriting: $ICON"
      fi
    fi
    # Refresh desktop DB (harmless if not needed)
    update-desktop-database "$APPDIR" >/dev/null 2>&1 || true

    echo ""
    ./dist/dev
    ;;
  build)
    echo "Running build..."
    echo ""
    gcc $STD $CFLAGS -I$SOURCE bushido/main.c -o dist/build $LDFLAGS
    ./dist/main
    ;;
  test)
    echo "Compiling tests..."
    gcc $STD $CFLAGS $DTEST $DDEBUG -I$INCLUDE -I$TESTS $SOURCE/*.c $TESTS/runner.c -o dist/tests $LDFLAGS
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