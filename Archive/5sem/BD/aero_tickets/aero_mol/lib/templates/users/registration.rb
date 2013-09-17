"
<form name = 'registration' method = 'post' action = 'aero.rb'>
<input type = 'hidden' name = 'controller' value = 'Users'>
<input type = 'hidden' name = 'action' value = 'registration'>
<input type = 'hidden' name = 'is_commit' value = 'true'> 
 <table class = 'list'>
<caption>
#{@header}<br>
<span style = 'color: Red;'>#{@message}</span>
</caption>
    <tbody>
      <tr>
        <th>Пользовательское имя:</th>
        <td><input type = 'text' name = 'login' value = ''></td>
      </tr>
      <tr>
        <th>Пароль:</th>
        <td><input type = 'password' name = 'password' value = ''></td>
      </tr>
      <tr>
        <th>Введите пароль снова:</th>
        <td><input type = 'password' name = 'password1' value = ''></td>
      </tr>
      <tr>
        <th>Email:</th>
        <td><input type = 'text' name = 'mail' value = ''></td>
      </tr>
      <tr>
        <th colspan = '2'><input type = 'submit' value = 'registration'></th>
      </tr>
    </tbody>
  </table>
</form>
"
