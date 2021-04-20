<?php
/**
* Session wird gestartet und die benötigten Klassen werden eingebunden
* require wurde verwendet um zu garantieren, da der weitere Verlauf des Scripts diese verwendet
* Es wird ein DatenbankObjekt erzeugt um die Anfragen auf die Datenbank zu verwalten
*/
    session_start();
    require('database/databaseauthentication.php');
    require('database/databaseclass.php');
    require('classes/userclass.php');
    require('classes/SingleFile.php');
    require('classes/verzeichnis.php');
    $db = new dbaccess($servername,$dbname,$username,$password);
/**
 * $error Variable wird verwendet um Fehlermeldungen auf dem Browser auszugeben
 * $userRegActive und $userLoginActive sind zum einblenden der Anmelde - sowie Registrierungsformulare
 * $showPost definiert welche Post dargestellt werden, wird bevor eine Session gestartet wurde auf public only gesetzt
 * $no_filter_yet schaut ob nach Tags gefiltert werden, wird mit true initialisiert
 * Es wird ein VerzeichnisObjekt für den Upload von Bildern erstellt
 */
    $error['value'] = false;
    $error['type'] = false;
    $userRegActive = true;
    $userLoginActive = true;
    $showPost = 'public_only';
    $no_filter_yet = true;
    $verzeichnis = new Verzeichnis('images/uploads/');
/**
 * Falls der User sich ausloggen wird, wird diese Abfrage als erstes behandelt
 */
    if(isset($_GET['logout']))
    {
        include_once("regandlogsystem/logout/logout.php");
    }
/**
 * Überprüft ob die Posts sortiert werden sollen, und nach was
 */
    if(isset($_GET['orderBy']) && ($_GET['orderBy'] == 'username')){
        $orderBy = 'username';  
    }
    else{
        $orderBy = 'post_date';
    }

/**
 * Überprüft ob der User angemeldet ist, wenn ja werden seine Informationen aus der Datenbank abgerufen
 * Login und Registrierung werden nicht mehr angezeigt und $showPost wird auf all gesetzt
 * 
 * Überprüft ob der angemeldete User ein Admin ist, falls ja wird hier nochmal überprüft ob der Admin eine Änderung
 * zu einem Benutzer eingegeben hat
 */
    if(isset($_SESSION['user_id']))
    {
        $result = $db->searchUser('id',$_SESSION['user_id']);
        $userLoginActive = false;
        $userRegActive = false;
        $showPost = 'all';
        if($result['isAdmin'] == 1 && isset($_GET['adminpage']))
        {
            if(isset($_GET['change']) && isset($_GET['id']))
            {
              $id = $_GET['id'];
              if($_GET['change'])
              {
                $result = $db->changeUserActivity($_GET['id']);
                header("Location:?adminpage=true");
              }
            }
        }
    }
/**
 * Falls ein einziger Post oder ein Profil angezeigt werden, wird überprüft ob der User angemeldet ist
 * Weiters entsperrt das, dann die Möglichkeit änderung an den Daten zu machen
 * Falls ein Post angezeigt wird, werden noch Möglichkeiten bezüglich des editieren/löschen/kommentieren/liken alles zur Auswertung in die Index Datei geladen
 * Falls aber nicht nur ein Profil oder ein einziger Post dargestellt wird, werden die Auswertung zu Login/Registrierung/Post geladen
 */
    if(isset($_GET['show']) || isset($_GET['profile']))
    {
        if(isset($_SESSION['user_id']))
        {
        if(isset($_GET['newdata']))
        {
            include("profilverwaltung/changeData.php");
            header("Location:?profile=".$_GET['profile']."");   
        }
        if(isset($_GET['newpassword']))
        {
            include("profilverwaltung/changePassword.php");
            if(!$error['value'])
            {
                header("Location:?profile=".$_GET['profile'].""); 
            }  
        }
        if(isset($_GET['newpic']))
        {
            include("profilverwaltung/changePicture.php");
            header("Location:?profile=".$_GET['profile']."");
        }
        if(isset($_GET['show']))
        {
        $postcheck = $db->getSinglePost($_GET['show']);
        if($_SESSION['user_id'] == $postcheck['user_id'] || $result['isAdmin'] == 1)
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
        if(isset($_GET['comment']))
        {
            include("comment/commentauswertung.php");
            header("Location:?show=".$_GET['show']."");
        }
        if(isset($_GET['like_info']))
        {
            include("likes/likeauswertung.php");
            header("Location:?show=".$_GET['show']."");
        }
        }
        }
    }
    else
    {
        if(isset($_GET['reg']))
        {
            include('regandlogsystem/registration/regAuswertung.php');
        }
        if(isset($_GET['login']))
        {
            include('regandlogsystem/login/login.php');
        }
        if(isset($_GET['post']))
        {
            include('postsystem/postAuswertung.php');
            header("Location:index.php");
        }
    }
