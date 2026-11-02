#!/usr/bin/env python3
"""Bounded, synthetic smoke and algorithm tests. Runs only explicitly reviewed sources."""
from pathlib import Path
import subprocess
import tempfile

ROOT=Path(__file__).resolve().parents[1]
def compile_to(out,*paths):
    args=["gcc","-std=c11","-Wall","-Wextra","-Wpedantic","-Werror",
          "-fsanitize=undefined","-fno-sanitize-recover=all","-O1",
          *(str(ROOT/p) for p in paths),"-o",str(out)]
    result=subprocess.run(args,check=False,text=True,capture_output=True,timeout=30)
    assert result.returncode==0, f"GCC failed: {result.stderr}"
def check_run(exe,input="",limit=10):
    r=subprocess.run([str(exe)],input=input,text=True,capture_output=True,timeout=limit)
    assert r.returncode==0, f"exit {r.returncode}: {r.stderr[-1000:]}, stdout={r.stdout[-1500:]}"
    return r.stdout
def contains(text,*needles):
    for x in needles:
        assert x in text, f"Missing {x!r} from {text[-1500:]!r}"
def main():
    with tempfile.TemporaryDirectory(prefix="search-sort-lists-") as dirname:
        tmp=Path(dirname)
        compile_to(tmp/"algos","ordenacao/algoritmos.c","ordenacao/tests/test_algoritmos.c")
        contains(check_run(tmp/"algos"),"PASS: 3 sort algorithms")
        print("PASS algorithms: bubble, selection, insertion, sequential & binary search")
        compile_to(tmp/"sort","ordenacao/main.c","ordenacao/algoritmos.c")
        printout=check_run(tmp/"sort","10\n11\n3\n10\n11\n7\n10\n12\n",limit=10)
        contains(printout,"Busca binaria exige vetor 3 ordenado","Ordenacao concluida.",
                 "Valor nao encontrado.")
        print("PASS sorting CLI: reject unsorted binary search and then sort")
        compile_to(tmp/"linked","listas_encadeadas/lista.c",
                   "listas_encadeadas/tests/test_lista.c")
        contains(check_run(tmp/"linked"),"PASS linked list")
        compile_to(tmp/"linked_cli","listas_encadeadas/main.c",
                   "listas_encadeadas/lista.c")
        contains(check_run(tmp/"linked_cli"),"Contem 23: sim",
                 "Tamanho apos remover 45: 1")
        print("PASS linked list: 1000 nodes, head/middle/tail, missing, duplicates")
        compile_to(tmp/"twovectors","busca_linear_binaria/main.c")
        inp="4\n1\n8\n5\n1\n4\n6\n3\n2\n7\n5\n3\n6\n2\n6\n3\n2\n8\n1\n4\n4\n6\n6\n7\n"
        txt=check_run(tmp/"twovectors",inp)
        contains(txt,"Preencha o vetor correspondente.","Valor encontrado na posicao",
                 "1 2 3 4 5 6 7 8")
        print("PASS two vectors CLI: sorting and search after filling")
        compile_to(tmp/"linear","lista_linear_1/main.c")
        contains(check_run(tmp/"linear","4\n10\n20\n30\n40\n30\n"),"Posicao: 2")
        contains(check_run(tmp/"linear","0\n5\n"),"O dado nao pertence")
        contains(check_run(tmp/"linear","3\n1\n2\n3\n7\n"),"O dado nao pertence")
        print("PASS linear list CLI: found, absent, empty")
        print("PASS ALL SEARCH/SORT/LINKED-LIST TESTS")
if __name__=="__main__":
    main()
