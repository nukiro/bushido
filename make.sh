#!/usr/bin/env bash
set -Eeuo pipefail

# --- ASCII-safe horizontal rule (no Unicode/tr) ---
hr() {
  local cols; cols=$( (command -v tput >/dev/null && tput cols) 2>/dev/null || echo 80 )
  [ "$cols" -lt 1 ] && cols=80
  printf '%*s\n' "$cols" '' | sed 's/ /-/g'
}

# --- compile with live colored output + summary ---
compile_and_report_live() {
  # usage: compile_and_report_live <compiler ...>
  local tmp rc warn err compiler
  tmp=$(mktemp)

  # Build command array so we can append "force-color" flags when needed
  local cmd=( "$@" )
  compiler="${cmd[0]##*/}"

  # Force colored diagnostics when piped (GCC/Clang)
  case "$compiler" in
    *clang*) cmd+=( -fcolor-diagnostics ) ;;
    *gcc*|*g++*) cmd+=( -fdiagnostics-color=always ); export GCC_COLORS=1 ;;
  esac

  hr

  # Stream to terminal (with colors) and capture to file
  # rc is the compiler's exit code, not tee's
  "${cmd[@]}" 2>&1 | tee "$tmp"
  rc=${PIPESTATUS[0]}

  hr

  # Count warnings/errors (gcc/clang style)
  warn=$(grep -ciE '\bwarning:' "$tmp" || true)
  err=$(grep -ciE '\b(fatal )?error:' "$tmp" || true)

  if [ $rc -eq 0 ] && [ "$warn" -eq 0 ]; then
    ok "No compilation issues."
  else
    [ "$warn" -gt 0 ] && echo "${DIM}Warnings:${RESET} $warn"
    [ "$err"  -gt 0 ] && echo "${DIM}Errors:${RESET}   $err"
    if [ $rc -ne 0 ]; then
      fail "Compiler exited with code $rc."
    else
      fail "Build completed with warnings."
    fi
  fi

  rm -f "$tmp"
  return $rc
}

compile_and_report_live() {
  local tmp rc warn err
  tmp=$(mktemp)

  # Build cmd + force colored diagnostics when piped
  local cmd=( "$@" )
  case "${cmd[0]##*/}" in
    *clang*) cmd+=( -fcolor-diagnostics ) ;;
    *gcc*|*g++*) cmd+=( -fdiagnostics-color=always ); export GCC_COLORS=1 ;;
  esac

  hr

  # With `set -e`, commands used in `if` conditions won't abort the script.
  if "${cmd[@]}" 2>&1 | tee "$tmp"; then
    rc=0
  else
    rc=${PIPESTATUS[0]}  # compiler’s status (not tee’s)
  fi

  hr

  # Strip ANSI before counting (colors don’t confuse grep)
  warn=$(sed -r 's/\x1b\[[0-9;]*m//g' "$tmp" | grep -ciE '\bwarning:' || true)
  err=$(sed -r 's/\x1b\[[0-9;]*m//g' "$tmp" | grep -ciE '\b(fatal )?error:' || true)

  if [ $rc -eq 0 ] && [ "$warn" -eq 0 ]; then
    printf '%s%s%s %s\n' "$(tput setaf 2 2>/dev/null)" "✅" "$(tput sgr0 2>/dev/null)" "No compilation issues."
  else
    [ "$warn" -gt 0 ] && echo "Warnings: $warn"
    [ "$err"  -gt 0 ] && echo "Errors:   $err"
    if [ $rc -ne 0 ]; then
      printf '%s%s%s %s\n' "$(tput setaf 1 2>/dev/null)" "❌" "$(tput sgr0 2>/dev/null)" "Compiler exited with code $rc."
    else
      printf '%s%s%s %s\n' "$(tput setaf 1 2>/dev/null)" "❌" "$(tput sgr0 2>/dev/null)" "Build completed with warnings."
    fi
  fi

  rm -f "$tmp"
  return $rc
}

usage() {
  cat <<'EOF'
Usage: ./make <install|dev|test|release> [options]

Options:
  --werror            Add -Werror to CFLAGS
  --no-werror         Ensure -Werror is NOT set
  -r, --run           After building, run the resulting binary (dev/test only)
  --no-run            Compile only (default)
  -h, --help          Show this help

Examples:
  ./make dev --werror
  ./make test
EOF
}

# --- subcommand ---
[[ $# -lt 1 ]] && { usage; exit 1; }
SUBCMD="$1"; shift || true

# --- defaults ---
CC=( gcc )
STD=( gnu23 )
CFLAGS=( -Wall -Wextra )
LDFLAGS=( -lraylib -lm -ldl -lpthread -lGL -lrt -lX11 )

WERROR=0
RUN=0

# --- option parse (pure bash, portable) ---
while (($#)); do
  case "$1" in
    --werror)       WERROR=1 ;;
    --no-werror)    WERROR=0 ;;
    -r|--run)       RUN=1 ;;
    --no-run)       RUN=0 ;;
    -h|--help)      usage; exit 0 ;;
    --)             shift; break ;;
    *)              echo "Unknown option: $1" >&2; usage; exit 2 ;;
  esac
  shift || true
done

# --- compose flags ---
(( WERROR )) && CFLAGS+=( -Werror )

# --- project ---
INCLUDEDIR="bushido/include"
SOURCEDIR="bushido/src"
TESTSDIR="bushido/tests"

mkdir -p dist

# --- build recipes ---
install() {
  echo "installing..."

  APPDIR="$HOME/.local/share/applications"
  APP="$APPDIR/bushido.desktop"
  ICONDIR="$HOME/.local/share/icons/hicolor/256x256/apps"
  ICON="$ICONDIR/samurai.png"

  mkdir -p "$APPDIR"

  # desktop
  if [[ ! -f "$APP" ]]; then
    cp --update=none "bushido.desktop" $APP
    chmod 0644 "$APP"
    echo "Installed: $APP"
  else
    echo "Desktop entry exists, not overwriting: $APP"
  fi
  # icon
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
}

build_dev() {
  echo "building for dev..."
  compile_and_report_live "$CC" -std="$STD" "${CFLAGS[@]}" -g -Og -DDEBUG -I$INCLUDEDIR -o dist/dev bushido/main.c $SOURCEDIR/*.c "${LDFLAGS[@]}"
  if (( RUN )); then
    echo ""
    ./dist/dev
  fi
}

build_test() {
  echo "building for test..."
  echo ""
  "$CC" "${CFLAGS[@]}" -g -O0 -DTEST -I$INCLUDEDIR -I$TESTSDIR -o dist/tests tests/*.c src/*.c "${LDFLAGS[@]}"
  echo "running tests..."
  echo ""
  ./dist/tests
}

build_release() {
  echo "build_release"
}

case "$SUBCMD" in
  install)  install ;;
  dev)      build_dev ;;
  test)     build_test ;;
  release)  build_release ;;
  *)        echo "Unknown subcommand: $SUBCMD" >&2; usage; exit 2 ;;
esac
