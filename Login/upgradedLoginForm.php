<?php

function valid($fieldName)
{
   if (!isset($_POST[$fieldName])
       return false;

   $forbiddenSymbols = array('\'', '"', '--');

   foreach ($forbiddenSymbols as &$symbol)
	   if (strpos($_POST[$fieldName] , $symbol)) return false;

   return true;
}

function blocked($username)
{
   $attemptsBeforeBlocking = 3;
   $sTimeOut = 60;

   $sample   = $mysqli->query('SELECT loginTime, failsCount FROM users WHERE user =' . $username);  
   $userData = $sample->fetch_assoc();  
 
   if ($userData['failsCount'] >= $attemptsBeforeBlocking) 
      if (time() - strtotime($userData['loginTime']) < $sTimeOut)
          return true

   return false;
}

function succeed()
{
    $avatar = $row['avatar'];  

    $html .= "<p>Welcome to the password protected area {$user}</p>";  
    $html .= "<img src=\"{$avatar}\" />";  

    $mysqli->query('UPDATE users SET failsCount = 0, loginTime = ' . time() . ' WHERE user = ' . $username);  
}

function failed()
{
   $html .= "<pre><br />Username and/or password incorrect.</pre>";

   $mysqli->query('UPDATE users SET failsCount = failsCount + 1 WHERE user = ' . $username);  
}

//------------------------main---------------------------
if (!valid('username') || !valid('password') || !isset($_POST['Login']))      //CWE-89 (Lack of injection verification (validate before))
    return;                                               

$user     = $_POST['username'];                           //CWE-598 (Get with confidential data (change to POST))
$password = crypt($_POST['password'], $someSalt);         //CWE-327 (Weak crypto alg (changed to sha256)), CWE-759 (One-way hash without salt (hash with salt))

$sample  = $mysqli->query('SELECT * FROM users WHERE user = ' . $user . ' AND password = ' . $password;  
$blocked = blocked($username); //CWE-307 (Improper Restriction of Excessive Authentication Attempts (add attempts count with time restriction))

if ($sample->num_rows() == 1 && !$blocked)
    succeed();

else if (!$blocked)
    failed();

?>
