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
  relative=${file#"$ROOT"/}
  # Explicitly classify non-source and platform-dependent files.
  # These are not PASS and will not count as validated.
  if [[ "$lang" == c && "$relative" == "main.c" ]] &&
     [[ "$(LC_ALL=C tr -d '\000' < "$file" | wc -c)" -eq 0 ]]; then
    result=SKIP_NULL_PLACEHOLDER
    printf 'Historical placeholder: file consists exclusively of NUL bytes; source preserved.\n' > "$log"
  elif [[ "$lang" == c && "$relative" == "urna_eletronica/Untitled1.c" ]] &&
       [[ "$(LC_ALL=C tr -d '[:space:]' < "$file" | wc -c)" -eq 0 ]]; then
    result=SKIP_EMPTY_PLACEHOLDER
    printf 'Historical empty placeholder; preserved, not a compilable source.\n' > "$log"
  elif [[ "$lang" == fortran && "$relative" == "temp_convertion.rtf.f08" ]] &&
     head -c 6 "$file" | grep -qF '{\rtf1'; then
    result=SKIP_RTF_DOCUMENT
    printf 'File is RTF, not Fortran source.\n' > "$log"
  elif [[ "$lang" == fortran && "$relative" == "test/Aec32BitAppServer57.f90" ]]; then
    result=SKIP_WINDOWS_COM
    printf 'Requires Intel Fortran/Windows COM modules.\n' > "$log"
  elif ! command -v "$compiler" >/dev/null 2>&1; then
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
    extra_flags=()
    # Legacy source with misleading .f suffix contains free-format code.
    if [[ "$relative" == "test/test.f03.f" ]]; then extra_flags=(-ffree-form); fi
    if (cd "$work" && gfortran -std=f2018 -Wall -Wextra -fsyntax-only -J "$work" -I "$(dirname "$file")" "${extra_flags[@]}" "$file") > "$log" 2>&1; then
      result=PASS; passed=$((passed+1))
    else
      result=FAIL; failed=$((failed+1))
    fi
  fi
  wc=$(grep -ci 'warning:' "$log" || true)
  warnings=$((warnings+wc))
  safe=${relative//\"/\"\"}
  printf '"%s",%s,%s,%s,%s\n' "$safe" "$lang" "$result" "$wc" "$id.log" >> "$REPORT"
done < <(find "$ROOT" -type f \( -iname '*.c' -o -iname '*.f' -o -iname '*.for' -o -iname '*.f77' -o -iname '*.f03' -o -iname '*.f08' -o -iname '*.f90' -o -iname '*.f95' -o -iname '*.f18' \) ! -path '*/.git/*' -print0 | sort -z)
printf 'Checked: %s | PASS: %s | FAIL: %s | Missing compiler: %s | Warnings: %s\nReport: %s\n' "$checked" "$passed" "$failed" "$missing" "$warnings" "$REPORT" >&2
# Syntax checks do NOT prove linking, behavior, binary identity or Windows/Intel compatibility.
if ((failed || missing)); then exit 1; fi
