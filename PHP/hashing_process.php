<?php
  
  /* This PHP script is for showing how to use in a easy way 
     PHP's password_*() functions */

// How to hash password
$password = "ThisIsSomeRandomPassword";
$hashed = password_hash($password,PASSWORD_DEFAULT); // default is a good choice if you don't need a specific

// How to verify input

$input = "ThisIsNotSomeRandomPassword";

  if (password_verify($input, $hashed)) {
        echo "Valid password";
  } else {
        echo "Invalid password";
  }

// Check if the hashed password is strong enough

  if (password_verify($input, $hashed)) {
        echo "Valid password";
    
    // Let's check the $hashed is strong enough
    
    if (password_needs_rehash($hashed,PASSWORD_DEFAULT)) {
        $new_hash = password_hash($input, PASSWORD_DEFAULT);
    }
    // Now you could prompt user to page after login
    
  } else {
        echo "Invalid password";
        
  }



  
