<?php
/**
 * Wird unter einem Post aufgerufen.
 * Gibt Icons und Anzahl für Likes und Dislikes aus. 
 *
*/

    $like_info = array();
    $count = 0;
    if(isset($_GET['show']))
    {
        $like_info = $db->countLikes($_GET['show']); 
    }
    else
    {
        $like_info = $db->countLikes($row['post_id']);
    }

    foreach($like_info as $row)
    {
        if($count == 0)
        {
            echo "<li>
            <a id='my_heart'><i class='bi bi-heart-fill'> ".$row['0']."</i></a>
            </li>";
            $count++;
        }
        else
        {
            echo "<li>
            <a id='my_dislike'><i class='bi bi-hand-thumbs-down-fill'> ".$row['0']."</i></a>
            </li>";
        }
    }
?>
