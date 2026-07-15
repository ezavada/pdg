#!/bin/bash
# this is only used on my file server to pull updated docs while leaving the dox files editable by
# the web user
CUR_USER=`whoami`
if [ "$CUR_USER" != "root" ]; then
	echo "ERROR: must run as root, try sudo tools/pull.sh"
	exit 1
fi
sudo chown -R root:root docs/javascript/dox
sudo chown -R root:root docs/cxx/dox
git pull
sudo chown -R nginx:nginx docs/javascript/dox
sudo chown -R nginx:nginx docs/cxx/dox
sudo touch docs/javascript/html/save.log
sudo touch docs/cxx/html/save.log
sudo chown nginx:nginx docs/javascript/html/save.log
sudo chown nginx:nginx docs/cxx/html/save.log
