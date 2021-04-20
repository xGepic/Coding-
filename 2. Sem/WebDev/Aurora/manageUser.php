<?php

/**
 * Kümmert sich um die Verwaltung des Usersprofils
 * 
 * Blendet abhängig von den GET Parametern die Unterschiedlichen Formulare ein und aus
 * Und sucht die Daten des angeschauten Profils aus der Datenbank
 *
*/

    $manage = $db->searchUser('id',$_GET['profile']);
    if(isset($_SESSION['user_id']))
    {
    if($_SESSION['user_id'] === $_GET['profile'])
    {

	if(isset($_GET['changedata']))
    {
        include('changeDataForm.php');
    }
    else if(isset($_GET['changepassword']))
    {
        include('changePasswordForm.php');
    }
    else if(isset($_GET['managepic']))
    {
        include('changePictureForm.php');
    }
    else
    {
        include('profilverwaltung/manageUserForm.php');
    }
    }
    else
    {
        include('profilverwaltung/manageUserForm.php');
    }
    }
    else
    {
        if($manage == false)
        {
            die("Nothing to see here");
        }
        include('profilverwaltung/manageUserForm.php');
    }


    

?>

