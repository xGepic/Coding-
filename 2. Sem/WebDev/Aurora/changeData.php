<?php
/**
 * Übernimmt die eingegeben Daten aus der Profilverwaltung und schreibt sie mit 
 * einer Datenbankfunktion in die Datenbank
 *
 * Nimmt eingaben aus POST, kreiert Array, welches an die Funktion übergeben wird
 * 
 *
*/
		$user_array = array();
		$user_array['anrede'] = $_POST['anrede'];
   		$user_array['vorname'] = $_POST['vorname'];
		$user_array['nachname'] = $_POST['nachname'];
		$user_array['user_id'] = $_SESSION['user_id'];

		$db->updateUser($user_array);
  ?>
