#!/usr/bin/env python3
"""Validate Code::Blocks .cbp source references and compile/link with GCC/MinGW."""
import argparse
import json
from pathlib import Path
import subprocess
import tempfile
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
PROJECTS = (
    "Controle_Academico", "Dois_Vetores_Ordenacao", "EDB_SL2_Desafio_1",
    "busca_linear_binaria", "gerador_nomes_aleatorios", "lista_linear_1",
    "lista_nomes_masculinos", "listas_encadeadas", "ordenacao",
    "registro_eleitores", "urna_eletronica",
)

def build(name, tmp):
    folder = ROOT / name
    project_files = list(folder.glob("*.cbp"))
    if len(project_files) != 1:
        raise RuntimeError("expected exactly one CodeBlocks .cbp")
    root = ET.parse(project_files[0]).getroot()
    units = [unit.get("filename") for unit in root.findall(".//Unit")]
    if not units or any(not x for x in units):
        raise RuntimeError("missing project unit")
    paths = [folder / u.replace("\\", "/") for u in units]
    missing = [str(p) for p in paths if not p.is_file()]
    if missing:
        raise RuntimeError("missing files: " + repr(missing))
    sources = [p for p in paths if p.suffix.lower() == ".c"]
    if not sources:
        raise RuntimeError("no C source units")
    exe = tmp / (name + ".exe")
    cmd = ["gcc", "-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Werror",
           *(str(p) for p in sources), "-o", str(exe)]
    result = subprocess.run(cmd, text=True, capture_output=True, timeout=90)
    if result.returncode or not exe.exists():
        raise RuntimeError("gcc/link failed: " + result.stderr[-2200:])
    return {"project": name, "status": "PASS", "cbp": project_files[0].name,
            "units": units, "sources": len(sources), "exe_bytes": exe.stat().st_size}

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--report", required=True, type=Path)
    args = parser.parse_args()
    args.report.parent.mkdir(parents=True, exist_ok=True)
    results = []
    with tempfile.TemporaryDirectory(prefix="cbp-build-") as d:
        for name in PROJECTS:
            try:
                row = build(name, Path(d))
            except (RuntimeError, ET.ParseError, subprocess.TimeoutExpired) as e:
                row = {"project": name, "status": "FAIL", "error": str(e)}
            results.append(row)
            print(row["status"], name, row.get("error", "")[:200], flush=True)
    args.report.write_text(json.dumps(results, indent=2, ensure_ascii=False)+"\n",
                           encoding="utf-8")
    passed = sum(x["status"] == "PASS" for x in results)
    print(f"CodeBlocks UCRT64 compilations: {passed}/{len(results)} PASS")
    if passed != len(results):
        raise SystemExit(1)

if __name__ == "__main__":
    main()
