<?php
/**
 * Klasse um Verzeichnisse zu verwalten. (Für Bilder)
 *
*/

class Verzeichnis
{
	private $path;
	private $datentypen = [];

	public function __construct($path, $datentypen = ['jpeg', 'png', 'jpg'])
	{
		$this->path = $path;
		$this->datentypen = $datentypen;
	}

	public function upload($name)
	{
			$file = $_FILES[$name];
			$filetype = explode('/',$file['type']);
			
			if($file['error'] == 0 && in_array(end($filetype),$this->datentypen))
			{
			$splitfilename = explode('.', $file['name']);
			$filePath = $this->path .$_SESSION['user_id'].'_'. time() .'.'. end($splitfilename);
			move_uploaded_file($file['tmp_name'], $filePath);
			$current_file = new SingleFile($filePath);

			return $current_file->returnCompletePath();
			}
	}
}
?>
