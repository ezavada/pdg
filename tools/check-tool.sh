command_exists () {
    type "$1" &> /dev/null ;
}

if ! command_exists $1 ; then
	echo "Looked for $1 in: $PATH"
	echo -e "${ERR}FATAL: $1 not found!${NRML}"
	echo -e "Please install it using: ${BOLD}$2${NRML}"
	exit 1
fi