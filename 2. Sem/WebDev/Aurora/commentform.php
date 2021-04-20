<?php
/**
 * Erscheint wenn ein einzelner Post aufgerufen wird darunter.
 *
 * Formular um einen Kommentar zur Datenbank hinzuzufügen.
 *
*/
?>

    <form action="?show=<?php echo$_GET['show'];?>&comment=true" method="post" enctype="multipart/form-data">
    <label>KOMMENTIEREN</label>
    <textarea name ="content" class="form-control" rows="3" required></textarea>
    <button type="submit" value="posten">POSTEN</button>
    </form>
