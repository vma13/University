count = 0
"
<table class = 'list'>
  <caption>
    #{@header}
  </caption>
  <thead>
    <tr>
      <th>
        Паспорт
      </th>
      <th>
        ФИО
      </th>
      <th>
        Класс
      </th>
      <th>
        Цена
      </th>
      <th>
        Номер рейса
      </th>
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td>#{i[:passport_number]}</td>
      <td>#{i[:first_name]}, #{i[:second_name]}, #{i[:patronymc]}</td>
      <td>#{i[:place_type]}</td>
      <td>#{i[:cost]}</td>
      <td>#{i.flight_id()}</td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"
