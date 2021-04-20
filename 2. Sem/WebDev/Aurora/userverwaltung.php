<?php
/**
 * Erscheint nur wenn der Admin angemeldet ist und die Admin Page aufgerufen wird.
 *  
 * Eine Tabelle mit allen Usern und ihren Daten (bis auf das Passwort). 
 * Formular enthält Link auf die User Pages und einen Link um Aktivitätsstatur der User zu ändern.
 * Beides mittels GET geregelt.
 *
*/


	echo "<div class='container' id='adminpage'>
		<table class='table'>
			<tr>
		        <th>ID</th>
		        <th>Anrede</th>
		        <th>Vorname</th>
		        <th>Nachname</th>
		        <th>Email</th>
		        <th>Username</th>
		        <th>Aktiv</th>
		        <th>(De-)Aktivieren</th>
	        </tr>";

    $adminSearch = $db->getAllUser();

	foreach ($adminSearch as $row) {

		if($row["active"] == 1){
			$activity="Aktiv";
		}
		else{
			$activity="Deaktiviert";
		}

	    echo "<tr>
	            <td>".$row["id"]."</td>
	            <td>".$row["anrede"]."</td>
	            <td>".$row["vorname"]."</td>
	            <td>".$row["nachname"]."</td>
	            <td>".$row["email"]."</td>
	            <td><a href=?profile=".$row['id'].">".$row["username"]."</a></td>
	            <td>".$activity."</td>
    			<td><a href=?adminpage=true&id=".$row["id"]."&change=true>Ändern</a></td>
			</tr>
			</div>
			";
	}
?>
