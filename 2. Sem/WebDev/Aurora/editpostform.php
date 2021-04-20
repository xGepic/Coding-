<?php
/**
 * Formular was aufgerufen wird um den Post zu bearbeiten, besitzt ein 
 * Textfeld um einen neuen Post Text zu schreiben sowie die möglichkeit zwischen den public und private
 * Zuständen zu wechseln
 *
 * Wird über POST mit den GET show=aktuellerPost und newedit=true gesendet
 *
*/
?>
<form action="?show=<?php echo$_GET['show'];?>&newedit=true" method="post" enctype="multipart/form-data">
    <textarea name ="content" class="form-control" rows="3"></textarea>
        <label for="public">Public</label>
        <input type="radio" id="public" name="post_type" value="public" <?php if($result["post_type"] == "public"){ echo "checked"; } ?> >
        <label for="private">Private</label>
        <input type="radio" id="private" name="post_type" value="private" <?php if($result["post_type"] == "private"){ echo "checked"; } ?>>
    <button type="submit" value="Ändern" id="changeButton">EDITIEREN</button>
    </form>

