<?php 

/**
 * Wird zur Auswertung von Anmeldedaten aufgerufen
 *
 * Überprüft ob die Angegebene Email in der Datenbank vorhanden ist
 * und prüft ob das eingegebene Passwort mit dem in der Datenbank überein stimmt
 * 
 * Falls der Account auf inaktiv gestellt wurde wird eine Fehlermeldung gesetzt
 * und der user nicht eingeloggt
*/
 
    $email = $_POST['email'];
    $password = $_POST['password'];
    
    $user = $db->searchUser('email',$email);
        
    //Überprüfung des Passworts
    if ($user !== false && password_verify($password, $user['password'])) 
    {
        if($user['active'] == 0)
        {
            $error['value'] = true;
            $error['type'] = "Account wurde deaktiviert.";
        }
        else
        {
            $_SESSION['user_id'] = $user['id'];
            die(header('Location: index.php'));   
        }
    } 
    else 
    {
            $error['value'] = true;
            $error['type'] = "Email oder Passwort falsch"; 
    }

?>
