#!/bin/bash
# Quick test runner for shape fill tests

cd "$(dirname "$0")/../.."

echo "======================================"
echo "PDG Shape Fill & Transform Test Suite"
echo "======================================"
echo ""

case "$1" in
    simple)
        echo "Running simple diagnostic test..."
        ./pdg test/ui_tests/shape_fill_test_simple.js
        ;;
    wait)
        echo "Running full test suite (manual mode)..."
        echo "Press SPACE to advance, ESC to quit"
        ./pdg test/ui_tests/shape_fill_test.js --wait
        ;;
    auto)
        echo "Running full test suite (auto mode - 30s per shape)..."
        echo "Press any key to advance early, ESC to quit"
        ./pdg test/ui_tests/shape_fill_test.js
        ;;
    rect|quad|circle|ellipse|roundrect|pentagon|star|pentagram|complex|spiral|hourglass|selfintersect)
        echo "Testing shape: $1"
        ./pdg test/ui_tests/shape_fill_test.js --shape "$1"
        ;;
    *)
        echo "Usage: $0 {simple|wait|auto|<shape>}"
        echo ""
        echo "Modes:"
        echo "  simple     - Run simple 8-rectangle diagnostic test"
        echo "  wait       - Run full test, manual advance with SPACE"
        echo "  auto       - Run full test, auto-advance every 30s"
        echo ""
        echo "Shapes:"
        echo "  rect, quad, circle, ellipse, roundrect"
        echo "  pentagon, star, pentagram, complex, spiral"
        echo "  hourglass, selfintersect"
        echo ""
        echo "Examples:"
        echo "  $0 simple         # Quick diagnostic"
        echo "  $0 wait           # Manual stepping"
        echo "  $0 auto           # Full auto test"
        echo "  $0 rect           # Test just rectangles"
        exit 1
        ;;
esac

