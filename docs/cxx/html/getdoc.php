<?php

$rawDocName = $_GET['name'];

// extremely simple safety check, limit us to the javascript/dox directory, and add .dox extension
$docNameArray = explode('/', $rawDocName);
$docName = '../dox/' . $docNameArray[count($docNameArray) - 1] . '.dox';
if (!file_exists($docName)) {
	header('HTTP/1.0 404 Not Found');
} else {
	header("Cache-Control: no-cache, must-revalidate"); // HTTP/1.1
	header("Expires: Sat, 26 Jul 1997 05:00:00 GMT"); // Date in the past
	header("ContentType: text/plain"); // HTTP/1.1
	
	file_put_contents ( "save.log", "GET docName: " . $docName . "\n", FILE_APPEND);
	$output = file_get_contents ( $docName);
	echo $output;
}

?>