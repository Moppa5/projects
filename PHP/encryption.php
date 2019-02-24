<?php
        /* This is just an easy encryption function for PHP using openssl library.
           $str here is the string to be encrypted and $cipher is obviously the 
           method with which you want to perform the encryption 
           
           Key and iv are generated with random pseudo bytes => you should always
           use cryptographically secure values if you're encrypting for example. */
   
        function encryption($str,$cipher="aes-256-cbc") {
        
                $key = openssl_random_pseudo_bytes(32);
                $ivlen = openssl_cipher_iv_length($cipher);
                $iv = openssl_random_pseudo_bytes($ivlen);
                $encrypted = openssl_encrypt($str,$cipher,$key,0,$iv);
                /* could be base64_encode'd here
                   key and iv are required for decryption */

                return $encrypted;
        }
?>
