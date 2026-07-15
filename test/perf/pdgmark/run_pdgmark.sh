#!/bin/bash
# Convenience script to run PDGMark from any directory

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PDG_ROOT="$( cd "$SCRIPT_DIR/../../.." && pwd )"

cd "$PDG_ROOT"

echo "Running PDGMark from $PDG_ROOT"
echo ""

./pdg test/perf/pdgmark/pdgmark.js

# Check if run was successful
if [ $? -eq 0 ]; then
    echo ""
    echo "=========================================="
    echo "PDGMark Complete!"
    echo "=========================================="
    
    # Show quick summary if results exist
    if [ -f test/perf/pdgmark/pdgmark_results.json ]; then
        echo ""
        echo "Results saved to: test/perf/pdgmark/pdgmark_results.json"
        
        # Extract composite score using node
        if command -v node &> /dev/null; then
            SCORE=$(node -e "console.log(require('./test/perf/pdgmark/pdgmark_results.json').compositeScore)")
            echo "Composite Score: $SCORE"
        fi
        
        echo ""
        echo "To save as baseline:"
        echo "  cp test/perf/pdgmark/pdgmark_results.json \\"
        echo "     test/perf/pdgmark/pdgmark_baseline.json"
        echo ""
        echo "To compare with baseline:"
        echo "  node test/perf/pdgmark/compare_results.js"
        echo ""
    fi
else
    echo ""
    echo "PDGMark failed. Check error messages above."
    exit 1
fi

