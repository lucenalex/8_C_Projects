#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DEST="$(mktemp -d)"
trap 'rm -rf "$DEST"' EXIT
FLAGS=(-std=c11 -Wall -Wextra -Wpedantic -Werror -g -fsanitize=undefined -fno-sanitize-recover=all)
gcc "${FLAGS[@]}" "$ROOT/agenda.c" "$ROOT/tests/test_agenda.c" -o "$DEST/test_agenda"
"$DEST/test_agenda"
gcc "${FLAGS[@]}" "$ROOT/main.c" "$ROOT/agenda.c" -o "$DEST/agenda"
python3 "$ROOT/tests/test_agenda_cli.py" "$DEST/agenda"
echo 'PASS: suite funcional da agenda'
