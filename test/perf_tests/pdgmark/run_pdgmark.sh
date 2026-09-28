#!/bin/bash
# Convenience script to run PDGMark from any directory

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PDG_ROOT="$( cd "$SCRIPT_DIR/../../.." && pwd )"

cd "$PDG_ROOT"

MARK_NAME="PDGMark"
for argument in "$@"; do
    if [ "$argument" = "--quick" ]; then MARK_NAME="QuickPDGMark"; fi
done
echo "Running $MARK_NAME from $PDG_ROOT"
echo ""

"${PDG_NODE:-$PDG_ROOT/tools/node}" test/lib/perf_build.js test/perf_tests/pdgmark/pdgmark.js "$@"
PERF_STATUS=$?
if [ "$MARK_NAME" = "QuickPDGMark" ]; then exit "$PERF_STATUS"; fi

# Check if run was successful
if [ "$PERF_STATUS" -eq 0 ]; then
    echo ""
    echo "=========================================="
    echo "PDGMark Complete!"
    echo "=========================================="
    
    # Show quick summary if results exist
    if [ -f test/perf_tests/pdgmark/pdgmark_results.json ]; then
        echo ""
        echo "Results saved to: test/perf_tests/pdgmark/pdgmark_results.json"
        
        # Extract composite score using node
        if command -v node &> /dev/null; then
            SCORE=$(node -e "console.log(require('./test/perf_tests/pdgmark/pdgmark_results.json').compositeScore)")
            echo "Composite Score: $SCORE"
        fi
        
        echo ""
        echo "To save as baseline:"
        echo "  cp test/perf_tests/pdgmark/pdgmark_results.json \\"
        echo "     test/perf_tests/pdgmark/pdgmark_baseline.json"
        echo ""
        echo "To compare with baseline:"
        echo "  node test/perf_tests/pdgmark/compare_results.js"
        echo ""
    fi
else
    echo ""
    echo "PDGMark failed. Check error messages above."
    exit 1
fi

