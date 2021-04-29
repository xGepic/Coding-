<?php

$method = $_SERVER['REQUEST_METHOD'];

// get list of available timezones
if ($method === 'GET') {
    
    $tz = getTimezones();

    header('Content-Type: application/json');
    http_response_code(200);
    echo json_encode($tz);    

// convert given datetime
} else if ($method === "POST") {

    // read json
    $jsonObj = json_decode(file_get_contents('php://input'));
    $timeObj = convertDateTime($jsonObj);
    if ($timeObj === null) {
        http_response_code(400);
        echo "Bad request";
        exit;    
    }

    header('Content-Type: application/json');
    http_response_code(200);
    echo json_encode($timeObj);

} else {
    http_response_code(405);
    header("Allow: GET POST");
    echo "Method Not Allowed";
    exit;
}

/** 
 * @return string[] list of all timezones + UTC
 */
function getTimezones() {
    return DateTimeZone::listIdentifiers(DateTimeZone::ALL);
}

/** 
 * @param object request, JSON Format eg:
 *  {
 *     "date": "23.04.2021 15:00:00",
 *	   "tzsource": "Europe/Vienna", 
 *     "tztarget": "Europe/London"
 *  }
 * @return stdClass converted date + timezone
 */
function convertDateTime($request) {
    if (!isset($request->date) ||
        !isset($request->tzsource) ||
        !isset($request->tztarget)) {
        return null;
    }

    $date = new DateTime($request->date, new DateTimeZone($request->tzsource));   
    if ($date === false) {
        return null;
    }
    if ($date->setTimezone(new DateTimeZone($request->tztarget)) === false) {
        return null;
    }

    $result = new stdClass();
    $result->date     = $date->format("d.m.Y H:i:s");
    $result->timezone = $request->tztarget;    
    return $result;
}