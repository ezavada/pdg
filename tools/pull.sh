# this is only used on my file server to pull updated docs while leaving the dox files editable by
# the web user
CUR_USER=`whoami`
if [ "$CUR_USER" != "ezavada" ]; then
	echo "WARNING: changing file ownership to $CUR_USER, not ezavada"
fi
sudo chown -R $CUR_USER:admin docs/javascript/dox
sudo chown -R $CUR_USER:admin docs/cxx/dox
git pull
sudo chown -R www:admin docs/javascript/dox
sudo chown -R www:admin docs/cxx/dox
sudo touch docs/javascript/html/save.log
sudo touch docs/cxx/html/save.log
sudo chown -R www:admin docs/javascript/html/save.log
sudo chown -R www:admin docs/cxx/html/save.log
