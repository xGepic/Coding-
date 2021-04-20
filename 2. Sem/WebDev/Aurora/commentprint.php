<?php
/**
 * Erscheint wenn ein einzelner Post aufgerufen wird unter dem Kommentar-hinzufügen Formular.
 *
 * Gibt alles kommentare zum Post aus, descending (neuestes Kommentar ganz oben).
 *
*/

    $result = $db->getComments($_GET['show']);
    if($result)
    {
    foreach($result as $row)
    {
        $user = $db->searchUser('id',$row['user_id']);
        echo "
        <table class='table'>
        <tr>
        <td><p id='changeColor'>".$row['comment_date']." - <a href='?profile=".$user['id']."'>".$user['username']."</a></td>
        </tr>
        <tr>
        <td><p>".$row['comment_content']."</p></td>
        </tr>
        </table>";
        
    }
    }
?>
