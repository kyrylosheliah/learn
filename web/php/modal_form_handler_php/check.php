<!DOCTYPE html>
<html lang="ua">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link href="assets/css/bootstrap.min.css" rel="stylesheet">
	<link href="assets/css/style.css" rel="stylesheet">
	<style>
		body>*{
			margin: 16px auto;
		}
		td{
			padding: 4px 16px;
		}
	</style>
</head>
<body class="d-flex flex-column align-items-center p-5">
	<?php
	$required = array('inputFirstName', 'inputSecondName', 'inputThirdName', 'inputEmail', 'inputPassword');
	$formFilled = true;
	foreach ($required as $field) { if (empty($_POST[$field])) { $formFilled = false; } }

	if ($formFilled) {
		print("<h1 style='color:#3f7f1f;'>Отримано дані форми:</h1><table>");
		print("<tr><td>Ім'я: </td><td>".$_POST['inputFirstName']."</td></tr>");
		print("<tr><td>Фамілія: </td><td>".$_POST['inputSecondName']."</td></tr>");
		print("<tr><td>По батькові: </td><td>".$_POST['inputThirdName']."</td></tr>");
		print("<tr><td>Email: </td><td>".$_POST['inputEmail']."</td></tr>");
		print("<tr><td>Пароль: </td><td>".$_POST['inputPassword']."</td></tr>");
		print("</table>");
	} else {
		print("<h1 style='color:#7f1f1f;'>Форму не заповнено</h1>");
	}
	?>
</body>
</html>
