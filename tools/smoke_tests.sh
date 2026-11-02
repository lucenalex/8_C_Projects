#!/usr/bin/env bash
# Fixed-input regression checks; the only sources compiled and executed are listed below.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
cd "$TMP"
CC=(gcc -std=c11 -Wall -Wextra -Wpedantic -fsanitize=undefined -fno-sanitize-recover=all)
"${CC[@]}" "$ROOT/Dois_Vetores_Ordenacao/main.c" -o dois
printf '2\n8\n1\n7\n3\n2\n6\n5\n4\n4\n6\n7\n' | timeout 5s ./dois > dois.log
grep -q 'Valor 6 encontrado na posição 5' dois.log

"${CC[@]}" "$ROOT/Controle_Academico/main.c" -o academico
printf '1\nAlice\n2\n1\n1\n3\n1\n1\n8.5\n4\n1\n5\n' | timeout 5s ./academico > academico.log
grep -q 'Média geral: 8.50' academico.log

"${CC[@]}" "$ROOT/Controle_Academico/exemplo2.c" -o funcionarios
printf 'Ana\n1500\nBia\n1800\nCaio\n2200\n' | timeout 5s ./funcionarios > funcionarios.log
grep -q 'Caio' funcionarios.log

"${CC[@]}" "$ROOT/gerador_nomes_aleatorios/main.c" -o nomes
printf 'Teste\n' | timeout 5s ./nomes > nomes.log
grep -q '^Teste$' exemplo.txt

"${CC[@]}" "$ROOT/registro_eleitores/main.c" -o registros
printf '1\n1\nAlice\nTEST\n3\n2\n1\n4\n' | timeout 5s ./registros > registros.log
grep -q '1 | Alice | TEST' registros.log

echo 'PASS: 5 smoke tests C with UBSan'
