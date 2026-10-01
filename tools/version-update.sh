#!/bin/bash
# -------------------------------------------
# version-update.sh
#
# update version number
#
# Written by Ed Zavada, 2012
# Copyright (c) 2012, Dream Rock Studios, LLC
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to permit
# persons to whom the Software is furnished to do so, subject to the
# following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
# NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
# USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# -------------------------------------------

# Update source metadata; generated docs and binaries are refreshed by their builds.
set -euo pipefail
PDG_VERSION_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
if [ "$#" -ne 1 ]; then
    echo "Usage: version-update.sh major.minor.patch" >&2
    exit 1
fi

python3 - "$PDG_VERSION_ROOT" "$1" <<'PYTHON'
from pathlib import Path
import re
import sys

root = Path(sys.argv[1])
version = sys.argv[2]
if not re.fullmatch(r"(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)", version):
    raise SystemExit("Version must have the form major.minor.patch (for example, 1.1.1)")

updates = {"VERSION": version + "\n"}

def replace(name, pattern, value, count=1):
    text = updates.get(name, (root / name).read_text())
    text, found = re.subn(pattern, lambda match: match[1] + value + match[2], text,
                          flags=re.MULTILINE)
    if found != count:
        raise SystemExit(f"Expected {count} version field(s) in {name}, found {found}")
    updates[name] = text

replace("CMakeLists.txt", r"(PROJECT\(PDG VERSION )[^ ]+( LANGUAGES)", version)
replace("src/inc/pdg/version.h", r'(#define PDG_VERSION ")[^"]+("$)', version)
replace("tools/node-pdg/package.json", r'(  "version": ")[^"]+(",$)', version)
for name in ("docs/cxx/Doxyfile", "docs/javascript/Doxyfile", "docs/javascript/Doxyfile-man"):
    replace(name, r"(PROJECT_NUMBER[ \t]*=[ \t]*)[^\n]+($)", "v" + version)
for key in ("CFBundleShortVersionString", "CFBundleVersion"):
    replace("ios/pdg-Info.plist", r"(<key>" + key + r"</key>\s*<string>)[^<]+(</string>)", version)

# Validate all inputs before writing any changes, including stale older versions.
for name, text in updates.items():
    destination = root / name
    if destination.read_text() != text:
        destination.write_text(text)
    print(f"{name}: {version}")
PYTHON
