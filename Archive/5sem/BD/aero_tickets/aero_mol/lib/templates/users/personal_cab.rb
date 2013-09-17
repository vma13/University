"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Users'>
<input type = 'hidden' name = 'action' value = 'personal_cab'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<table class = 'list'>
<caption>
Пользователь: #{@user}
#{@header}<br>
<span style = 'color: Red;'>#{@message}</span>
</caption>
	<tbody>
    <tr>
      <th>Сменить пароль:</th>
      <td><input type = 'password' name = 'new_password' value = ''></td>
    </tr>
    <tr>
      <th>Сменить email:</th>
      <td><input type = 'text' name = 'new_mail' value = ''></td>
    </tr>
    <tr>
      <th colspan = '2'><input type = 'submit' name = 'delete' value = 'Удалить данного пользователя'></th>
    </tr>
    <tr>
      <th colspan = '2'><input type = 'submit' value = 'Внести изменения'></th>
    </tr>
	</tbody>
</table>
</form>
"
