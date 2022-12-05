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

## SqlMap

**Добавим в Burp новый адрес и порт прослушивания HTTP-пакетов.**

![image](https://user-images.githubusercontent.com/78639838/205710794-b9c888b6-3d8f-4510-a7b9-f49226ed4e1b.png)

**В браузере укажем в качестве proxy-сервера выбранный ранее адрес и порт.**

![image](https://user-images.githubusercontent.com/78639838/205711406-d20d3907-f1be-4310-8c6e-48aaed8ccdb1.png)

**Отправим запрос в форму задания blind-injection, после чего в Burp сможем наблюдать перехваченный HTTP-пакет с заголовками.**

![image](https://user-images.githubusercontent.com/78639838/205711543-05ae1b68-0a4d-4981-9c3f-e4fa56961875.png)

**Воспользуемся утилитой SQLmap для поиска уязвимых параметров запроса. 
В результате поиска утилита выявила уязвимости типа boolean-based blind и time-based blind у параметра id.**

![image](https://user-images.githubusercontent.com/78639838/205712284-1491d3b2-8993-411c-a184-d711a1736f50.png)

**При помощи утилиты sqlmap получим список имеющихся баз данных.**

![image](https://user-images.githubusercontent.com/78639838/205712183-cbb6a147-1e37-49ac-af43-395615d1f205.png)

**При помощи утилиты sqlmap получим список имеющихся таблиц базы данных dvwa.**

![image](https://user-images.githubusercontent.com/78639838/205712808-aba4959b-1480-4b14-8b5d-f8c1d98417a7.png)

**При помощи утилиты sqlmap получим строки из таблицы users.**

![image](https://user-images.githubusercontent.com/78639838/205713253-901043f3-c700-4321-a991-ba70815f8054.png)

**В ходе получения строк таблицы утилита sqlmap осуществила перебор паролей по имеющимся в таблице хэшам, в результате чего смогла определить пароли пользователей.**

![image](https://user-images.githubusercontent.com/78639838/205713311-4b74f8d5-9112-45c6-af2b-7ca2c74f0bfe.png)

## Burp

**Включим перехват пакетов в Burp и осуществим отправку запроса в форме dvwa. В результате в Burp сможем наблюдать перехваченный HTTP-пакет.**

![image](https://user-images.githubusercontent.com/78639838/205756421-2a42425c-a249-402c-a62f-cf4ee9ca5e6c.png)

**Изменим тело запроса, указав для параметра id значение _1 OR 1=1#_.**

![image](https://user-images.githubusercontent.com/78639838/205756540-aaa5df19-d9db-4a50-95c8-b9a76c8df46e.png)

**В результате для каждого из имеющихся в базе данных значений id было возвращено true, и информация о всех пользователях, находящихся в таблице, помещена на странице сайта.**

![image](https://user-images.githubusercontent.com/78639838/205756621-3f267b3e-162e-42b8-9bfc-f5400fe12c20.png)

**Попробуем получить информацию об имеющихся в базе данных таблицах. Для этого в качестве значения для параметра id впишем _1 OR 1=1 UNION SELECT NULL,TABLE_NAME FROM INFORMATION_SCHEMA.TABLES#_**

![image](https://user-images.githubusercontent.com/78639838/205757007-14cac63f-9af9-473b-bcf4-ea5cad909818.png)

**В ответ на данный запрос, как и ожидалось, на странице отобразились все имеющиеся в базе данных таблицы.**

![image](https://user-images.githubusercontent.com/78639838/205757051-ce35f5fd-c412-4c45-bfaf-9f13ec65086b.png)

**Наконец, попробуем получить логины и пароли пользователей, отправив запрос к таблице users: _1 OR 1=1 UNION SELECT USER,PASSWORD FROM users#_.**

![image](https://user-images.githubusercontent.com/78639838/205758287-68dea91a-e5e0-4300-896a-592d50bfa429.png)

**В результате можем наблюдать полученные логины пользователей, а также захэшированные пароли.**

![image](https://user-images.githubusercontent.com/78639838/205757656-fdf48531-0dc3-4aef-8899-a81df35a011b.png)
