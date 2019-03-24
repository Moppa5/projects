<?php
 /* Simple MySQL connector function which uses PDO
    to connect to the server */

        function sql_conn($db,$query) {

                if (empty($db) or empty($query)) {
                        echo "Database or query is empty";
                        die();
                } else { // Conn try
                        // Requires login data

                        // $path is data file for sql user and pass
                        if (!file_exists($path)) {
                                echo "Data file couldn't be read";
                        die();
                        } else {
                        // file could be read, now begin the data reading

                        /* This is example for reading user, pass from a file where they're presented
                           like user:pass:something_else
                           
                        $file_row = file($path);
                        $data = $file_row[0];

                        $all_data = explode(":",$data);

                        $user = $all_data[0];
                        $pass = $all_data[1];
                        */ 

                        try {
                        $conn = new PDO("mysql:host=localhost;dbname={$db}",$user,$pass);
                        } catch(PDOException $e) {
                                die("Error: " . $e->getMessage());
                        }
                        $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
                        $conn->exec("SET NAMES utf8");

                        $q = $conn->prepare("{$query}");
                        $q->execute();
                        }
                  
                }
        }
?>
