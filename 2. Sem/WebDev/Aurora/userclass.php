<?php
/**
 * Klasse um einzelne User zu verwalten.
 *
*/

   class user
   {
     private $neuer_user = array(); 
     
     public function __construct($anrede,$vorname,$nachname,$email,$username,$password)
     {
         $this->neuer_user['anrede'] = $anrede;
         $this->neuer_user['vorname'] = $vorname;
         $this->neuer_user['nachname'] = $nachname;
         $this->neuer_user['email'] = $email;
         $this->neuer_user['username'] = $username;
         $this->neuer_user['password'] = $password;
     }

     public function setid($id)
     {
         $this->neuer_user['id'];
     }

     public function return_as_array()
     {
         return $this->neuer_user;
     }
   }
   

?>
