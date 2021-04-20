<?php

/**
 * Wertet die Eingaben zum ändern des Passworts aus und ändert wenn alles passt das Passwort, ansonsten wird eine Fehlermeldung ausgegeben
 *
 * Passwort wird mit der Datenbank verglichen und falls die neuen Passwörter übereinstimmen werden sie mithilfe einer Datenbankfunktion in die Datenbank eingefügt
 * Passwörter sind gehashed in der Datenbank
 *
*/
    $password0 = $_POST['password0'];
    $password1 = $_POST['password1'];
    $password2 = $_POST['password2'];
        
    //Überprüfung des Passworts
    if(password_verify($password0, $result['password'])){
      if($password1 != $password2)
      {
          $error['value'] = true;
          $error['type'] = 'Passwort stimmt nicht überein';
      }
      else
      {
        $password_hashed = password_hash($password1, PASSWORD_DEFAULT);
        $user_info = array();
        $user_info['user_id'] = $_SESSION['user_id'];
        $user_info['password'] = $password_hashed;

        $db->updatePassword($user_info);
      }
    }
    else{
      $error['value'] = true;
      $error['type'] = 'Passwort ist falsch';
      
    } 
  ?>
