<?php
  /* Simple function to call and hash a string with 
  default password_hash function settings */
  
	function hash_string($to_string) {
		
		if (empty($to_string)) {
			echo "String can't be hashed since there's no input";
			die();
		}
		
		else {
			$hashed = password_hash($to_string,PASSWORD_DEFAULT);
			return $hashed;
		}
		
	}

?>
