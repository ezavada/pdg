#!/bin/bash

# Alternative PDG Profiling Script
# This script uses built-in macOS tools to profile PDG without requiring DTrace

echo "PDG Alternative Profiling Tool"
echo "=============================="
echo ""

# Check if we're in the right directory
if [ ! -f "./pdg" ]; then
    echo "Error: ./pdg executable not found. Please run this from the pdg-devel directory."
    exit 1
fi

echo "Choose profiling method:"
echo "1. Activity Monitor profiling"
echo "2. Sample-based profiling"
echo "3. Memory usage monitoring"
echo "4. CPU usage monitoring"
echo "5. Combined profiling"
echo ""

read -p "Enter your choice (1-5): " choice

case $choice in
    1)
        echo "Starting Activity Monitor profiling..."
        echo "1. Start your PDG application"
        echo "2. Open Activity Monitor (Applications/Utilities/Activity Monitor)"
        echo "3. Find the pdg process and monitor CPU/Memory usage"
        echo "4. Look for spikes in CPU usage that correlate with frame drops"
        echo ""
        echo "Press Enter when ready to continue..."
        read
        ;;
    2)
        echo "Starting sample-based profiling..."
        echo "First, start your PDG application in another terminal"
        echo "Then enter the PDG process ID when prompted"
        echo ""
        read -p "Enter PDG process ID: " pdg_pid
        
        if [ -z "$pdg_pid" ]; then
            echo "Error: No process ID provided"
            exit 1
        fi
        
        echo "Taking samples every 1 second for 30 seconds..."
        echo "Press Ctrl+C to stop early"
        echo ""
        
        for i in {1..30}; do
            if ! ps -p "$pdg_pid" > /dev/null 2>&1; then
                echo "Process $pdg_pid no longer running"
                break
            fi
            
            echo "Sample $i:"
            ps -p "$pdg_pid" -o pid,ppid,%cpu,%mem,time,command
            echo ""
            sleep 1
        done
        ;;
    3)
        echo "Starting memory usage monitoring..."
        echo "First, start your PDG application in another terminal"
        echo "Then enter the PDG process ID when prompted"
        echo ""
        read -p "Enter PDG process ID: " pdg_pid
        
        if [ -z "$pdg_pid" ]; then
            echo "Error: No process ID provided"
            exit 1
        fi
        
        echo "Monitoring memory usage every 2 seconds..."
        echo "Press Ctrl+C to stop"
        echo ""
        
        while true; do
            if ! ps -p "$pdg_pid" > /dev/null 2>&1; then
                echo "Process $pdg_pid no longer running"
                break
            fi
            
            memory_info=$(ps -p "$pdg_pid" -o rss,vsz,%mem --no-headers)
            echo "$(date '+%H:%M:%S') - Memory: $memory_info"
            sleep 2
        done
        ;;
    4)
        echo "Starting CPU usage monitoring..."
        echo "First, start your PDG application in another terminal"
        echo "Then enter the PDG process ID when prompted"
        echo ""
        read -p "Enter PDG process ID: " pdg_pid
        
        if [ -z "$pdg_pid" ]; then
            echo "Error: No process ID provided"
            exit 1
        fi
        
        echo "Monitoring CPU usage every 1 second..."
        echo "Press Ctrl+C to stop"
        echo ""
        
        while true; do
            if ! ps -p "$pdg_pid" > /dev/null 2>&1; then
                echo "Process $pdg_pid no longer running"
                break
            fi
            
            cpu_info=$(ps -p "$pdg_pid" -o %cpu,time --no-headers)
            echo "$(date '+%H:%M:%S') - CPU: $cpu_info"
            sleep 1
        done
        ;;
    5)
        echo "Starting combined profiling..."
        echo "First, start your PDG application in another terminal"
        echo "Then enter the PDG process ID when prompted"
        echo ""
        read -p "Enter PDG process ID: " pdg_pid
        
        if [ -z "$pdg_pid" ]; then
            echo "Error: No process ID provided"
            exit 1
        fi
        
        echo "Monitoring CPU, Memory, and taking samples..."
        echo "Press Ctrl+C to stop"
        echo ""
        
        while true; do
            if ! ps -p "$pdg_pid" > /dev/null 2>&1; then
                echo "Process $pdg_pid no longer running"
                break
            fi
            
            echo "=== $(date '+%H:%M:%S') ==="
            ps -p "$pdg_pid" -o pid,%cpu,%mem,rss,vsz,time,command --no-headers
            echo ""
            sleep 2
        done
        ;;
    *)
        echo "Invalid choice"
        exit 1
        ;;
esac
