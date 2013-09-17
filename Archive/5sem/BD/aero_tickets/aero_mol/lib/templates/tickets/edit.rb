"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Tickets'>
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
      <th>Номер паспорта:</th>
      <td><input type = 'text' name = 'item[passport_number]' value = '#{@item[:passport_number]}'></td>
    </tr>
    <tr>
      <th>
        Пассажир<br>
        <div style = 'margin-left: 10px;'>Фамилия:</div>
        <div style = 'margin-left: 10px;'>Имя:</div>
        <div style = 'margin-left: 10px;'>Отчество:</div>
      </th>
      <td>
        &nbsp;<br>
        <input type = 'text' name = 'item[second_name]' value = '#{@item[:second_name]}' size = '30'><br>
        <input type = 'text' name = 'item[first_name]' value = '#{@item[:first_name]}' size = '30'><br>
        <input type = 'text' name = 'item[patronymc]' value = '#{@item[:patronymc]}' size = '30'>
      </td>
    </tr>
   
    <tr>
      <th>Рейс:</th>
      <td>#{flights_select('item[flight_id]', "#{@item[:flight_id]}")}</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=Tickets&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"
