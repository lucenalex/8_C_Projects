#!/usr/bin/env python3
"""Six isolated legacy demonstrations; synthetic inputs, no legacy binaries.

Compiles from current sources and runs ONLY these explicitly reviewed examples.
All files are written under TemporaryDirectory, never repository working tree.
"""
from pathlib import Path
import subprocess
import tempfile
import sys

ROOT = Path(__file__).resolve().parents[1]

def compile_one(folder, name, kind):
    src = ROOT / name / ("main.f90" if kind == "fortran" else "main.c")
    dest = folder / ("bin_" + name)
    if kind == "fortran":
        command = ["gfortran", "-std=f2018", "-Wall", "-Wextra", "-Wpedantic",
                   "-Werror", "-fcheck=all", str(src), "-o", str(dest)]
    else:
        command = ["gcc", "-std=c11", "-Wall", "-Wextra", "-Wpedantic",
                   "-Werror", "-g", "-O1", "-fsanitize=undefined",
                   "-fno-sanitize-recover=all", str(src), "-o", str(dest)]
    p = subprocess.run(command, text=True, capture_output=True, timeout=30)
    if p.returncode:
        raise AssertionError(f"Compilation {name}: {p.stderr[-3000:]}")
    return dest

def run(binary, *args, stdin="", cwd=None, exit_code=0):
    p = subprocess.run([str(binary), *args], input=stdin,
                       text=True, encoding="utf-8", errors="replace",
                       capture_output=True, cwd=cwd, timeout=12)
    assert p.returncode == exit_code, (
        f"{binary.name} exit={p.returncode}, expected={exit_code}\n"
        f"stdout={p.stdout[-1300:]}\nstderr={p.stderr[-1300:]}")
    return p.stdout, p.stderr

def test_hello(binfile, tmp):
    out, _ = run(binfile, cwd=tmp)
    assert out.strip() == "Hello world!"
    print("PASS: EDB_AULA_2022_11_09 hello world")

def test_minmax(binfile, tmp):
    out, _ = run(binfile, stdin="5\n3 -8 7 12 0\n",cwd=tmp)
    assert "componentes e: -8." in out and "componentes e: 12." in out
    out, _ = run(binfile, stdin="1\n-2147483648\n",cwd=tmp)
    assert "componentes e: -2147483648." in out
    out, _ = run(binfile, stdin="3\n5 5 5\n",cwd=tmp)
    assert "componentes e: 5." in out
    for data in ("0\n", "-3\n", "100001\n", "abc\n", "3\n1 2\n", "1\nword\n"):
        _, err = run(binfile, stdin=data, cwd=tmp,exit_code=1)
        assert "invalida" in err.lower()
    print("PASS: MinMaxFuction numeric limits, equality and invalid input")

def test_search(binfile,tmp):
    for v in ("14", "27", "63", "92"):
        out,_=run(binfile,v,cwd=tmp)
        assert "Dado encontrado!" in out
    for v in ("0","15","100","-1"):
        out,_=run(binfile,v,cwd=tmp)
        assert "Dado nao encontrado!" in out
    _,err=run(binfile,"invalid",cwd=tmp,exit_code=2)
    assert "Alvo nao e inteiro" in err
    print("PASS: busca_binaria_1 first/middle/last, missing, malformed target")

def test_file_sort(binfile,tmp):
    out,_=run(binfile,cwd=tmp)
    assert "Ordenacoes concordam: SIM" in out and not list(tmp.glob("*.txt"))
    target=tmp/"numeros.txt"
    out,_=run(binfile,"--count","30","--seed","29","--output","numeros.txt",cwd=tmp)
    assert "Ordenacoes concordam: SIM" in out
    before=target.read_bytes()
    rows=target.read_text().strip().splitlines()
    assert len(rows)==30 and all(0<=int(x)<1000000 for x in rows)
    _,err=run(binfile,"--count","30","--output","numeros.txt",cwd=tmp,exit_code=1)
    assert "Arquivo nao criado" in err and before==target.read_bytes()
    for args in (("--count","0"),("--count","10001"),("--count","3000"),
                 ("--bogus",),("--seed","-3")):
        _,err=run(binfile,*args,cwd=tmp,exit_code=2)
        assert err.strip()
    print("PASS: criar_arquivo 3 sorts, output, no overwrite and quadratic guard")

def test_fortran(binfile,tmp):
    out,_=run(binfile,stdin="3\n2.5\n(1.0,-1.0)\nTeste\n",cwd=tmp)
    assert "Valor lido:" in out and "Parte real" in out
    out,_=run(binfile,stdin="invalid\n",cwd=tmp,exit_code=1)
    assert "Entrada invalida para x." in out
    out,_=run(binfile,stdin="3\n2.5\nsem_complexo\n",cwd=tmp,exit_code=1)
    assert "Entrada invalida para u." in out
    print("PASS: example Fortran numeric, complex, string and invalid input")

def test_alias(binfile,tmp):
    out,_=run(binfile,cwd=tmp)
    assert "20 ponteiros compartilham o mesmo texto: Exemplo" in out
    print("PASS: racunho memory ownership / 20 aliases")

def main():
    with tempfile.TemporaryDirectory(prefix="legacy-six-tests-") as tmp_name:
        tmp=Path(tmp_name)
        jobs=(
            ("EDB_AULA_2022_11_09","c",test_hello),
            ("MinMaxFuction","c",test_minmax),
            ("busca_binaria_1","c",test_search),
            ("criar_arquivo","c",test_file_sort),
            ("example","fortran",test_fortran),
            ("racunho","c",test_alias),
        )
        for name,kind,test in jobs:
            path=compile_one(tmp,name,kind)
            test(path,tmp)
    print("PASS: 6 legacy examples, data kept in temporary directory")

if __name__=="__main__":
    main()
