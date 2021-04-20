<?php
/**
 * Formular fürs Hochladen des Profilbildes
 *
 *Nimmt nur Bilder, welche über POST gesendet werden mit den GET profile=aktuelles Profil und newpic=true
 *
*/
?>

<div class="post-bar" id="order_type_div">
<div class="job_descp">
    <form action='?profile=<?php echo$_GET['profile'];?>&newpic=true' method="post" enctype="multipart/form-data">
    <div class="custom-file">
    <input type="file" class="custom-file-input" accept="image/*" name="bild" id="my_bild">
                <label class="custom-file-label" for="my_bild">Hochladen <i class="bi bi-cloud-upload"></i></label> 
    </div>
                <button class="btn btn-outline-dark btn-sm" type="submit" value="Absenden">Bild Ändern</button>
        <a href="?profile=<?php echo$_GET['profile'];?>">ZURÜCK</a>
    </form>
</div>
</div>
