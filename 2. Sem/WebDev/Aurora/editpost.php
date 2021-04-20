<?php
/**
 * Falls die editierten Daten von einem Post im Textfeld leer sind, werden die Originalen Post Inhalte genommen
 * Dies wird gemacht um ein löschen des Inhalts bei einer reinen Darstellungsänderung (public,private) zu verhindern
 *
 * Die Daten werden wieder in die Datenbank geschrieben
 *
*/
    $textchecker = $db->getSinglePost($_GET['show']);
    $post_id = $_GET['show'];
    if($_POST['content'] == '')
    {
        $text = $textchecker['post_content'];
    }
    else
    {
        $text = $_POST['content'];
    }

    $post_type = $_POST['post_type'];
    $db->modifyPost($post_id,$text,$post_type);
?>
