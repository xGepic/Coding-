<?php
/**
 * Wird aufgerufen um einen Kommentar zur Datenbank hinzuzufügen der mittels Formular (POST) abgeschickt wurde.
 *
*/

    $comment_array = array();
    
    $comment_array['user_id'] = $_SESSION["user_id"];
    $comment_array['text'] = $_POST['content'];
    $comment_array['date'] = date('Y-m-d H:i:s');
    $comment_array['post_id'] = $_GET['show'];

    $db->addComment($comment_array);
?>
