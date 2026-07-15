#!/bin/bash
# Quick script to run Bunnymark from anywhere in the project

# Get the directory where this script lives
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Get PDG root (two levels up from test/perf)
PDG_ROOT="$SCRIPT_DIR/../.."

# Change to PDG root
cd "$PDG_ROOT"

# Run the benchmark
echo "Running Bunnymark from $PDG_ROOT"
./pdg test/perf/bunnymark.js "$@"

# Show results if they exist
if [ -f test/perf/bunnymark_results.json ]; then
    echo ""
    echo "Results saved. Key metrics:"
    cat test/perf/bunnymark_results.json | grep -A 3 '"performance"' | grep -E '(maxBunniesAt60FPS|averageFPS)'
fi

