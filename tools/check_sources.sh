#!/usr/bin/env bash
# Static compiler checks only: never run project executables or change tracked files.
set -uo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT_DIR="${1:-$(mktemp -d "${TMPDIR:-/tmp}/source-check.XXXXXX")}"
mkdir -p -- "$OUT_DIR"
OUT_DIR="$(cd "$OUT_DIR" && pwd)"
REPORT="$OUT_DIR/results.csv"
printf '%s\n' 'source,language,result,warning_count,log_file' > "$REPORT"
checked=0; passed=0; warnings=0; failed=0; missing=0
while IFS= read -r -d '' file; do
  checked=$((checked+1))
  case "${file,,}" in
    *.c) lang=c; compiler=gcc;;
    *) lang=fortran; compiler=gfortran;;
  esac
  id=$(printf '%04d' "$checked")
  log="$OUT_DIR/$id.log"
  work="$OUT_DIR/work-$id"
  mkdir -p -- "$work"
  if ! command -v "$compiler" >/dev/null 2>&1; then
    result=NO_COMPILER
    printf 'Required compiler %s not found\n' "$compiler" > "$log"
    missing=$((missing+1))
  elif [[ "$lang" == c ]]; then
    if (cd "$work" && gcc -std=c11 -Wall -Wextra -Wpedantic -fsyntax-only "$file") > "$log" 2>&1; then
      result=PASS; passed=$((passed+1))
    else
      result=FAIL; failed=$((failed+1))
    fi
  else
    if (cd "$work" && gfortran -std=f2018 -Wall -Wextra -fsyntax-only -J "$work" -I "$(dirname "$file")" "$file") > "$log" 2>&1; then
      result=PASS; passed=$((passed+1))
    else
      result=FAIL; failed=$((failed+1))
    fi
  fi
  wc=$(grep -ci 'warning:' "$log" || true)
  warnings=$((warnings+wc))
  relative=${file#"$ROOT"/}
  safe=${relative//\"/\"\"}
  printf '"%s",%s,%s,%s,%s\n' "$safe" "$lang" "$result" "$wc" "$id.log" >> "$REPORT"
done < <(find "$ROOT" -type f \( -iname '*.c' -o -iname '*.f' -o -iname '*.for' -o -iname '*.f77' -o -iname '*.f03' -o -iname '*.f08' -o -iname '*.f90' -o -iname '*.f95' -o -iname '*.f18' \) ! -path '*/.git/*' -print0 | sort -z)
printf 'Checked: %s | PASS: %s | FAIL: %s | Missing compiler: %s | Warnings: %s\nReport: %s\n' "$checked" "$passed" "$failed" "$missing" "$warnings" "$REPORT" >&2
# Syntax checks do NOT prove linking, behavior, binary identity or Windows/Intel compatibility.
if ((failed || missing)); then exit 1; fi
