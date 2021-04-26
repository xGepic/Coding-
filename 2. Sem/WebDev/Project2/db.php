<?php

class db
{
    private $con;

    function __construct() {
        $this->con = mysqli_connect('localhost', 'bif2webscriptinguser', 'bif2021');
        $selectAlreadyCreatedDatabase = mysqli_select_db($this->con, "WEBSCprojekt");
        if (!$selectAlreadyCreatedDatabase) 
        {
            $createNewDb = "CREATE DATABASE IF NOT EXISTS `WEBSCprojekt`";
            mysqli_query($this->con, $createNewDb);
        }
        $selectCreatedDatabase = mysqli_select_db($this->con, "WEBSCprojekt");
        if ($selectCreatedDatabase) {
            $sqlCreateTable1 = "
              CREATE TABLE IF NOT EXISTS `appointments` (
                `id` int(11) NOT NULL AUTO_INCREMENT,
                `titel` varchar(100) NOT NULL,
                `ort` varchar(100) NOT NULL,
                `duration` date NOT NULL,
                `info` varchar(100) NOT NULL,
                PRIMARY KEY (`id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
            $sqlCreateTable2 = "
              CREATE TABLE IF NOT EXISTS `dates` (
                `id` int(11) NOT NULL AUTO_INCREMENT,
                `idAppointment` int(11) NOT NULL,
                `date` date NOT NULL,
                `time` time NOT NULL,
                `nameVonBenutzer` varchar(100),
                PRIMARY KEY (`id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
            mysqli_query($this->con, $sqlCreateTable1);
            mysqli_query($this->con, $sqlCreateTable2);
        }
    }

    public function queryAppointments()
    {
        $query = "SELECT * FROM appointments";
        if ($ergebnis = mysqli_query($this->con, $query)) {
            return $ergebnis;
        } else {
            return 0;
        }
    }

    public function queryDatesByAppointment($idAppointment)
    {
        $idOfAppointment = mysqli_real_escape_string($this->con, $idAppointment);
        $query = "SELECT * FROM `dates` WHERE `idAppointment`='" . $idAppointment . "'";
        if ($ergebnis = mysqli_query($this->con, $query)) {
            return $ergebnis;
        } else {
            return 0;
        }
    }

    public function queryPostAppointment(Appointment $appointment)
    {
        $query1="INSERT INTO `appointments`(`titel`, `ort`, `duration`, `info`) VALUES ('".$appointment->getTitel()."','".$appointment->getOrt()."','".$appointment->getDuration()."','".$appointment->getInfo()."')";
        if(mysqli_query($this->con, $query1))
        {
            $query2 = "SELECT `id` FROM `appointments` WHERE `titel`='" . $appointment->getTitel() . "' AND `ort`='".$appointment->getOrt()."' AND `duration`='".$appointment->getDuration()."' AND `info`='".$appointment->getInfo()."'";
            if($ergebnis = mysqli_query($this->con, $query2));
                return $ergebnis;
        }
        else
        {
            return 0;
        }
    }

    public function queryPostDateTimeArray($idAppointment, $dateTimeArray)
    {
        for($i=0;$i<5;$i++)
        {
            $query="INSERT INTO `dates`(`idAppointment`,`date`, `time`) VALUES ('". $idAppointment ."','". $dateTimeArray[$i]->getDate() ."','". $dateTimeArray[$i]->getTime() ."')";
            if(!mysqli_query($this->con, $query))
            {
                return 0;
            }
        }
        return 1;
    }

    public function queryBookAppointment($name, $id)
    {
        $id = mysqli_real_escape_string($this->con, $id);
        $name = mysqli_real_escape_string($this->con, $name);
        $query = 'UPDATE `dates` SET `nameVonBenutzer`= "'.$name.'" WHERE `id`="'.$id.'"';
        if($ergebnis = mysqli_query($this->con, $query))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    public function queryUnbookAppointment($id)
    {
        $id = mysqli_real_escape_string($this->con, $id);
        $query = 'UPDATE `dates` SET `nameVonBenutzer`= NULL WHERE `id`="'.$id.'"';
        if($ergebnis = mysqli_query($this->con, $query))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    public function queryIsItBooked($id)
    {
        $id = mysqli_real_escape_string($this->con, $id);
        $query = 'SELECT `nameVonBenutzer` FROM `dates` WHERE `id`="'.$id.'"';
        if($ergebnis = mysqli_query($this->con, $query))
        {
            return $ergebnis;
        }
        else
        {
            return 0;
        }
    }

    function getCon() { return $this->con; }
}