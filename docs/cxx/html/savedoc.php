<?php
// saves a block of documentation

header("Cache-Control: no-cache, must-revalidate"); // HTTP/1.1
header("Expires: Sat, 26 Jul 1997 05:00:00 GMT"); // Date in the past

  function getRemoteIP () {
    // check to see whether the user is behind a proxy - if so,
    // we need to use the HTTP_X_FORWARDED_FOR address (assuming it's available)
    if (array_key_exists("HTTP_X_FORWARDED_FOR", $_SERVER) > 0) { 
      // this address has been provided, so we should probably use it
      $f = $_SERVER["HTTP_X_FORWARDED_FOR"];
      // however, before we're sure, we should check whether it is within a range 
      // reserved for internal use (see http://tools.ietf.org/html/rfc1918)- if so 
      // it's useless to us and we might as well use the address from REMOTE_ADDR
      $reserved = false;
      // check reserved range 10.0.0.0 - 10.255.255.255
      if (substr($f, 0, 3) == "10.") {
        $reserved = true;
      }
      // check reserved range 172.16.0.0 - 172.31.255.255
      if (substr($f, 0, 4) == "172." && substr($f, 4, 2) > 15 && substr($f, 4, 2) < 32) {
        $reserved = true;
      }
      // check reserved range 192.168.0.0 - 192.168.255.255
      if (substr($f, 0, 8) == "192.168.") {
        $reserved = true;
      }
      // now we know whether this address is any use or not
      if (!$reserved) {
        $ip = $f;
      }
    } 
    // if we didn't successfully get an IP address from the above, we'll have to use
    // the one supplied in REMOTE_ADDR
    if (!isset($ip)) {
      $ip = $_SERVER["REMOTE_ADDR"];
    }
    // done!
    return $ip;
  }

$remoteIP = getRemoteIP();

file_put_contents ( "save.log", "got request from " . $remoteIP . "\n", FILE_APPEND);
$rawDocName = $_POST['docName'];
$docContents = $_POST['docContents'];
$docContents = str_replace('\\\\', '\\', $docContents);  // remove escapes from backslashes
$docContents = str_replace("\\'", "'", $docContents);  // remove escapes from apostrophes
$docContents = str_replace('\\"', '"', $docContents);  // remove escapes from double quotes

file_put_contents ( "save.log", " rawDocName: " . $rawDocName . "\n", FILE_APPEND);
file_put_contents ( "save.log", " docContents: " . $docContents . "\n", FILE_APPEND);

// extremely simple safety check, limit us to the javascript/dox directory, and add .dox extension
$docNameArray = explode('/', $rawDocName);
$docName = '../dox/' . $docNameArray[count($docNameArray) - 1] . '.dox';
file_put_contents ( "save.log", " docName: " . $docName . "\n", FILE_APPEND);
file_put_contents ( "save.log", " writing file : " . $docName . "\n", FILE_APPEND);
file_put_contents ( $docName , $docContents );
$cmd = 'sudo -u ezavada /sw/bin/git add ' . $docName . ' 2>&1';
//file_put_contents ( "save.log", " > " . $cmd . "\n", FILE_APPEND);
$output = shell_exec($cmd);
//file_put_contents ( "save.log", " git said : " . $output . "\n", FILE_APPEND);
$cmd = 'sudo -u ezavada /sw/bin/git commit -o ' . $docName . ' -m "update from ' . getRemoteIP() . 
	'"  --no-status 2>&1 | tail -1';
file_put_contents ( "save.log", " > " . $cmd . "\n", FILE_APPEND);
$output = shell_exec($cmd);
file_put_contents ( "save.log", $output . "\n", FILE_APPEND);

?>