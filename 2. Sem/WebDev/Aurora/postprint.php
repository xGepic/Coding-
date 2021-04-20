<?php
/**
 * Wird auf Startseite oder unter einem Userprofil aufgerufen.
 * 
 * Startseite: Gibts alle Posts aus falls jemand eingeloggt ist, sonst nur "public" Posts.
 * Userprofil: Gibt alle Posts eines Users unter dessen Profil aus, descending (neueste oben).
 *
 * Post Informationen: Link zum einzlenen Post im Datum und Bild (falls vorhanden.)
 * Link zu User Profil im Username des Erstellers.
 *
*/

    // Default 
    if(!isset($_GET['tags']) && !isset($_GET['search']) && !isset($_GET['profile'])){
        $post_array = $db->getAllPostId($showPost, $orderBy);
        $post_array = $db->makePostArray($post_array);
    }

    // Filtert Posts (und Kommentare) nach Suchbegriff
    else if(isset($_GET['search'])){
        if(isset($_POST['suchbegriff'])){
            echo "<div class='post-bar' id='order_type_div'><div class='job_descp'><h3>Gesucht: ".$_POST['suchbegriff']."</h3></div></div>";
            $post_array_all = $db->getAllPostId($showPost, $orderBy);
            $post_array_all = $db->makePostArray($post_array_all);
            $post_array_search = $db->searchPost($_POST['suchbegriff']);
            $post_array_search = $db->makePostArray($post_array_search);
            $comment_array_search = $db->searchComment($_POST['suchbegriff']);
            $comment_array_search = $db->makePostArray($comment_array_search);

            if($comment_array_search && $post_array_search){
                $array_search = array_merge($post_array_search, $comment_array_search);
            }
            else if($comment_array_search){
                $array_search = $comment_array_search;
            }
            else if($post_array_search){
                $array_search = $post_array_search;
            }
            else{
                $array_search=false;
            }

            if($array_search){
                $post_array = array_intersect($post_array_all,$array_search);
            }
            else{
                $post_array = false;
            }
           
        }
    }

    // Filtert Posts nach Tags
    else if(isset($_GET['tags']) ){
        $tags_to = $_POST['tags'];
        if (strpos($tags_to, ",") !== false) {
            $tags_array = explode(',', $tags_to);
        }
        else{
            $tags_array = array();
            $tags_array[] = $tags_to;
        }

        $post_array_all = $db->getAllPostId($showPost, $orderBy);
        $post_array_all = $db->makePostArray($post_array_all);
        $post_array = array();

        foreach($post_array_all as $post_id){
            $post_tags = $db->getPostTags($post_id);
            $post_tags = $db->makePostArray($post_tags);
            $post_tags_string = $post_tags[0];
            if (strpos($post_tags_string, ",") !== false) {
                $post_tags_array = explode(',', $post_tags_string);
            }
            else{
                $post_tags_array = array();
                $post_tags_array[] = $post_tags_string;
            }

            if($post_tags_array){
                $vgl = array_intersect($tags_array,$post_tags_array);
                if($vgl == $tags_array){
                    $post_array[] = $post_id;
                }
            }
        }
    }

    // Alle Posts eines Users
    else if(isset($_GET['profile']))
    {
        if(!isset($_SESSION['user_id']))
        {
        $post_array = $db->getUserPost($_GET['profile'],'public');
        $post_array = $db->makePostArray($post_array);
        }
        else
        {
        $post_array = $db->getUserPost($_GET['profile'],'private');
        $post_array = $db->makePostArray($post_array);
        }
    }

    // Form die die gefilterten Posts zeigt
    if($post_array)
    {
        foreach($post_array as $post_id)
        {
            $row = $db->getSinglePost($post_id);

            $pathresult = $db->getMediaPath($row['post_id']);
            $user = $db->searchUser('id',$row['user_id']);
            echo '      
            <div class="post-bar">
                <div class="post_topbar">
                    <div class="container">
                    <div class="row">
                    <div class="col">
                    <div class="usy-dt">
                        <img src="'.$user['avatar'].'">
                        <div class="usy-name">
                            <a href="?profile='.$user['id'].'"><h3>'.$user['username'].'</h3></a>
                        </div>
                    </div>
                    </div>
                    <a href="?show='.$row['post_id'].'">  
                    <div class="col">
                    <p>'.$row['post_date'].'-'.$row['post_type'].'</p>
                    </div>
                    </a>
                    </div>
                    </div>
                </div>

                <div class="job_descp">
                    <p>'.$row['post_content'].'</p>';
                    if($pathresult)
                    {
                        echo '<img src="'.$pathresult['path'].'" class="img-fluid">';
                    }                    
echo                '<ul class="skill-tags">';
                        if($row['post_tags'] != NULL)
                        {
                            $tagsresult = explode(",",$row['post_tags']);

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
echo            '</ul>
            </div>
        </div>';
        
        }
    }
    else{
        if(!isset($_GET['profile']))
        {
            echo "Ups! Es konnte nichts der Suche entsprechendes gefunden werden!"; 
        }

    }

?>

