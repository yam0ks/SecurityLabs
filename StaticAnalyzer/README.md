# Анализ уязвимостей

## SonarCloud
![image](https://user-images.githubusercontent.com/78639838/200187776-5f379402-0fcf-4c9d-8115-fe63a9ede959.png)

**Статический анализтор выявил одну критическую ошибку, вызванную использованием переменной id непосредственно в строке запроса, что может быть использовано злоумышленниками для внедрения SQL-кода.**

____________________________________________________________________________________

## Code review

*CWE-89 - Неправильная нейтрализация специальных символов, используемых в SQL команде*

```php
$getid  = "SELECT first_name, last_name FROM users WHERE user_id = '$id';";
$result = mysqli_query($GLOBALS["___mysqli_ston"],  $getid );
```
**Исправление: Использование технологии PDO**

```php
$mysql = new PDO('mysql:host=localhost;dbname=someDB', "user", "password");

$query = $mysql->prepare("SELECT first_name, last_name FROM users WHERE user_id = :id;");
$query->bindParam("id", $id, PDO::PARAM_INT);
$query->execute();
```

*CWE-20 - Неправильная проверка ввода*

```php
$id = $_GET[ 'id' ];
```
**Исправление: Валидация переменной, в данном случае обеспечивается при помощи технологии PDO**

![image](https://user-images.githubusercontent.com/78639838/200187682-35e2a419-9ce6-455c-9d29-77c090d44c14.png)

**После добавления исправлений в код статический анализтор не выявил критических ошибок.**
