<?php
include("models/appointment.php");
include("models/dateTime.php");
include("db.php");
class DataHandler
{

    private $db;

    function __construct()
    {
        $this->db = new db();
    }

    public function queryAppointments()
    {
        $array = array();
        $ergebnis = $this->db->queryAppointments();
        while ($row = mysqli_fetch_object($ergebnis)) {
            $appointment = new Appointment($row->titel, $row->ort, $row->duration, $row->info);
            $appointment->setID($row->id);
            array_push($array, $appointment);
        }
        return $array;
    }

    public function queryDatesByAppointment($idAppointment)
    {
        $array = array();
        $ergebnis = $this->db->queryDatesByAppointment($idAppointment);
        while ($row = mysqli_fetch_object($ergebnis)) {
            $dateTime = new DateAndTime($row->date, $row->time);
            $dateTime->setID($row->id);
            array_push($array, $dateTime);
        }
        return $array;
    }

    public function queryPostAppointment($param)
    {
        $pieces=explode(",",$param);
        $appointment=new Appointment($pieces[0],$pieces[1],$pieces[2],$pieces[3]);
        $ergebnis = $this->db->queryPostAppointment($appointment);
        $row = mysqli_fetch_object($ergebnis);
        return $row->id;
    }

    public function queryPostDateTimeArray($param)//$param[0] ist idAppointment, $param[i*2+1] ist date und $param[(i+1)*2] ist time
    {
        $array = array();
        $param=str_replace("T",",",$param);
        $pieces=explode(",",$param);
        for($i=0;$i<5;$i++)
        {
            echo $pieces[$i*2+1];
            echo $pieces[($i+1)*2];
            $dateTime=new DateAndTime($pieces[$i*2+1],$pieces[($i+1)*2]);
            array_push($array, $dateTime);
            
        }
        if($this->db->queryPostDateTimeArray($pieces[0],$array))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    public function queryBookAppointment($param)
    {
        $pieces=explode(",",$param);
        return $this->db->queryBookAppointment($pieces[0],$pieces[1]);
    }

    public function queryUnbookAppointment($param)
    {
        return $this->db->queryUnbookAppointment($param);
    }

    public function queryIsItBooked($param)
    {
        $ergebnis=$this->db->queryIsItBooked($param);
        $row = mysqli_fetch_object($ergebnis);
        if($row->nameVonBenutzer==NULL)
            return 0;
        else
            return 1;
    }

    function getDB() { return $this->db; }

}
