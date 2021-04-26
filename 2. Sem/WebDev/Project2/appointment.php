<?php
class Appointment {
    public $id;
    public $titel;
    public $ort;
    public $duration;
    public $info;

    function __construct($titel, $ort, $duration, $info) {
        $this->titel = $titel;
        $this->ort = $ort;
        $this->duration = $duration;
        $this->info = $info;
      }
      public function getID() { return $this->id; }
      public function setID($id) { $this->id=$id; }
      public function getTitel() { return $this->titel; }
      public function setTitel($titel) { $this->titel=$titel; }
      public function getOrt() { return $this->ort; }
      public function setOrt($ort) { $this->ort=$ort; }
      public function getDuration() { return $this->duration; }
      public function setDuration($duration) { $this->duration=$duration; }
      public function getInfo() { return $this->info; }
      public function setInfo($info) { $this->info=$info; }
}
