<?php
/**
 * Erstellt mittels Verzeichnis Class ein neues Verzeichnis für den Avatar des Users
 *
 * Grundsätzlich hat jeder User nach dem Registrieren ein Default Profilbild
 * 
 * Prüft ob ein Bild hochgeladen wurde, lädt das Bild hoch und speichert den Pfad in die Datenbank unter Avatar
 *
*/

	$avatar = new Verzeichnis('images/avatar/');

	if(isset($_FILES['bild']))
	{
		$path = $avatar->upload('bild');
		$avatar_info = array();
		$avatar_info['path'] = $path;
		$avatar_info['user_id'] = $_SESSION['user_id'];
		$db->changeAvatar($avatar_info);
	}
?>
