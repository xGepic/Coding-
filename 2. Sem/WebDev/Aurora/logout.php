<?php
/**
 * Wird aufgerufen wenn der Logout Button gedrückt wurde
 *
 * Zerstört die Session und lädt die Index Seite
 *
*/
    session_start();
    session_destroy();
    header("Location:index.php");
?>
