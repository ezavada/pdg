#!/bin/bash

# PDG DTrace Profiling Script
# This script makes it easy to run DTrace profiling on PDG

echo "PDG DTrace Profiling Tool"
echo "========================="
echo ""

# Check if we're running as root (required for DTrace)
if [ "$EUID" -ne 0 ]; then
    echo "Error: DTrace requires root privileges"
    echo "Please run with: sudo $0"
    exit 1
fi

# Check if DTrace is available
if ! command -v dtrace &> /dev/null; then
    echo "Error: DTrace not found. This script requires macOS."
    exit 1
fi

echo "Choose profiling mode:"
echo "1. Full profile (comprehensive monitoring)"
echo "2. Hitch detection (focused on frame drops)"
echo "3. Simple hitch detection (basic monitoring)"
echo "4. Basic monitoring (guaranteed to work)"
echo "5. Custom profiling"
echo ""

read -p "Enter your choice (1-5): " choice

case $choice in
    1)
        echo "Starting full PDG profiling..."
        echo "Run your PDG application in another terminal, then press Ctrl+C to stop"
        echo ""
        dtrace -s tools/dtrace-pdg-profile.d
        ;;
    2)
        echo "Starting hitch detection..."
        echo "First, start your PDG application in another terminal"
        echo "Then enter the PDG process ID when prompted"
        echo ""
        read -p "Enter PDG process ID: " pdg_pid
        
        if [ -z "$pdg_pid" ]; then
            echo "Error: No process ID provided"
            exit 1
        fi
        
        # Check if the process exists
        if ! ps -p "$pdg_pid" > /dev/null 2>&1; then
            echo "Error: Process $pdg_pid not found"
            echo "Make sure PDG is running and use the correct PID"
            exit 1
        fi
        
        echo "Monitoring process $pdg_pid for hitches..."
        echo "Press Ctrl+C to stop"
        echo ""
        dtrace -s tools/dtrace-pdg-hitches.d -p "$pdg_pid"
        ;;
    3)
        echo "Starting simple hitch detection..."
        echo "First, start your PDG application in another terminal"
        echo "Then enter the PDG process ID when prompted"
        echo ""
        read -p "Enter PDG process ID: " pdg_pid
        
        if [ -z "$pdg_pid" ]; then
            echo "Error: No process ID provided"
            exit 1
        fi
        
        # Check if the process exists
        if ! ps -p "$pdg_pid" > /dev/null 2>&1; then
            echo "Error: Process $pdg_pid not found"
            echo "Make sure PDG is running and use the correct PID"
            exit 1
        fi
        
        echo "Monitoring process $pdg_pid for hitches (simple mode)..."
        echo "Press Ctrl+C to stop"
        echo ""
        dtrace -s tools/dtrace-pdg-simple.d -p "$pdg_pid"
        ;;
    4)
        echo "Starting basic monitoring..."
        echo "First, start your PDG application in another terminal"
        echo "Then enter the PDG process ID when prompted"
        echo ""
        read -p "Enter PDG process ID: " pdg_pid
        
        if [ -z "$pdg_pid" ]; then
            echo "Error: No process ID provided"
            exit 1
        fi
        
        # Check if the process exists
        if ! ps -p "$pdg_pid" > /dev/null 2>&1; then
            echo "Error: Process $pdg_pid not found"
            echo "Make sure PDG is running and use the correct PID"
            exit 1
        fi
        
        echo "Monitoring process $pdg_pid (basic mode)..."
        echo "Press Ctrl+C to stop"
        echo ""
        dtrace -s tools/dtrace-pdg-basic.d -p "$pdg_pid"
        ;;
    5)
        echo "Custom profiling options:"
        echo "1. Monitor specific system calls"
        echo "2. Monitor memory allocation patterns"
        echo "3. Monitor file I/O operations"
        echo "4. Monitor OpenGL operations"
        echo ""
        read -p "Enter custom choice (1-4): " custom_choice
        
        case $custom_choice in
            1)
                echo "Monitoring system calls..."
                echo "Enter PDG process ID:"
                read -p "PID: " pdg_pid
                dtrace -n 'syscall:::entry /pid == $target/ { @syscalls[probefunc] = count(); } tick-10sec { printa(@syscalls); }' -p "$pdg_pid"
                ;;
            2)
                echo "Monitoring memory allocation..."
                echo "Enter PDG process ID:"
                read -p "PID: " pdg_pid
                dtrace -n 'pid$target:libsystem_malloc.dylib:malloc:entry { @allocations[arg0] = quantize(arg0); } tick-10sec { printa(@allocations); }' -p "$pdg_pid"
                ;;
            3)
                echo "Monitoring file I/O..."
                echo "Enter PDG process ID:"
                read -p "PID: " pdg_pid
                dtrace -n 'syscall::open:entry, syscall::read:entry, syscall::write:entry /pid == $target/ { @io[probefunc] = count(); } tick-10sec { printa(@io); }' -p "$pdg_pid"
                ;;
            4)
                echo "Monitoring OpenGL operations..."
                echo "Enter PDG process ID:"
                read -p "PID: " pdg_pid
                dtrace -n 'pid$target:libGL.dylib:*:entry { @gl[probefunc] = count(); } tick-10sec { printa(@gl); }' -p "$pdg_pid"
                ;;
            *)
                echo "Invalid choice"
                exit 1
                ;;
        esac
        ;;
    *)
        echo "Invalid choice"
        exit 1
        ;;
esac
