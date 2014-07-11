<?php

$output = shell_exec('sudo -u ezavada /sw/bin/git status'); // 2>&1 1> /dev/null');
//$output = shell_exec('sudo -u ezavada /sw/bin/git config --global user.name "Ed Zavada"  2>&1 1> /dev/null');
//$output .= shell_exec('sudo -u ezavada /sw/bin/git config --global user.email ezavada@zoom.local  2>&1 1> /dev/null');

echo "Git output:<br/><pre>{$output}</pre>";

?>