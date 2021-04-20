<?php
/**
 * Wird unter einzelnem Post aufgerufen.
 * Form für Likes und Dislikes, funktioniert mittels GET. 
 *
*/
?>

<li>
<form action="?show=<?php echo$_GET['show'];?>&like_info=like" method="post" enctype="multipart/form-data">
    <button type="submit" value="LIKE" class="btn btn-danger">
    <i class="bi bi-heart"></i>
    </button>
</form>
</li>
<li>
<form action="?show=<?php echo$_GET['show'];?>&like_info=dislike" method="post" enctype="multipart/form-data">
    <button type="submit" value="DISLIKE" class="btn btn-dark">
    <i class="bi bi-hand-thumbs-down"></i>
    </button>
</form>
</li>
