<?php
/**
 * Wird aufgerufen um einen Like oder Disklike zur Datenbank hinzuzufügen der mittels GET abgeschickt wurde.
 *
*/

    $like_array = array();
    
    $like_array['user_id'] = $_SESSION["user_id"];
    $like_array['like_info'] = $_GET['like_info'];
    $like_array['post_id'] = $_GET['show'];

    $db->likePost($like_array);
?>
