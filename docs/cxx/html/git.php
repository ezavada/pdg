<?php

$output = shell_exec('sudo /usr/bin/git status'); // 2>&1 1> /dev/null');

echo "Git output:<br/><pre>{$output}</pre>";

?>
