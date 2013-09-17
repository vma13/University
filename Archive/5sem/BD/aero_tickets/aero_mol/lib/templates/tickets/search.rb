count = 0
"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Tickets'>
<input type = 'hidden' name = 'action' value = 'search'>

<table class = 'list'>
  <caption>
    #{@header}<br>
    <span style = 'color: Red;'>#{@message}</span>
  </caption>
  <thead>
  <tbody>
    <tr>
      <th>Номер паспорта:</th>
      <td><input type = 'text' name = 'item[passport_number]' value = ''></td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '1'>
        <input type = 'submit' value = 'Поиск'>
      </th>
    </tr>
  </tfoot>
</table>
"+
"

<table class = 'list'>
  
  <thead>
    <tr>
      <th>
        Номер рейса
      </th>
      <th>
        Вылет
      </th>
      <th>
        Посадка
      </th>
      <th>
        Паспорт
      </th>
      <th>
        ФИО
      </th>
      
    </tr>
  </thead>
  <tbody>
" + @res.map do |i|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td>#{i[:code]}</td>
      <td>#{i[:departure_place]}, #{i[:departure_airport]}: #{i[:departure_date]}</td>
      <td>#{i[:arrival_place]}, #{i[:arrival_airport]}: #{i[:arrival_date]}</td>
      <td>#{i[:passport_number]}</td>
      <td>#{i[:second_name]} ,#{i[:first_name]},  #{i[:patronymc]}</td>
      <td>#{i[:place_type]}</td>
      <td>#{i[:cost]}</td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"
