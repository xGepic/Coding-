<?php
/**
 * Formular was aufgerufen wird um das Passwort zu ändern
 * 
 * Nimmt das alte Passwort sowie das Neue und seine Bestätigung
 *
 * Wird über POST übermittelt mit GET auf profile=aktuelles Profil und newpassword=true
 *
*/
?>

<div class="post-bar" id="order_type_div">
<div class="job_descp">
    <form action='?profile=<?php echo$_GET['profile'];?>&newpassword=true' method="post">
        <table>
            <tr>
                <td><label for="passwortAlt">Altes Passwort: </label></td>
                <td><input type="password" id="password0" name="password0"></td>
            </tr>
            <tr>
                <td><label for="passwort1">Neues Passwort: </label></td>
                <td><input type="password" id="password1" name="password1"></td>
            </tr>
            <tr>
                <td><label for="passwort2">Passwort nochmal eingeben: </label></td>
                <td><input type="password" id="password2" name="password2"></td>
            </tr> 
             
            <tr>
                <td><button class="btn btn-outline-dark btn-sm" type="submit" value="Absenden">Passwort Ändern</td>
                <td><a href="?profile=<?php echo$_GET['profile'];?>">ZURÜCK</a></td>
            </tr>
        </table>
    </form>
</div>
</div>
