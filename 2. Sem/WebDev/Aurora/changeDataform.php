<?php
/**
 * Wird aufgerufen wenn der User seine Daten ändern will
 *
 * Übernimmt aus der Datenbank die Werte und lässt den User somit diese editieren
 * Sendet diese über POST mit GET profile = aktuelles Profil und newdata=true
 *  
 *
*/
?>

<div class="post-bar" id="order_type_div">
    <div class="job_descp">
    <form action='?profile=<?php echo$_GET['profile'];?>&newdata=true' method="post">
        <table>
            <tr>
                <td><label>Anrede</label></td>     
                <td><label for="male">Herr</label>
                <input type="radio" id="male" name="anrede" value="Herr" <?php if($manage["anrede"] == "Herr"){ echo "checked"; } ?> >
                <label for="female">Frau</label>
                <input type="radio" id="female" name="anrede" value="Frau" <?php if($manage["anrede"] == "Frau"){ echo "checked"; } ?>>
                <label for="other">keine Angabe</label>
                <input type="radio" id="other" name="anrede" value="" <?php if($manage["anrede"] == ""){ echo "checked"; } ?>></td>
            </tr>
            <tr>
                <td><label for="vorname">Vorname: </label></td>
                <td><input type="text" id="vorname" name="vorname" value="<?php echo htmlspecialchars($manage['vorname']);?>" ></td> 
            </tr>
            <tr>
                <td><label for="nachname">Nachname: </label></td>
                <td><input type="text" id="nachname" name="nachname" value="<?php echo htmlspecialchars($manage['nachname']); ?>" ></td>
            </tr>    
            <tr>
                <td><button class="btn btn-outline-dark btn-sm" type="submit" value="Absenden">Daten Ändern</button></td>
                <td><a href="?profile=<?php echo$_GET['profile'];?>">ZURÜCK</a></td>
            </tr>
        </table>
    </form>
    </div>
</div>
