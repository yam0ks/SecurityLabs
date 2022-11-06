<?php
if (isset($_GET['Submit'])) {
    $id = $_GET['id'];

    $mysql = new PDO('mysql:host=localhost;dbname=someDB', "user", "password");

    $query = $mysql->prepare("SELECT first_name, last_name FROM users WHERE user_id = :id;");
    $query->bindParam("id", $id, PDO::PARAM_INT);
    $query->execute();

    if ($query->rowCount() > 0) {
        $html .= "<pre>User ID exists in the database.</pre>";
    } else {
        header($_SERVER["SERVER_PROTOCOL"] . " 404 Not Found");
        $html .= "<pre>User ID is MISSING from the database.</pre>";
    }
}

