<?php
/**
 * Formular für die Registrierung von Usern
 *
 *Wird aufgerufen wenn der User nicht angemeldet ist und sich noch nicht registriert hat
 *
*/
?>

<form action="?reg=true" method="post">
            <table class="table">
			<tr>
			<td>
			<h3>Registrieren</h3>
			</td>
			</tr>
			<tr>
			<td>
			<label>Anrede</label>
			<br>
            <label for="male">Herr</label>
            <input type="radio" id="male" name="anrede" value="Herr" checked ="checked">
			<br>
            <label for="female">Frau</label>
            <input type="radio" id="female" name="anrede" value="Frau">
			<br>
            <label for="other">keine Angabe</label>
            <input type="radio" id="other" name="anrede" value="">
			<br>
			</td>
			</tr>
			<tr>
			<td>
    		<label for="vorname">Vorname: </label>
    		<input type="text" id="vorname" name="vorname" required>
			</td>
			</tr>
			<tr>
			<td>
    		<label for="nachname">Nachname: </label>
    		<input type="text" id="nachname" name="nachname" required>
			</td>
			</tr>
			<tr>
			<td>
    		<label for="email">E-Mail: </label>
    		<input type="email" id="email" name="email" required>
			</td>
			</tr>
			<tr>
			<td>
    		<label for="username">Username: </label>
    		<input type="text" id="username" name="username" required>
			</td>
			</tr>
			<tr>
			<td>
    		<label for="passwort">Passwort: </label>
    		<input type="password" id="password" name="password" required>
			</td>
			</tr>
			<tr>
			<td>
    		<label for="passwort2">Passwort nochmal eingeben: </label>
    		<input type="password" id="password2" name="password2" required>
			</td>
			</tr>
			<tr>
			<td>
			<button class="btn btn-outline-dark btn-sm" type="submit" value="Absenden">Registrieren</button>
			<button class="btn btn-outline-dark btn-sm" type="reset" value="Abbrechen">Abbrechen</button>
			</td>
			</tr>
			</table>
</form>
