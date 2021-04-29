<?php
//this class takes all raw input from db.php and convert it to appropiate data format
//this class is called from simpleLogic.php, based on which query user wants to run
include("models/appointment.php");
include("models/dateTime.php");
include("models/vote.php");
include("db.php");
class DataHandler
{

    private $db;

    function __construct()//db.php object
    {
        $this->db = new db();
    }
    //function for transforming raw input to Appointment.php objects
    //it adds them to array and then the whole array is returned to simpleLogic.php
    public function queryAppointments()
    {
        $array = array();
        $ergebnis = $this->db->queryAppointments();
        while ($row = mysqli_fetch_object($ergebnis)) {
            $appointment = new Appointment($row->titel, $row->ort, $row->durationDate, $row->durationTime, $row->info);
            $appointment->setID($row->id);
            array_push($array, $appointment);
        }
        return $array;
    }
    //function for transforming raw input to DateAndTime.php objects
    //it adds them to array and then the whole array is returned to simpleLogic.php
    public function queryDatesByAppointment($idAppointment)
    {
        $array = array();
        $ergebnis = $this->db->queryDatesByAppointment($idAppointment);
        while ($row = mysqli_fetch_object($ergebnis)) {
            $dateTime = new DateAndTime($row->date, $row->time);
            array_push($array, $dateTime);
        }
        return $array;
    }
    //function for transforming parameters from input to Appointment.php object
    //it transforms duration (in hours) to appropriate date and time when the appointment will expire
    public function queryPostAppointment($param)
    {
        $pieces=explode(",",$param);
        $now = new DateTime();
        $now->add(new DateInterval("PT{$pieces[2]}H"));
        $date = $now->format('Y-m-d');
        $time = $now->format('H:i:s');
        $appointment=new Appointment($pieces[0],$pieces[1],$date,$time,$pieces[3]);
        return $this->db->queryPostAppointment($appointment);
    }
    //function for transforming parameters from input to DateAndTime.php object
    //it transforms date and time from param variable to appropriate data format
    public function queryPostDateTimeArray($param)//$param[0] ist idAppointment, $param[i*2+1] ist date und $param[(i+1)*2] ist time
    {
        $array = array();
        $param=str_replace("T",",",$param);
        $pieces=explode(",",$param);
        for($i=0;$i<5;$i++)
        {
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
    //function which takes name, comment and id of date option which has to be booked
    //it returns whole row from table because we have to print that row to the table in html
    public function queryBookAppointment($param)
    {
        $pieces=explode(",",$param);
        $ergebnis = $this->db->queryBookAppointment($pieces[0],$pieces[1],$pieces[2]);
        $row = mysqli_fetch_object($ergebnis);
        return $row;
    }
    //function for deleting an Appointment
    //just passing params for this query, without changing them
    public function queryDeleteAppointment($param)
    {
        return $this->db->queryDeleteAppointment($param);
    }
    //function for transforming raw input to DateAndTime.php and Vote.php objects
    //it adds them to array and then the whole array is returned to simpleLogic.php
    public function queryVotingsByAppointment($param)
    {
        $array = array();
        $ergebnis=$this->db->queryVotingsByAppointment($param);
        while ($row = mysqli_fetch_object($ergebnis)) {
            $vote = new Vote($row->name, $row->comment);
            $dateTime=new DateAndTime($row->date,$row->time);
            array_push($array, $vote);
            array_push($array, $dateTime);
        }
        return $array;
    }

    function getDB() { return $this->db; }

}
