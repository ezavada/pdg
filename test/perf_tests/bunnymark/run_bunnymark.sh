#!/bin/bash
# Quick script to run Bunnymark from anywhere in the project

# Get the directory where this script lives
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Get PDG root (three levels up from test/perf_tests/bunnymark)
PDG_ROOT="$SCRIPT_DIR/../../.."

# Change to PDG root
cd "$PDG_ROOT"

# Run the benchmark
MARK_NAME="BunnyMark"
for argument in "$@"; do
    if [ "$argument" = "--quick" ]; then MARK_NAME="QuickBunnyMark"; fi
done
echo "Running $MARK_NAME from $PDG_ROOT"
"${PDG_NODE:-$PDG_ROOT/tools/node}" test/lib/perf_build.js test/perf_tests/bunnymark/bunnymark.js "$@"
PERF_STATUS=$?
if [ "$PERF_STATUS" -ne 0 ] || [ "$MARK_NAME" = "QuickBunnyMark" ]; then exit "$PERF_STATUS"; fi

# Show results if they exist
if [ -f test/perf_tests/bunnymark/bunnymark_results.json ]; then
    echo ""
    echo "Results saved. Key metrics:"
    cat test/perf_tests/bunnymark/bunnymark_results.json | grep -A 3 '"performance"' | grep -E '(maxBunniesAt60FPS|averageFPS)'
fi

