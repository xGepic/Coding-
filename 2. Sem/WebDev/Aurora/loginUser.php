<?php
/**
 * Formular für das Anmelden wird aufgerufen wenn der User nicht angemeldet ist
 *
 *Formular enthält Input für Email und Passwort, wird mit GET login=true abgesendet
 *
*/
?>

<form action="?login=true" method="post">
	<table class="table">
			<tr>
			<td>
			<h3>Anmelden</h3>
			</td>
			</tr>
			<tr>
			<td>
			<label for="email">Email:</label>
			<input type="email" maxlength="250" name="email" required>
			</td>
			</tr>
			<tr>
			<td>
			<label for="password">Passwort: </label>
			<input type="password"  maxlength="250" name="password" required>
			</td>
			</tr>
			<tr>
			<td>
			<button class="btn btn-outline-dark btn-sm" type="submit" value="Login">Login</button>
			</td>
			</tr>
	</table>
		</form> 
