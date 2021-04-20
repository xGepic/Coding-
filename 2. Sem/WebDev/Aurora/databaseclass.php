<?php
/**
 * Klasse für alle Anfragen an die Datenbank.
 *
*/

    class dbaccess
    {
        public $connection;
        
        public function __construct($host,$database,$user,$pass)
        {
            $this->connection = new PDO("mysql:host=$host;dbname=$database;charset=utf8","$user","$pass");
        }

        /**
         * Fügt übergebene Daten mittels SQL Befehl in Datenbank ein.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function insertUser(array $data)
        {
            $statement = $this->connection->prepare("INSERT INTO userdata (anrede,vorname,nachname,email,username,password) VALUES (:anrede, :vorname, :nachname, :email, :username, :password)");
            $result = $statement->execute($data);
            
            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach einem User. 
         * Gibt bei Erfolg die Userdaten zurück, sonst False.
         *
        */
        public function searchUser($type,$data)
        {
            $statement = $this->connection->prepare("SELECT * FROM userdata WHERE $type = :$type");
            $result = $statement->execute(array("$type" => $data));
            $resfetch = $statement->fetch();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach allen Usern die nicht Admin sind. 
         * Gibt bei Erfolg die Userdaten zurück, sonst False.
         *
        */
        public function getAllUser()
        {
            $statement = $this->connection->prepare("SELECT * FROM userdata WHERE isAdmin = '0'");
            $result = $statement->execute();
            $resfetch = $statement->fetchAll();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Ändert mittels SQL Befehl den Aktivitätsstatus eines Users.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function changeUserActivity($user_id)
        {
            $statement = $this->connection->prepare("UPDATE userdata SET active = active ^ 1 WHERE id = :user_id");
            $result = $statement->execute(array('user_id' => $user_id));

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Fügt übergebene Daten mittels SQL Befehl in Datenbank ein.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function insertPost(array $data)
        {
            $statement = $this->connection->prepare("INSERT INTO post (user_id, post_content, post_date, post_type, post_tags) VALUES (:user_id, :text, :date, :type, :tags)");
            $result = $statement->execute($data);

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach einer PostID. 
         * Gibt bei Erfolg die Post-Daten zurück, sonst False.
         *
        */
        public function getPostId($user_id,$date)
        {
            $statement = $this->connection->prepare("SELECT post_id FROM post WHERE user_id = :user_id AND post_date = :date");
            $result = $statement->execute(array(':user_id' => $user_id, ':date' => $date));
            $resfetch = $statement->fetch();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach allen Posts eines Users. 
         * Gibt bei Erfolg die Post-Daten zurück, sonst False.
         *
        */
        public function getUserPost($user_id,$post_type)
        {
            if($post_type == 'private')
            {
            $statement = $this->connection->prepare("SELECT post_id FROM post WHERE user_id = :user_id  ORDER BY post_date DESC");
            $result = $statement->execute(array(':user_id' => $user_id));
            $resfetch = $statement->fetchAll();
            }
            else
            {
                $statement = $this->connection->prepare("SELECT post_id FROM post WHERE user_id = :user_id AND post_type = 'public' ORDER BY post_date DESC");
                $result = $statement->execute(array(':user_id' => $user_id));
                $resfetch = $statement->fetchAll(); 
            }

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Fügt übergebene Daten mittels SQL Befehl in Datenbank ein.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function insertMedia(array $data)
        {
            $statement = $this->connection->prepare("INSERT INTO media(post_id, path) VALUES (:post_id, :path)");
            $result = $statement->execute($data);

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach einem bestimmten Post. 
         * Gibt bei Erfolg die Post-Daten zurück, sonst False.
         *
        */
        public function getSinglePost($post_id)
        {
            $statement = $this->connection->prepare("SELECT DISTINCT * FROM post WHERE post_id =:post_id");
            $result = $statement->execute(array('post_id' => $post_id));
            $resfetch = $statement->fetch();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach allem Posts.
         * Je nachdem wonach geordnet werden soll und ob public oder private werden verschiedene Abfragen getätigt. 
         * Gibt bei Erfolg die PostIDs zurück, sonst False.
         *
        */
        public function getAllPostId($type, $order)
        {
            if($type == 'public_only')
            {
                if($order == 'post_date'){
                    $statement = $this->connection->prepare("SELECT post_id FROM post WHERE post_type = 'public' ORDER BY post_date DESC");
                    $result = $statement->execute();
                    $resfetch = $statement->fetchAll();

                    if($resfetch)
                    {                        
                        return $resfetch;
                    }
                    else
                    {
                        return false;
                    }
                }
                else if($order == 'username'){
                    $statement = $this->connection->prepare("SELECT post_id FROM post JOIN userdata ON user_id = id WHERE post_type = 'public' ORDER BY username");
                    $result = $statement->execute();
                    $resfetch = $statement->fetchAll();

                    if($resfetch)
                    {                        
                        return $resfetch;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else if($type == 'all')
            {
                if($order == 'post_date'){
                    $statement = $this->connection->prepare("SELECT post_id FROM post ORDER BY post_date DESC");
                    $result = $statement->execute();
                    $resfetch = $statement->fetchAll();

                    if($resfetch)
                    {
                        return $resfetch;
                    }
                    else
                   {
                        return false;
                    }
                }
                else if($order == 'username'){
                    $statement = $this->connection->prepare("SELECT post_id FROM post JOIN userdata ON user_id = id ORDER BY username");
                        $result = $statement->execute();
                        $resfetch = $statement->fetchAll();

                        if($resfetch)
                        {
                            return $resfetch;
                        }
                        else
                       {
                            return false;
                        }
                }
                
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach allen Posts die in ihrem Content den Suchbegriff enthalten. 
         * Gibt bei Erfolg die PostIDs zurück, sonst False.
         *
        */
        public function searchPost($search){
            $statement = $this->connection->prepare("SELECT post_id FROM post WHERE post_content LIKE '%$search%'");
            $result = $statement->execute();
            $resfetch = $statement->fetchAll();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach den Tags eines Posts. 
         * Gibt bei Erfolg die Tags zurück, sonst False.
         *
        */
        public function getPostTags($id){
            $statement = $this->connection->prepare("SELECT post_tags FROM post WHERE post_id=$id");
            $result = $statement->execute();
            $resfetch = $statement->fetchAll();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach allen Kommentaren die in ihrem Content den Suchbegriff enthalten. 
         * Gibt bei Erfolg die PostIDs zurück, sonst False.
         *
        */
        public function searchComment($search){
            $statement = $this->connection->prepare("SELECT DISTINCT post_id FROM comment WHERE comment_content LIKE '%$search%'");
            $result = $statement->execute();
            $resfetch = $statement->fetchAll();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Macht aus den Ergebnis einer SQL Suchanfrage ein eindimensionales Array mit den Ergebnissen.
         * Gibt, falls die Lsite nicht leer ist, das Array zurück, sonst False.
         *
        */
        public function makePostArray($list_posts){
            $return_array = array();

            if($list_posts != NULL){
                foreach($list_posts as $post_id_array)
                {
                    $post_id = $post_id_array[0];
                    $return_array[] = $post_id;
                }
            }
            else{
                return false;
            }

            return $return_array;
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach dem Bild Path eines bestimmten Posts. 
         * Gibt bei Erfolg den Path zurück, sonst False.
         *
        */
        public function getMediaPath($post_id)
        {
            $post_id_array = array();
            $post_id_array['post_id'] = $post_id;
            $statement = $this->connection->prepare("SELECT path FROM media WHERE post_id = :post_id");
            $result = $statement->execute($post_id_array);
            $resfetch = $statement->fetch();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Fügt übergebene Daten mittels SQL Befehl in Datenbank ein.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function addComment(array $data)
        {
            $statement = $this->connection->prepare("INSERT INTO comment(post_id,user_id,comment_content,comment_date) VALUES (:post_id,:user_id,:text,:date)");
            $result = $statement->execute($data);

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach allen Kommentaren zu einem bestimmten Post. 
         * Gibt bei Erfolg die Kommentare zurück, sonst False.
         *
        */
        public function getComments($post_id)
        {
            $statement = $this->connection->prepare("SELECT * FROM comment WHERE post_id = :post_id ORDER BY comment_date DESC");
            $result = $statement->execute(array('post_id' => $post_id));
            $resfetch = $statement->fetchAll();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Fügt übergebene Daten mittels SQL Befehl in Datenbank ein.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function likePost(array $data)
        {
            $statement = $this->connection->prepare("INSERT INTO like_table(post_id,user_id,like_info) VALUES (:post_id,:user_id,:like_info)");
            $result = $statement->execute($data);

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Zählt mittels SQL Abfrage in der Datenbank die Anzahl der Likes und Dislikes. 
         * Gibt sie in einem Array zurück.
         *
        */
        public function countLikes($post_id)
        {
            $like_info = array();
            $statement = $this->connection->prepare("SELECT COUNT(like_info) FROM like_table WHERE post_id = :post_id AND like_info = 'like'");
            $result = $statement->execute(array('post_id' => $post_id));
            $resfetch = $statement->fetch();
            $like_info['like'] = $resfetch;

            $statement = $this->connection->prepare("SELECT COUNT(like_info) FROM like_table WHERE post_id = :post_id AND like_info = 'dislike'");
            $result = $statement->execute(array('post_id' => $post_id));
            $resfetch = $statement->fetch();
            $like_info['dislike'] = $resfetch;

            return $like_info;
        }

        /**
         * Sucht mittels SQL Abfrage in der Datenbank nach einem Like das von einem bestimmten User an einen bestimmten Post vergeben wurde. 
         * Gibt bei Erfolg den EIntrag in der like_table zurück, sonst False.
         *
        */
        public function checkLike($user_id,$post_id)
        {
            $statement = $this->connection->prepare("SELECT 1 FROM like_table WHERE post_id = :post_id AND user_id = :user_id");
            $result = $statement->execute(array('user_id' => $user_id, 'post_id' => $post_id));
            $resfetch = $statement->fetch();
            if($result)
            {
                return $resfetch;
            }
            else
            {
                return false;
            }
        }

        /**
         * Ändert mittels SQL Befehl die Daten eines Users.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function updateUser(array $data)
        {
            $statement = $this->connection->prepare("UPDATE userdata SET anrede= :anrede, vorname = :vorname, nachname = :nachname WHERE id = :user_id");
            $result = $statement->execute($data);

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Ändert mittels SQL Befehl das Passwort eines Users.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function updatePassword(array $data)
        {
            $statement = $this->connection->prepare("UPDATE userdata SET password = :password WHERE id = :user_id");
            $result = $statement->execute($data);

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
        /**
         * Ändert mittels SQL Befehl den Profilbild Path eines Users.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function changeAvatar(array $data)
        {
            $statement = $this->connection->prepare("UPDATE userdata SET avatar = :path WHERE id = :user_id");
            $result = $statement->execute($data);

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Ändert mittels SQL Befehl einen Post.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function modifyPost($post_id, $text,$post_type)
        {
            $statement = $this->connection->prepare("UPDATE post SET post_content = :post_content, post_type = :post_type WHERE post_id = :post_id");
            $result = $statement->execute(array('post_content' => $text, 'post_type' => $post_type, 'post_id' => $post_id));

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Löscht mittels SQL Befehl einen Post in der Datenbank.
         * Gibt True oder False zurück je nach Erfolg.
         *
        */
        public function deletePost($post_id)
        {
            $statement = $this->connection->prepare("DELETE FROM post WHERE post_id = :post_id");
            $result = $statement->execute(array('post_id' => $post_id));

            if($result)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Zählt mittels SQL Abfrage in der Datenbank die Anzahl der Posts die von einem bestimmten User erstellt wurden. 
         * Gibt bei Erfolg das Ergebnis zurück, sonst Null(Zahl).
         *
        */
        public function countPost($user_id)
        {
            $statement = $this->connection->prepare("SELECT COUNT(post_id) FROM post WHERE user_id = :user_id");
            $result = $statement->execute(array('user_id' => $user_id));
            $resfetch = $statement->fetch();

            if($resfetch)
            {
                return $resfetch;
            }
            else
            {
                return 0;
            }
        }
    }
?>
