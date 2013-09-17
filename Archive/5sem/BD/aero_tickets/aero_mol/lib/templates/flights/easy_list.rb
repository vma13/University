count = 0
"
<table class = 'list'>
  <caption>
    #{@header}
  </caption>
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
        Авиакомпания
      </th>
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td><a href='aero.rb?controller=Tickets&action=index&flight_id=#{i[:id]}'>#{i[:code]}</a></td>
      <td>#{i[:departure_place]}, #{i[:departure_airport]}: #{i[:departure_date]}</td>
      <td>#{i[:arrival_place]}, #{i[:arrival_airport]}: #{i[:arrival_date]}</td>
      <td>#{i.company_name()}</td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"