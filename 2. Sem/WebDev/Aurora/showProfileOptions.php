<?php
/**
 * 3 Formulare, die Buttons enthalten um die jeweiligen Bearbeitungsseiten zu laden -- Profilverwaltung
 *
 *
 *
*/
?>

<form action='?profile=<?php echo$_GET['profile'];?>&changedata=true' method="post">
        <button class="btn btn-outline-dark btn-sm" type="submit" value="Change User Data">User-Daten Bearbeiten</button>
</form>
<form action='?profile=<?php echo$_GET['profile'];?>&changepassword=true' method="post">
        <button class="btn btn-outline-dark btn-sm" type="submit" value="Change User Password">User-Passwort Ändern</button>
</form>
<form action='?profile=<?php echo$_GET['profile'];?>&managepic=true' method="post">
        <button class="btn btn-outline-dark btn-sm" type="submit" value="Change User Profile Picture">Profilbild Ändern</button>
</form>
