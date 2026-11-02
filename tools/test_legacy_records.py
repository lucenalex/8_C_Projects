#!/usr/bin/env python3
"""Deterministic end-to-end CLI tests with synthetic data and isolated temp files."""
from pathlib import Path
import os
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]

SOURCES = {
    "nomes": "lista_nomes_masculinos/main.c",
    "gerador": "gerador_nomes_aleatorios/main.c",
    "registro": "registro_eleitores/main.c",
    "academico": "Controle_Academico/main.c",
}

def run(binary, input_text, cwd, expected=0):
    p = subprocess.run([str(binary)], input=input_text, cwd=cwd, text=True,
                       capture_output=True, timeout=8)
    assert p.returncode == expected, (
        f"{binary.name}: return {p.returncode} != {expected}\n"
        f"stderr: {p.stderr[-1500:]}\nstdout: {p.stdout[-1500:]}"
    )
    return p.stdout, p.stderr

def ensure(text, *expected):
    for needle in expected:
        assert needle in text, f"Missing {needle!r}; tail={text[-1200:]!r}"

def compile_all(tempdir):
    binaries = {}
    for name, source in SOURCES.items():
        binary = tempdir / f'program_{name}'
        cmd = ["gcc", "-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Werror",
               "-g", "-fsanitize=undefined", "-fno-sanitize-recover=all",
               str(ROOT / source), "-o", str(binary)]
        p = subprocess.run(cmd, text=True, capture_output=True, timeout=20)
        assert p.returncode == 0, f"{name}: GCC failed\n{p.stderr}"
        binaries[name] = binary
    return binaries

def test_nomes(binary, base):
    d = base / "nomes"; d.mkdir()
    path = d / "nomes_masculinos.bin"
    out, _ = run(binary, "", d)
    ensure(out, "Nenhum nome cadastrado")
    assert not path.exists()
    out, _ = run(binary, "Ana\n1\nBia\n0\n", d)
    ensure(out, "2 nomes gravados", "nome[0]: Ana", "nome[1]: Bia")
    raw = path.read_bytes()
    assert len(raw) == 30 and raw[:4] == b"Ana\x00" and raw[15:19] == b"Bia\x00"
    lines = ["N" * 300, "Nome", "0"]
    out, _ = run(binary, "\n".join(lines) + "\n", d)
    ensure(out, "Nome muito longo", "1 nomes gravados")
    assert len(path.read_bytes()) == 15
    entries = []
    for i in range(20):
        entries.append(f"Nome{i:02d}")
        if i < 19:
            entries.append("1")
    out, _ = run(binary, "\n".join(entries) + "\n", d)
    ensure(out, "20 nomes gravados")
    assert len(path.read_bytes()) == 300
    print("PASS nomes: EOF, 2 registros binarios, overflow e capacidade 20")

def test_gerador(binary, base):
    d = base / "gerador"; d.mkdir()
    target = d / "exemplo.txt"
    out, _ = run(binary, "", d)
    ensure(out, "nenhum arquivo alterado")
    assert not target.exists()
    out, err = run(binary, "A" * 300 + "\n", d, expected=1)
    ensure(err, "Nome muito longo")
    assert not target.exists()
    out, err = run(binary, "\n", d, expected=1)
    ensure(err, "Nome vazio")
    assert not target.exists()
    target.write_text("Anterior\n", encoding="utf-8")
    out, _ = run(binary, "Ana\n", d)
    ensure(out, "Anterior", "Ana")
    out, _ = run(binary, "Bia\n", d)
    ensure(out, "Anterior", "Ana", "Bia")
    assert target.read_text(encoding="utf-8") == "Anterior\nAna\nBia\n"
    print("PASS gerador: sem truncamento, preservacao, append e leitura")

def test_registro(binary, base):
    d = base / "registro"; d.mkdir()
    data = "\n".join([
        "invalid", "1", "10", "Ana", "TEST",
        "1", "10", "1", "20", "Bia", "DEMO", "3",
        "2", "10", "3", "2", "10", "4"
    ]) + "\n"
    out, _ = run(binary, data, d)
    ensure(out, "Opção inválida", "Registro incluído",
           "Código inválido ou já cadastrado", "10 | Ana | TEST",
           "20 | Bia | DEMO", "Código não encontrado.")
    assert out.count("10 | Ana | TEST") == 1
    assert out.count("20 | Bia | DEMO") == 2
    # The long input must not leave a tail interpreted as a menu selection.
    data = "1\n31\n" + "X" * 300 + "\n3\n4\n"
    out, _ = run(binary, data, d)
    ensure(out, "Texto vazio ou maior que o limite")
    assert "31 |" not in out
    assert not list(d.iterdir())
    print("PASS registro: inserir, duplicata, listar, excluir e entrada longa")

def test_academico(binary, base):
    d = base / "academico"; d.mkdir()
    data = "\n".join([
        "4", "1", "Alice", "2", "1", "1",
        "3", "1", "1", "11", "8.5",
        "4", "1", "2", "999", "5"
    ]) + "\n"
    out, _ = run(binary, data, d)
    ensure(out, "Cadastre um aluno primeiro",
           "Matrícula: 1", "Matrícula realizada.",
           "Média inválida.", "Média geral: 8.50",
           "Matrícula inexistente.")
    names = []
    for i in range(30):
        names.extend(["1", f"Aluno{i:02d}"])
    names.extend(["1", "5"])
    out, _ = run(binary, "\n".join(names) + "\n", d)
    ensure(out, "Matrícula: 30", "Limite de 30 alunos atingido.")
    assert out.count("Matrícula: ") == 30
    data = "1\n" + "X" * 300 + "\n1\nAna\n" + "X" * 300 + "\n5\n"
    out, _ = run(binary, data, d)
    ensure(out, "Nome vazio ou longo demais.", "Matrícula: 1",
           "Entrada muito longa")
    assert not list(d.iterdir())
    print("PASS academico: notas, boletim, faltantes, capacidade e entradas longas")

def main():
    with tempfile.TemporaryDirectory(prefix="cpp-regressions-") as path:
        base = Path(path)
        binaries = compile_all(base)
        test_nomes(binaries["nomes"], base)
        test_gerador(binaries["gerador"], base)
        test_registro(binaries["registro"], base)
        test_academico(binaries["academico"], base)
    print("PASS: 4 exercicios C com UBSan e dados ficticios")

if __name__ == "__main__":
    main()
