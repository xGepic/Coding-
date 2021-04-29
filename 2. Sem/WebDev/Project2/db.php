<?php
//this class only deals with sql queries
//each query is done here and they are called from dataHandler.php
class db
{
    private $con;
    //constructor which creates db locally if it doesnt exist
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
                `durationDate` date NOT NULL,
                `durationTime` time NOT NULL,
                `info` varchar(100) NOT NULL,
                PRIMARY KEY (`id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
            $sqlCreateTable2 = "
              CREATE TABLE IF NOT EXISTS `dates` (
                `id` int(11) NOT NULL AUTO_INCREMENT,
                `idAppointment` int(11) NOT NULL,
                `date` date NOT NULL,
                `time` time NOT NULL,
                PRIMARY KEY (`id`),
                FOREIGN KEY (idAppointment) REFERENCES appointments(id)
                ) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
            $sqlCreateTable3 = "
                CREATE TABLE IF NOT EXISTS `userDate` (
                  `idDate` int(11) NOT NULL,
                  `name` varchar(100) NOT NULL,
                  `comment` varchar(100),
                  FOREIGN KEY (idDate) REFERENCES dates(id)
                  ) ENGINE=InnoDB DEFAULT CHARSET=latin1;";
            mysqli_query($this->con, $sqlCreateTable1);
            mysqli_query($this->con, $sqlCreateTable2);
            mysqli_query($this->con, $sqlCreateTable3);
        }
    }
    //query which returns all appointments
    public function queryAppointments()
    {
        $query = "SELECT * FROM appointments";
        if ($ergebnis = mysqli_query($this->con, $query)) {
            return $ergebnis;
        } else {
            return 0;
        }
    }
    //query which returns date options for given appointment
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
    //query which posts new appointment
    public function queryPostAppointment(Appointment $appointment)
    {
        $query1="INSERT INTO `appointments`(`titel`, `ort`, `durationDate`, `durationTime`, `info`) VALUES ('".$appointment->getTitel()."','".$appointment->getOrt()."','".$appointment->getDurationDate()."','".$appointment->getDurationTime()."','".$appointment->getInfo()."')";
        if(mysqli_query($this->con, $query1))
        {
            $query2 = "SELECT * FROM `appointments` WHERE `titel`='" . $appointment->getTitel() . "' AND `ort`='".$appointment->getOrt()."' AND `durationDate`='".$appointment->getDurationDate()."' AND `durationTime`='".$appointment->getDurationTime()."' AND `info`='".$appointment->getInfo()."'";
            $ergebnis = mysqli_query($this->con, $query2);
            $row = mysqli_fetch_object($ergebnis);
            $appointment = new Appointment($row->titel, $row->ort, $row->durationDate, $row->durationTime, $row->info);
            $appointment->setID($row->id);
            return $appointment;
        }
        else
        {
            return 0;
        }
    }
    //query which posts 5 date options
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
    //query which books one date option and in return gives row from dates table in db 
    public function queryBookAppointment($id,$name,$comment)
    {
        $id = mysqli_real_escape_string($this->con, $id);
        $name = mysqli_real_escape_string($this->con, $name);
        $comment = mysqli_real_escape_string($this->con, $comment);
        $query="INSERT INTO `userdate`(`idDate`,`name`,`comment`) VALUES ('". $id ."','".$name."','".$comment."')";
        if(mysqli_query($this->con, $query))
        {
            $returnQuery = "SELECT * FROM `dates` WHERE `id`='" . $id."'";
            if($ergebnis = mysqli_query($this->con, $returnQuery));
                return $ergebnis;
        }
        else
        {
            return 0;
        }
    }
    //query which deletes whole appointment, date options for given appointment and previous votings
    public function queryDeleteAppointment($id)
    {
        $id = mysqli_real_escape_string($this->con, $id);
        $sql1 = "DELETE ud FROM `userdate` ud INNER JOIN `dates` d ON ud.idDate=d.id WHERE d.idAppointment='" . $id . "'";
        $temp1=mysqli_query($this->con, $sql1);
        $sql2 = "DELETE FROM `dates` WHERE idAppointment=" . $id;
        $temp2=mysqli_query($this->con, $sql2);
        $sql3 = "DELETE FROM `appointments` WHERE id=" . $id;
        $temp3=mysqli_query($this->con, $sql3);
        if($temp1&&$temp2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //query which returns all votings for an appointment
    public function queryVotingsByAppointment($id)
    {
        $id = mysqli_real_escape_string($this->con, $id);
        $query = "SELECT * FROM `dates` INNER JOIN `userdate` ON userdate.idDate=dates.id WHERE dates.idAppointment='" . $id . "'";
        if ($ergebnis = mysqli_query($this->con, $query)) {
            return $ergebnis;
        } else {
            return 0;
        }
    }

    function getCon() { return $this->con; } //just a getter for connection, used nowhere
}
