<?php
include("db/dataHandler.php");

class SimpleLogic
{

    private $dh;

    function __construct()
    {
        $this->dh = new DataHandler();
    }

    function handleRequest($method, $param)
    {
        switch ($method) 
        {
            case "queryAppointments":
                $res = $this->dh->queryAppointments();
                break;

            case "queryDatesByAppointment":
                $res = $this->dh->queryDatesByAppointment($param);
                break;

            case "queryPostAppointment":
                $res = $this->dh->queryPostAppointment($param);
                break;

            case "queryPostDateTimeArray":
                $res = $this->dh->queryPostDateTimeArray($param);
                break;
    
            case "queryBookAppointment":
                $res = $this->dh->queryBookAppointment($param);
                break;
            case "queryUnbookAppointment":
                $res = $this->dh->queryUnbookAppointment($param);
                break;
            case "queryIsItBooked":
                $res = $this->dh->queryIsItBooked($param);
                break;
            
            default:
                $res = null;
                break;
        }
        return $res;
    }

    function getDH() { return $this->dh; }
}
