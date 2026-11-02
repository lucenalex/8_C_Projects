#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
mkdir -p "$TMP/unit"
FLAGS=(-std=c11 -Wall -Wextra -Wpedantic -Werror -g -O1 -fsanitize=undefined -fno-sanitize-recover=all)
gcc "${FLAGS[@]}" "$ROOT/simulador.c" "$ROOT/tests/test_simulador.c" -o "$TMP/unit-tests"
(cd "$TMP/unit" && "$TMP/unit-tests")
gcc "${FLAGS[@]}" "$ROOT/main.c" "$ROOT/simulador.c" -o "$TMP/simulador"
python3 "$ROOT/tests/test_cli.py" "$TMP/simulador"
echo 'PASS: fictional classroom simulator (not official election software)'
