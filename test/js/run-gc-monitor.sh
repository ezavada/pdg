#!/bin/bash

# GC Monitor Test Scripts
# This script provides different ways to run PDG with GC monitoring

echo "PDG GC Monitor Test Scripts"
echo "=========================="
echo ""

# Check if we're in the right directory
if [ ! -f "./pdg" ]; then
    echo "Error: ./pdg executable not found. Please run this from the pdg-devel directory."
    exit 1
fi

echo "Choose an option:"
echo "1. Run basic GC test (no special flags)"
echo "2. Run GC test with --expose-gc (manual GC control)"
echo "3. Run GC test with --trace-gc (detailed GC logging)"
echo "4. Run GC test with --trace-gc --expose-gc (full monitoring)"
echo "5. Run your main.js with GC monitoring"
echo "6. Run main.js with --expose-gc"
echo "7. Run main.js with --trace-gc"
echo "8. Run main.js with --trace-gc --expose-gc"
echo ""

read -p "Enter your choice (1-8): " choice

case $choice in
    1)
        echo "Running basic GC test..."
        ./pdg test/js/gc-test.js
        ;;
    2)
        echo "Running GC test with --expose-gc..."
        ./pdg --expose-gc test/js/gc-test.js
        ;;
    3)
        echo "Running GC test with --trace-gc..."
        ./pdg --trace-gc test/js/gc-test.js
        ;;
    4)
        echo "Running GC test with full monitoring..."
        ./pdg --trace-gc --expose-gc test/js/gc-test.js
        ;;
    5)
        echo "Running main.js with GC monitoring..."
        ./pdg test/js/main.js
        ;;
    6)
        echo "Running main.js with --expose-gc..."
        ./pdg --expose-gc test/js/main.js
        ;;
    7)
        echo "Running main.js with --trace-gc..."
        ./pdg --trace-gc test/js/main.js
        ;;
    8)
        echo "Running main.js with full monitoring..."
        ./pdg --trace-gc --expose-gc test/js/main.js
        ;;
    *)
        echo "Invalid choice. Exiting."
        exit 1
        ;;
esac
