<?php

/**
 * Auswertungsdatei um die Eingaben aus dem Post auszuwerten
 * Ein Array wird erstellt, falls es keine Tags gibt werden diese auf NULL gesetzt
 *
 * Es wird überprüft ob ein Bild hochgeladen wurde, falls ja wird auch der Pfad in der Datenbank gespeichert
*/

    $post_array = array();
    
    $post_array['user_id'] = $_SESSION["user_id"];
    $post_array['text'] = $_POST['content'];
    $post_array['date'] = date('Y-m-d H:i:s');
    $post_array['type'] = $_POST['post_type'];
    if($_POST['tags'] == ""){
        $post_array['tags'] = NULL;
    }
    else{
        $post_array['tags'] = $_POST['tags'];
    }
    $picadded = false;

    $db->insertPost($post_array);

    if(isset($_FILES['bild']))
	{
        $path = $verzeichnis->upload('bild');
        $picadded = true;
        $resfetch = $db->getPostId($post_array['user_id'], $post_array['date']);
    }
    
    if($picadded == true)
    {
        $new_media = array();
        $new_media['post_id'] = $resfetch['post_id'];
        $new_media['path'] = $path;
        $db->insertMedia($new_media);
    } 
?>
