#!/bin/bash
# -------------------------------------------
# colors.sh
#
# source this to define colors for use in terminal output
#
# example:
# 		echo -e "${ERR}This is an error${NRML}"
#
#
# Written by Ed Zavada, 2014
# Copyright (c) 2014, Dream Rock Studios, LLC
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

if [ $? = 0 ] && [ "$(tput colors 2> /dev/null)" -gt "2" ]; then
	export ERR="\033[1;37;41m"
	export RED="\033[1;37m"
	export MGNT="\033[1;35m"
	export NRML="\033[0;0m"
	export BOLD="\033[1;37m"
	export BLUE="\033[0;34m"
	export GRN="\033[0;32m"
	export YELW="\033[0;33m"
	export BLUE="\033[0;34m"
fi
