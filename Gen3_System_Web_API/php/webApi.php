#!/usr/bin/env php
<?php

$USAGE_MSG = 'Usage: webApi.php HOST[:PORT] KEY [KEY ...]' . PHP_EOL;

$argvLen = count($argv);

if ($argvLen < 3) {
	echo($USAGE_MSG);
	exit(1);
}

if (filter_var(explode(':', $argv[1])[0], FILTER_VALIDATE_IP) === false) {
	echo('Invalid IP Address: ' . $argv[1] . PHP_EOL);
	exit(1);
}

if ($argvLen == 3) {
	$jsonRequest['messageType'] = 'getStatusItem';
	$jsonRequest['key'] = $argv[2];
}
else {
	$jsonRequest['messageType'] = 'getStatusItemBatch';
	$jsonRequest['keys'] = array_slice($argv, 2);
}

$url = 'http://' . $argv[1] . '/api/v1/status';
$ch = curl_init($url);
curl_setopt_array($ch, array(
	CURLOPT_POST => TRUE,
	CURLOPT_RETURNTRANSFER => TRUE,
	CURLOPT_POSTFIELDS => json_encode($jsonRequest)
));

// Send the request
$response = curl_exec($ch);

// Check for errors
if($response === FALSE){
    die(curl_error($ch));
}

// Decode the response
$responseData = json_decode($response, TRUE);

// Close the cURL handler
curl_close($ch);

// Print the date from the response
echo('JSON Request: ');
print_r($jsonRequest);

echo('Resp: ');
print_r($responseData);
