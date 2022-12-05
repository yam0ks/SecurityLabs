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

____________________________________________________________________________________

## SqlMap + Burp

**Добавим в Burp новый адрес и порт прослушивания HTTP-пакетов.**

![image](https://user-images.githubusercontent.com/78639838/205710794-b9c888b6-3d8f-4510-a7b9-f49226ed4e1b.png)

**В браузере укажем в качестве proxy-сервера выбранный ранее адрес и порт.**

![image](https://user-images.githubusercontent.com/78639838/205711406-d20d3907-f1be-4310-8c6e-48aaed8ccdb1.png)

**Отправим запрос в форму задания blind-injection, после чего в Burp сможем наблюдать перехваченный HTTP-пакет с заголовками.**

![image](https://user-images.githubusercontent.com/78639838/205711543-05ae1b68-0a4d-4981-9c3f-e4fa56961875.png)

**Воспользуемся утилитой SQLmap для поиска уязвимых параметров запроса. 
В результате поиска утилита выявила уязвимости типа boolean-based blind и time-based blind у параметра id.**

![image](https://user-images.githubusercontent.com/78639838/205712284-1491d3b2-8993-411c-a184-d711a1736f50.png)

**При помощи утилиты SQLmap получим список имеющихся баз данных.**

![image](https://user-images.githubusercontent.com/78639838/205712183-cbb6a147-1e37-49ac-af43-395615d1f205.png)

**При помощи утилиты SQLmap получим список имеющихся таблиц базы данных dvwa.**

![image](https://user-images.githubusercontent.com/78639838/205712808-aba4959b-1480-4b14-8b5d-f8c1d98417a7.png)

**При помощи утилиты SQLmap получим строки из таблицы users.**

![image](https://user-images.githubusercontent.com/78639838/205713253-901043f3-c700-4321-a991-ba70815f8054.png)

**В ходе получения строк таблицы утилита SQLmap осуществила перебор паролей по имеющимся в таблице хэшам, в результате чего смогла определить пароли пользователей.**

![image](https://user-images.githubusercontent.com/78639838/205713311-4b74f8d5-9112-45c6-af2b-7ca2c74f0bfe.png)
