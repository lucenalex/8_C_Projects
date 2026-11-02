#!/usr/bin/env python3
"""Patch 16 malformed scanf scansets without transcoding legacy Latin-1 source."""
from pathlib import Path
import argparse
import re

TARGET = Path("EDB_SL2_Desafio_1/main.c")
PATTERN = re.compile(rb'scanf\("([0-9]+)\[\^\\n\]"')

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--apply", action="store_true")
    args = p.parse_args()
    source = TARGET.read_bytes()
    matches = list(PATTERN.finditer(source))
    if len(matches) != 16:
        raise SystemExit(f"Expected 16 malformed input scansets, found {len(matches)}; refusing to edit")
    def replace(m):
        capacity = int(m.group(1))
        if capacity not in (3, 5, 9, 15, 45, 50):
            raise SystemExit("Unexpected destination capacity")
        return b'scanf(" %' + str(capacity - 1).encode("ascii") + b'[^\\n]"'
    revised, n = PATTERN.subn(replace, source)
    if n != 16:
        raise SystemExit("Unexpected substitution count")
    print(f"Safe scanf formats: {n}, bytes {len(source)} -> {len(revised)}")
    if args.apply:
        TARGET.write_bytes(revised)

if __name__ == "__main__":
    main()
