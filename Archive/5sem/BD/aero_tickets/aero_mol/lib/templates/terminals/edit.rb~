"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Terminals'>
<input type = 'hidden' name = 'action' value = 'edit'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<input type = 'hidden' name = 'item[id]' value = '#{@item[:id]}'>
<table class = 'list'>
  <caption>
    #{@header}<br>
    <span style = 'color: Red;'>#{@message}</span>
  </caption>
  <thead>
  <tbody>
    <tr>
      <th>Название посадочного терминала:</th>
      <td><input type = 'text' name = 'item[name]' value = '#{@item[:name]}'></td>
    </tr>
    <tr>
      <th>Описание:</th>
      <td><textarea name = 'item[description]'>#{@item[:description]}</textarea></td>
    </tr>
    <tr>
      <th>Необходим автобус:</th>
      <td><input type = 'checkbox' name = 'item[needs_bus]' value = '1' #{@item[:needs_bus] ? "checked = 'yes'" : ""}></td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=Terminals&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"
