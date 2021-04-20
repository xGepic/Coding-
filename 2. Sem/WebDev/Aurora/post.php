<?php
/**
 * Beinhaltet das Formular um einen Post zu erstellen
 *
 * Textfeld, Bildupload, Private/Public selection sowie eine Eingabe für Tags, die dem Pattern entsprechen müssen
 * Gesndet wird über POST mit der GET post=true
 *
*/
?>

<div class="post-bar">
    <div class="comment-section">
        <div class="post-comment">
            <div class="comment_box">
            <form action="?post=true" method="post" enctype="multipart/form-data">
            <h2>Post</h2>
            <textarea name ="content" class="form-control" rows="3" required></textarea>
            <input type="text" id="tags" name="tags" pattern="^[a-zA-Z]+(,[a-zA-Z]+)*$" placeholder="tag,tag,tag">
            <div class="custom-file">
                <input type="file" class="custom-file-input" accept="image/*" name="bild" id="my_bild">
                <label class="custom-file-label" for="my_bild">Hochladen <i class="bi bi-cloud-upload"></i></label>
            </div>
            <button type="submit" value="posten">POSTEN</button>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="post_type" id="public" value="public">
                <label class="form-check-label" for="public">
                    Public
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="post_type" id="private" value="private"checked>
                <label class="form-check-label" for="private">
                    Private
                </label>
            </div>
            </form>
            </div>
        </div>
    </div>
</div>

