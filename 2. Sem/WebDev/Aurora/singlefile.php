<?php
/**
 * Klasse um einzelne Files zu verwalten. (Für Bilder)
 *
*/
	class SingleFile
	{
		public $filename;
		public $path;
		public $datatype;

		public function __construct($path)
		{
			$info = pathinfo($path);
			$this->filename = $info['basename'];
			$this->datatype = $info['extension'];
			$this->path = $info['dirname'].'/';
		}

		public function returnCompletePath()
		{
			return $this->path.$this->filename;
		}
	}