/**
 * Soll bei einem Fehler die Fehlermeldung ausgeben
 */
    if($error['value'] == true)
    {
        echo $error['type'];
    }
?>

<!DOCTYPE html>
<html lang="de">
<head>
<title>Aurora</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
<link rel="stylesheet" type="text/css" href="css/style.css">
<link rel="stylesheet" type="text/css" href="css/bootstrap-icons-1.3.0/bootstrap-icons.css">
<script type="text/javascript" src="js/jquery.min.js"></script>
<script type="text/javascript" src="js/script.js"></script>
</head>
<body>
<div class="wrapper">
<header class="navbar navbar-inverse navbar-fixed-top">
			<div class="container">
				<div class="header-data">
					<div class="search-bar">
                        <form action="?search=true" method="post">
                            <input type="hidden" name="aktion" value="suchen">
                            <input type="text" name="suchbegriff" id="suchbegriff" placeholder="Suche">
                            <button type="submit" value="suchen"><i class="bi bi-search"></i></button>
                        </form>
					</div>
					<nav>
						<ul>
                            <li>
                                <span><img src="" alt=""></span>
                                <?php 
                                if(isset($_SESSION['user_id']) && $result['isAdmin'] == 1)
                                {
                                    echo "<a href=?adminpage=true>AdminPage</a>";
                                }
                                ?>
                            </li>
							<li>
								<a href="index.php" title="">
                                    <i><i class="bi bi-house"></i>
                                </a>
							</li>
							<li>
                                <span><img src="" alt=""></span>
                                <?php 
                                if(isset($_SESSION['user_id']))
                                {
                                    echo "<a href='?profile=".$_SESSION['user_id']."'>Profile</a>";
                                }
                                ?>
							</li>
							<li>
								<a href="#" title="">
									<span><img src="" alt=""></span>
									<a href="?impr=true">Impressum/Kontakt</a>
								</a>
							</li>
							<li>
								<a href="#" title="">
									<span><img src="" alt=""></span>
									<a href="?help=true">Hilfe</a>
								</a>
							</li>
						</ul>
                    </nav>
                    <?php if(isset($_SESSION['user_id']))
                    {
                    echo '
					<div class="user-account">
						<div class="user-info">
							<img src="'.$result['avatar'].'" alt="">
							<a href="#" title="">'.$result['username'].'</a>
						</div>
						<div class="user-account-settingss">
							<ul class="us-links">
								<li><a href="?profile='.$_SESSION['user_id'].'" title="">Account</a></li>
								<li><a href="?help=true" title="">Hilfe</a></li>
							</ul>
							<h3 class="tc"><a href="?logout=true" title="">Logout</a></h3>
                        </div>
                    ';}?>
					</div>
				</div>
			</div>
		</header>
<main>
    <div class="main-section">
        <div class="container">
            <div class="main-section-data">
                <div class="row">
                    <?php if(isset($_SESSION['user_id']))
                    {
                    $anzahl = $db->countPost($_SESSION['user_id']);
                    echo '
                    <div class="col-lg-3 col-md-4 pd-left-none no-pd">
                        <div class="main-left-sidebar no-margin">
                            <div class="user-data full-width">
                                <div class="user-profile">
                                    <div class="username-dt">
                                        <div class="usr-pic">
                                            <img src='.$result['avatar'].'>
                                        </div>
                                    </div>
                                    <div class="user-specs">
                                        <h3>'.$result['username'].'</h3>
                                        <span>'.$result['vorname'].' '.$result['nachname'].'</span>
                                    </div>
                                    <ul class="user-fw-status">
                                        <li>
                                            <h4>Posts</h4>
                                            <span>'.$anzahl[0].'</span>
                                        </li>
                                    </ul>
                                </div>
                            </div>
                        </div>
                    </div>';
                    }?>
                    <div class="col-lg-6 col-md-8 no-pd">
                        <div class="main-ws-sec">
                            <div class="post-section">
    <?php
/**
 * Falls das Impressum oder die Hilfeseite geladen werden sollen
 */
        if(isset($_GET['impr']))
        {
            include("impressum/Impressum.php");
        }
        if(isset($_GET['help']))
        {
            include("impressum/Help_Center.php");
        }
/**
 * Falls der angemeldete User ein Admin ist und auf die Adminseite geklickt hat
 */
        if(isset($_SESSION['user_id']))
        {
            $resAdmin = $db->searchUser('id',$_SESSION['user_id']);
            if($resAdmin['isAdmin'] == 1 && isset($_GET['adminpage']))
            {
                include('admin/userverwaltung.php');
            }
        }
/**
 * Falls auf ein Profil geklickt wurde
 */
        if(isset($_GET['profile']))
        {
            include('profilverwaltung/manageUser.php');
            if(!isset($_GET['changedata']) && !isset($_GET['changepassword']) && !isset($_GET['managepic']))
            {
                include('postsystem/postprint.php'); 
            }

        }
/**
 * Falls auf ein Post geklickt wurde
 */
        if(isset($_GET['show']))
        {
            include('postsystem/singlepost.php');
        }        
/**
 * Falls keine spezielle Seite ausgewählt wurde, werden Postformular/Filter/Sortieren/sowie alle Posts angezeigt
 */
        if(!isset($_GET['show']) && !isset($_GET['profile']) && !isset($_GET['adminpage']) &&!isset($_GET['impr']) &&!isset($_GET['help']))
        {        
        if(isset($_SESSION['user_id']))
        {
                include('postsystem/post.php');
        }
        if($no_filter_yet)
        {
            $post_array_all = $db->getAllPostId($showPost, $orderBy);
            $post_array_all = $db->makePostArray($post_array_all);
            $no_filter_yet=false;
        }
        echo '<div class="post-bar">
            <div class="job_descp" id="order_type_div">
            <label for="order_type">SORTIEREN</label>
            <div class="row">
            <div class="col">
            <form action="?orderBy=date" method="post" id="order_type">
            <button class="btn btn-outline-dark btn-sm" type="submit" value="Date">Datum</button>
            </form>
            </div>
            <div class="col">
            <form action="?orderBy=username" method="post" id="order_type"> 
                <button class="btn btn-outline-dark btn-sm" type="submit" value="username">Username</button>
            </form>
            </div>
            </div>
            </div>
            </div>';

        echo '<div class="post-bar">
            <div class="job_descp" id="order_type_div">
            <form action="?tags=true" method="post">
                Tag-Suche: 
                <input type="hidden" name="aktion" value="tags">
                <input type="text" name="tags" id="tags" pattern="^[a-zA-Z]+(,[a-zA-Z]+)*$">
                <button class="btn btn-outline-dark btn-sm" type="submit" value="tags">Tags</button>
            </form>';
            if(!$no_filter_yet)
            {
                echo "<a id='make_purple' href='index.php'>Filter zurücksetzten</a>";
            } 
            echo'
            </div>
            </div>';      

            include('postsystem/postprint.php');
        }
    ?>
                            </div>
                        </div>
                    </div>
                    <?php if(!isset($_SESSION['user_id']))
                    {
                    echo '
                    <div class="col-lg-3 col-md-4 pd-left-none no-pd">
                        <div class="main-left-sidebar no-margin">
                            <div class="user-data full-width">
                            <div class="job_descp">';
                            if($userRegActive == true)
                            {
                                include('regandlogsystem/registration/registerUser.php');
                            }
                            echo '</div><div class="job_descp">';
                            if($userLoginActive == true)
                            {
                                include('regandlogsystem/login/loginUser.php');
                            }
                            echo '</div></div>
                        </div>
                    </div>';
                    }?>
                </div>
            </div>
        </div>
    </div>
</main>
</div>
</body>
</html>
