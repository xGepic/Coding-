<?php
/**
 * Wird aufgerufen wenn ein Post geöffnet wird
 *
 * Lädt über die Datenbank alle Informationen des Post rein
 * überprüft ob der Angemeldete User der gleiche ist wie der User, der den Post erstellt hat
 * Falls ja werden extra Optionen eingeblendet wie: Bearbeiten und Löschen
 * 
 * Es werden weiters unter dem Post die Anzahl der Likes, Dislike; Die Like Möglichkeit(falls noch nicht bewertet wurde) sowie die Kommentare eingeblendet
 * Kommentare können nur erstellt werden wenn man eingeloggt ist
 * Like oder Dislike können nur einmal pro Post abgegeben werden
 *
*/
        
        $result = $db->getSinglePost($_GET['show']);
        if($result == false)
        {
            echo "Nothing to see here";
            die();
        }
        if(!isset($_SESSION['user_id']))
        {
            goto jumpverf;
        }

        if(isset($_GET['like_info']))
        {
            include("likes/likeauswertung.php");
            header("Location:?show=".$_GET['show']."");
        }
        $checkUser = $db->searchUser('id',$_SESSION['user_id']);
        if($_SESSION['user_id'] == $result['user_id'] || $checkUser['isAdmin'] == 1)
        {
            if(isset($_GET['delPost']))
            {
                $db->deletePost($_GET['show']);
                header("Location:index.php");
            }
            if(isset($_GET['newedit']))
            {
                include("postsystem/editPost.php");
                header("Location:?show=".$_GET['show']."");
            }
        }
        jumpverf:
        if($result['post_type'] == 'private' && !isset($_SESSION['user_id']))
        {
            echo "ACCESS DENIED!";
            die();
        }
        else
        {
        $pathresult = $db->getMediaPath($result['post_id']);
        $user = $db->searchUser('id',$result['user_id']);

echo '        
            <div class="post-bar">
                <div class="post_topbar">
                    <div class="usy-dt">
                        <img src="'.$user['avatar'].'">
                        <div class="usy-name">
                            <a href="?profile='.$user['id'].'"><h3>'.$user['username'].'</h3></a>
                        </div>
                    </div>
                </div>
                <div class="job_descp">
                    <p>'.$result['post_content'].'</p>';
                    if($pathresult)
                    {
                        echo '<img src="'.$pathresult['path'].'" class="img-fluid">';
                    }                    
echo                '<ul class="skill-tags">';
                        if($result['post_tags'] != NULL)
                        {
                            $tagsresult = explode(",",$result['post_tags']);

                            foreach($tagsresult as $tag)
                            {
                                echo "<li><a>".$tag."</a></li>";
                            }
                        }	
echo                '</ul>
                </div>
                <div class="job-status-bar">
                    <ul class="like-com">';
                    include("likes/showLikes.php");
                    if(isset($_SESSION['user_id']))
                    {
                        if($db->checkLike($_SESSION['user_id'],$_GET['show']) == false)
                        {
                            include("likes/likeform.php");   
                        }
                        if($_SESSION['user_id'] == $result['user_id'] || $checkUser['isAdmin'] == 1)
                        {
                            echo "<li><a href='?show=".$_GET['show']."&editPost=true'>bearbeiten</a></li>";
                            echo "<li><a href='?show=".$_GET['show']."&delPost=true'>löschen</a></li>";
                            echo "<li><a>".$result['post_type']." - ".$result['post_date']."</a>";
                            echo "</ul>";
                            if(isset($_GET['editPost']))
                            {
                                include("postsystem/editPostForm.php");
                            }
                        }
                        echo '
                        <div class="comment-section">
                        <div class="post-comment">
                        <div class="comment_box">
                        ';
                        include("comment/commentform.php");
                        echo '</div></div></div>';
                    }
                    echo '</div></div>';
        }
        include("comment/commentprint.php");
?>
