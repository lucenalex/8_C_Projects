#!/usr/bin/env python3
"""Synthetic classroom simulation only; tests execute in a disposable directory."""
import csv
from pathlib import Path
import subprocess
import sys
import tempfile

binary=Path(sys.argv[1]).resolve()
with tempfile.TemporaryDirectory(prefix="urna-demo-") as tmp:
    input_text="\n".join([
        "1",
        "2","1","101",
        "2","1","101",
        "2","2","105",
        "3",
        "5","1",
        "5","4",
        "6","101",
        "4",
        "4",
        "0",
        ""
    ])
    p=subprocess.run([str(binary)],input=input_text,text=True,capture_output=True,
                     cwd=tmp,timeout=10)
    assert p.returncode==0, f"exit={p.returncode} stderr={p.stderr[-1000:]}"
    out=p.stdout
    for text in ("SIMULADOR DIDATICO", "Voto ficticio registrado.",
                 "Eleitor ficticio ja votou.", "TOTAL DE VOTOS: 2",
                 "PARTIDO PBA: 1 votos", "PARTIDO PBB: 1 votos",
                 "Exclusao bloqueada", "Registro ficticio excluido.",
                 "Arquivo eleitores_demo.csv criado", "Falha ao criar CSV"):
        assert text in out, f"missing {text!r} in output tail {out[-1000:]!r}"
    path=Path(tmp)/"eleitores_demo.csv"
    assert path.exists()
    with path.open(encoding="utf-8",newline="") as f:
        rows=list(csv.DictReader(f,delimiter=";"))
    assert len(rows)==199
    by_id={int(r["codigo"]):r for r in rows}
    assert by_id[1]["votou"]=="1" and by_id[2]["votou"]=="1"
    assert 4 not in by_id
    assert rows[0]["nome_ficticio"].startswith("Eleitor ficticio")
    assert path.read_text().startswith("codigo;nome_ficticio;votou\n")
print("PASS: simulator CLI, single-vote rule, results, no-overwrite synthetic CSV")
