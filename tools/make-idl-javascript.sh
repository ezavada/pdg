#!/bin/bash
# -------------------------------------------
# make-idl-javascript.sh
#
# Uses the C++ preprocessor and bcpp pretty printer
# to convert pdg_js_classes.h/.cpp into pdg_interfaces.h/.cpp
# files. Having the macro expansion be part of the source
# code makes debugging through the bindings much easier.
#
# Written by Ed Zavada, 2012
# Copyright (c) 2012, Dream Rock Studios, LLC
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to permit
# persons to whom the Software is furnished to do so, subject to the
# following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
# NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
# USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# -------------------------------------------

# load pdgrc
_SD=`pwd`;while [ "`pwd`" != '/' ];do { if [ -e ".pdgrc" ];then { source .pdgrc;break; } fi;cd ..; } done;cd $_SD
if [ -z "$PDG_ROOT" ]; then
	echo "FATAL: couldn't source .pdgrc in `pwd` or it's parent directories. Have you run configure yet?"
	exit 1
fi

PDG_BUILD_DIR="$PDG_ROOT/build"
PDG_TOOLS_DIR="$PDG_ROOT/tools"
PDG_BINDING_DIR="$PDG_ROOT/src/bindings/emscripten/"

if [ -z "$1" ]; then
	PDG_DOCS_DIR="$PDG_ROOT/docs/javascript"
else
	PDG_DOCS_DIR="$1"
fi

PDG_IDL_AUTO_EXIT_TIMEOUT_SECONDS="${PDG_IDL_AUTO_EXIT_TIMEOUT_SECONDS:-60}"
PDG_IDL_WATCHDOG_SECONDS="${PDG_IDL_WATCHDOG_SECONDS:-75}"
PDG_IDL_FORCE_KILL_GRACE_SECONDS="${PDG_IDL_FORCE_KILL_GRACE_SECONDS:-5}"

run_pdg_idl() {
	local format="$1"
	local output_file="$2"
	local stderr_file="${output_file}.stderr.log"
	local watchdog_note_file="${output_file}.watchdog.log"
	local pdg_pid
	local watchdog_pid
	local exit_code

	rm -f "$stderr_file" "$watchdog_note_file"

	(
		export PDG_AUTO_EXIT_TIMEOUT="$PDG_IDL_AUTO_EXIT_TIMEOUT_SECONDS"
		"$PDG_ROOT/pdg" tools/make-idl.js "$format" > "$output_file" 2> "$stderr_file"
	) &
	pdg_pid=$!

	(
		sleep "$PDG_IDL_WATCHDOG_SECONDS"
		if kill -0 "$pdg_pid" 2>/dev/null; then
			echo "[make-idl] Terminating hung pdg process after ${PDG_IDL_WATCHDOG_SECONDS}s: $format" > "$watchdog_note_file"
			kill -TERM "$pdg_pid" 2>/dev/null || true
			sleep "$PDG_IDL_FORCE_KILL_GRACE_SECONDS"
			if kill -0 "$pdg_pid" 2>/dev/null; then
				echo "[make-idl] Forcing kill after ${PDG_IDL_FORCE_KILL_GRACE_SECONDS}s grace period: $format" >> "$watchdog_note_file"
				kill -KILL "$pdg_pid" 2>/dev/null || true
			fi
		fi
	) &
	watchdog_pid=$!

	wait "$pdg_pid"
	exit_code=$?

	kill "$watchdog_pid" 2>/dev/null || true
	wait "$watchdog_pid" 2>/dev/null || true

	if [ -f "$watchdog_note_file" ]; then
		cat "$watchdog_note_file" >&2
		rm -f "$watchdog_note_file"
	fi
	if [ -s "$stderr_file" ]; then
		cat "$stderr_file" >&2
	fi
	rm -f "$stderr_file"

	return "$exit_code"
}

cd $PDG_ROOT

run_pdg_idl --doxygen-h-format "$PDG_BUILD_DIR/pdg-js.h" || { exit 1; }

cd $PDG_ROOT
if [ -z "`diff $PDG_BUILD_DIR/pdg-js.h $PDG_DOCS_DIR/pdg-js.h`" ]; then
	echo "-- JavaScript Interface was unchanged --"
else
    diff $PDG_BUILD_DIR/pdg-js.h $PDG_DOCS_DIR/pdg-js.h
	cp $PDG_BUILD_DIR/pdg-js.h $PDG_DOCS_DIR/pdg-js.h
	ls -l $PDG_DOCS_DIR/pdg-js.h
	echo "To rebuild docs use: tools/regen-doxygen-docs.sh"
fi

run_pdg_idl --json-format "$PDG_BUILD_DIR/pdg-js.json" || { exit 1; }

cd $PDG_ROOT
if [ -z "`diff --ignore-matching-lines=\"\\\"when\\\":\\ \" $PDG_BUILD_DIR/pdg-js.json $PDG_DOCS_DIR/pdg-js.json`" ]; then
	echo "-- JSON IDL was unchanged --"
else
    diff --ignore-matching-lines="\"when\": " $PDG_BUILD_DIR/pdg-js.json $PDG_DOCS_DIR/pdg-js.json
	cp $PDG_BUILD_DIR/pdg-js.json $PDG_DOCS_DIR/pdg-js.json
	ls -l $PDG_DOCS_DIR/pdg-js.json
fi
