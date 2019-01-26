<?php

// A simple mysql connection function with PDO

  function mysql_conn($user,$pass,$host,$query) {
  
        if (empty($user) or empty($pass)) {
            echo "User or password not set";
            die();
        }
        else if (empty($host) or empty($query)) {
          echo "Host or query not set";
          die();
        }
        else {
          try {
            $conn = new PDO("mysql:host={$host};dbname={$db}",$user,$pass);
           } catch (PDOException $e) {
                  die("Error: " . $e->getMessage());
              }

          $conn->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
          $conn->exec("SET NAMES utf8");

          $query = $conn->prepare("{$query}");
          $query->execute();
      }
    }
?>
             
