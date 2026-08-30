#!/usr/bin/env bash

set -euo pipefail

case "$(uname -s)" in
    Darwin)
        SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
        "$SCRIPT_DIR/release-macos.sh" "$@"
        exec "$SCRIPT_DIR/release-emscripten.sh" "$@"
        ;;
    MINGW*|MSYS*|CYGWIN*)
        WINDOWS_ARGS=()
        while [[ $# -gt 0 ]]; do
            case "$1" in
                --tag)
                    WINDOWS_ARGS+=("-Tag" "$2")
                    shift 2
                    ;;
                --configure)
                    WINDOWS_ARGS+=("-Configure")
                    shift
                    ;;
                --output-dir)
                    WINDOWS_ARGS+=("-OutputDirectory" "$2")
                    shift 2
                    ;;
                *)
                    WINDOWS_ARGS+=("$1")
                    shift
                    ;;
            esac
        done
        exec powershell.exe -NoProfile -ExecutionPolicy Bypass \
            -File "$(cd "$(dirname "$0")" && pwd)/release-windows.ps1" \
            "${WINDOWS_ARGS[@]}"
        ;;
    *)
        echo "PDG release assets are currently supported only on macOS and Windows." >&2
        exit 1
        ;;
esac
