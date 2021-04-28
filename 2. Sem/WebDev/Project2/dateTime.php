<?php
class DateAndTime {
    public $id;
    public $date;
    public $time;
    public $nameVonBenutzer;
    public $comment;

    function __construct($date, $time) {
        $this->date = $date;
        $this->time = $time;
      }
      public function getID() { return $this->id; }
      public function setID($id) { $this->id=$id; }
      public function getDate() { return $this->date; }
      public function setDate($date) { $this->date=$date; }
      public function getTime() { return $this->time; }
      public function setTime($time) { $this->time=$time; }
      public function getNameVonBenutzer() { return $this->nameVonBenutzer; }
      public function setNameVonBenutzer($nameVonBenutzer) { $this->nameVonBenutzer=$nameVonBenutzer; }
      public function getComment() { return $this->comment; }
      public function setComment($comment) { $this->comment=$comment; }
}
