<?php
	/**
 * Zeigt wenn aufgerufen die Userdaten eines Profils an, wenn der Angemeldete User
 * mit dem Profil übereinstimmt, werden ihm auch die Optionen angezeigt um seine
 * Daten zu ändern, das Passwort zu ändern und sein Profilbild zu ändern
 *
 *
 *
*/
?>
			<div class="post-bar"  id="profilverwaltung">
				<div class="container">
					<div class="row">
						<div class="col">
							<div class="post_topbar">
								<div class="usy-dt">
									<table>
									<tr><td><img src="<?php echo $manage['avatar']?>" id="prof_pic"></td>	    		
									<td><h3><?php  echo $manage['username']?></h3></td></tr>
									</table>
								</div>
							</div>
						</div>
						<div class="col">
							<div class="job_descp">
								<table id="user_data_table">	
								<tr>
									<td>Anrede</td>
									<td> <?php  echo $manage['anrede'] ?> </td>
								</tr>
								<tr>
									<td>Vorname</td>
									<td> <?php  echo $manage['vorname'] ?> </td>
								</tr>
								<tr>
									<td>Nachname</td>
									<td> <?php  echo $manage['nachname'] ?> </td>
								</tr>
								<tr>
									<td>E-Mail</td>
									<td> <?php  echo $manage['email'] ?> </td>
								</tr>
							</table>
						</div>
						<div class="container">
							<?php
							if(isset($_SESSION['user_id']))
							{
								if($_GET['profile'] == $_SESSION['user_id'])
							{
								include("profilverwaltung/showProfileOptions.php");
							}	
							}
							?>
						</div>
					</div>
				</div>
			</div>
		</div>
