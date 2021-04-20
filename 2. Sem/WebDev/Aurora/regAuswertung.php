<?php
/**
 * Wird aufgerufen wenn ein User das Registrierungsformular abgesendet hat
 *
 * Liest die eingegeben Daten aus POST und durchläuft Filter um die Eingaben zu überprüfen
 * Falls kein Fehler aufkommt wird die Variable $userRegActive auf false gesetzt und somit das Formular ausgeblendet
 *
*/
    $anrede = $_POST['anrede'];
    $vorname = $_POST['vorname'];
    $nachname = $_POST['nachname'];
    $email = $_POST['email'];
    $username = $_POST['username'];
    $password = $_POST['password'];
    $password2 = $_POST['password2'];


    if(!filter_var($email, FILTER_VALIDATE_EMAIL))
    {
        $error['value'] = true;
        $error['type'] = 'Email ungültig';
    }
    else if(strlen($password) == 0 || strlen($password2) == 0)
    {
        $error['value'] = true;
        $error['type'] = 'Passwort fehlt';
    }
    else if($password != $password2)
    {
        $error['value'] = true;
        $error['type'] = 'Passwort stimmt nicht überein';
    }

    if($error['value'] == false)
    {
        $resfetch = $db->searchUser('email',$email);

        if($resfetch !== false)
        {
            $error['value'] = true;
            $error['type'] = 'Email bereits registriert';
        }
    }
    if($error['value'] == false)
    {
        $resfetch = $db->searchUser('username',$username);

        if($resfetch !== false)
        {
            $error['value'] = true;
            $error['type'] = 'Username bereits registriert';
        }
    }
    
    if($error['value'] == false)
    {
        $password_hashed = password_hash($password, PASSWORD_DEFAULT);
        $new_user = new user($anrede, $vorname, $nachname, $email, $username, $password_hashed);
        $result = $db->insertUser($new_user->return_as_array());
        
        if($result)
        {
            $userRegActive = false;
        }
        else
        {
            $error['value'] = true;
            $error['type'] = 'Unknown Error';
        }
    }
?>
