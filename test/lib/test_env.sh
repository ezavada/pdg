#!/bin/bash

pdg_test_prepare_env() {
    local mode="$1"
    local platform_name

    if [ -z "$PDG_ROOT" ]; then
        PDG_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
        export PDG_ROOT
    fi

    if [ -z "$mode" ]; then
        mode="client"
    fi

    platform_name="${PDG_TEST_PLATFORM:-$(uname -s | awk '{print tolower($0)}')}"

    export PDG_TEST_MODE="$mode"
    export PDG_TEST_PLATFORM="$platform_name"
    export PDG_TEST_ARTIFACTS_DIR="${PDG_TEST_ARTIFACTS_DIR:-$PDG_ROOT/artifacts/test-results/$PDG_TEST_PLATFORM/$PDG_TEST_MODE}"
    export PDG_TEST_LOG_DIR="${PDG_TEST_LOG_DIR:-$PDG_TEST_ARTIFACTS_DIR/logs}"
    export PDG_TEST_REPORT_DIR="${PDG_TEST_REPORT_DIR:-$PDG_TEST_ARTIFACTS_DIR/reports}"
    export PDG_TEST_TEMP_DIR="${PDG_TEST_TEMP_DIR:-$PDG_TEST_ARTIFACTS_DIR/tmp}"

    mkdir -p "$PDG_TEST_LOG_DIR" "$PDG_TEST_REPORT_DIR" "$PDG_TEST_TEMP_DIR"
}
