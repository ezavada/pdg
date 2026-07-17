#!/bin/bash

ensure_repo_submodule() {
    local repo_root="$1"
    local submodule_path="$2"
    local sentinel_path="$3"
    local display_name="${4:-$2}"
    local sentinel_full="$repo_root/$sentinel_path"

    if [ -e "$sentinel_full" ]; then
        return 0
    fi

    echo "-- $display_name is not checked out at $submodule_path"

    if ! command -v git >/dev/null 2>&1; then
        echo "FATAL: git is required to populate $submodule_path."
        echo "Run: git submodule update --init --recursive $submodule_path"
        return 1
    fi

    echo "-- Initializing $display_name from git submodule $submodule_path"
    if ! (cd "$repo_root" && git submodule update --init --checkout --recursive "$submodule_path"); then
        echo "FATAL: unable to populate $submodule_path via git submodule update."
        return 1
    fi

    if [ ! -e "$sentinel_full" ]; then
        echo "FATAL: $display_name is still missing after submodule initialization."
        return 1
    fi

    return 0
}
