#!/usr/bin/env python3
"""Read-only provenance audit of tracked PE executables. Never executes a binary.

Rechecks the historical manifest against each original file's Git blob,
SHA-256, PE32+/x86_64/console headers, and CodeBlocks project references.
"""
import argparse
import csv
import datetime as dt
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "MANIFESTO-EXECUTAVEIS-HISTORICOS-2026-11-02.csv"


def inspect_exe(file):
    data = file.read_bytes()
    if len(data) < 256 or data[:2] != b"MZ":
        raise ValueError("missing DOS MZ header")
    pe_offset = struct.unpack_from("<I", data, 0x3c)[0]
    if pe_offset + 128 > len(data) or data[pe_offset:pe_offset+4] != b"PE\0\0":
        raise ValueError("missing or truncated PE header")
    machine = struct.unpack_from("<H", data, pe_offset+4)[0]
    timestamp = struct.unpack_from("<I", data, pe_offset+8)[0]
    optional_size = struct.unpack_from("<H", data, pe_offset+20)[0]
    opt = pe_offset + 24
    if opt + optional_size > len(data):
        raise ValueError("invalid PE optional header size")
    magic = struct.unpack_from("<H", data, opt)[0]
    subsystem = struct.unpack_from("<H", data, opt+68)[0]
    date = dt.datetime.fromtimestamp(timestamp, dt.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    return {
        "machine_hex": f"{machine:04x}",
        "magic_hex": f"{magic:04x}",
        "subsystem": subsystem,
        "coff_time_utc": date,
        "bytes": len(data),
        "sha256": hashlib.sha256(data).hexdigest(),
        "raw": data,
    }


def audit():
    with MANIFEST.open(newline="", encoding="utf-8") as fp:
        rows = list(csv.DictReader(fp))
    if len(rows) != 16 or len({r["path"] for r in rows}) != 16:
        raise ValueError("expected exactly 16 unique historical executables")
    existing = {
        p.relative_to(ROOT).as_posix()
        for p in ROOT.rglob("*.exe")
        if p.is_file()
    }
    if existing != {r["path"] for r in rows}:
        raise ValueError("tracked/existing EXE set differs from manifest")
    result = []
    for row in rows:
        relative = Path(row["path"])
        if relative.is_absolute() or ".." in relative.parts:
            raise ValueError("unsafe path in manifest")
        project = relative.parts[0]
        if relative.as_posix() != f"{project}/bin/Debug/{project}.exe":
            raise ValueError(f"unexpected binary path: {relative}")
        file = ROOT / relative
        meta = inspect_exe(file)
        git_sha = subprocess.run(
            ["git", "-C", str(ROOT), "hash-object", str(relative)],
            check=True, capture_output=True, text=True
        ).stdout.strip()
        checks = {
            "bytes": meta["bytes"] == int(row["size_bytes"]),
            "sha256": meta["sha256"] == row["sha256"],
            "git_blob_sha": git_sha == row["git_blob_sha"],
            "pe_x64_console": meta["machine_hex"] == "8664"
                 and meta["magic_hex"] == "020b" and meta["subsystem"] == 3,
            "coff_timestamp": meta["coff_time_utc"] == row["coff_time_utc"],
        }
        dependency = row["extra_runtime_dependency"]
        if dependency not in ("", "standard"):
            checks["runtime_import_mentioned"] = dependency.encode("ascii").lower() in meta["raw"].lower()
        cbp = ROOT / project / (project + ".cbp")
        checks["project_file"] = cbp.is_file()
        if cbp.is_file():
            root = ET.parse(cbp).getroot()
            outputs = [x.attrib.get("output", "") for x in root.iter("Option")]
            units = [x.attrib.get("filename", "") for x in root.iter("Unit")]
            checks["codeblocks_output"] = f"bin/Debug/{project}" in outputs
            checks["has_source_unit"] = any(x.lower().endswith((".c", ".f90")) for x in units)
        status = "PASS" if all(checks.values()) else "FAIL"
        result.append({
            "path": row["path"], "status": status,
            "size_bytes": meta["bytes"], "sha256": meta["sha256"],
            "git_blob_sha": git_sha, "pe_machine": meta["machine_hex"],
            "coff_timestamp_utc": meta["coff_time_utc"],
            "runtime_dependency_note": dependency,
            "checks": checks
        })
        print(f"{status}: {row['path']} | " +
              ",".join(key for key, ok in checks.items() if not ok), flush=True)
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    result = audit()
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(result, indent=2, ensure_ascii=False)+"\n", encoding="utf-8")
    passed = sum(row["status"] == "PASS" for row in result)
    print(f"STATIC PE AUDIT: {passed}/16 PASS; executable runs: ZERO", flush=True)
    if passed != 16:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
