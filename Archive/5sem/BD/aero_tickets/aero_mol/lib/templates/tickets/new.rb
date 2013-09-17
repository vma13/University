"
<form name = 'ticket' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Tickets'>
<input type = 'hidden' name = 'action' value = 'new'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<input type = 'hidden' name = 'flight_id' value = '#{@flight[:id]}'>
<input type = 'hidden' name = 'item[row]' value = '#{@row}'>
<input type = 'hidden' name = 'item[seat]' value = '#{@seat}'>
<table class = 'list'>
  <caption>Приобритение авиабилета на рейс #{@flight[:code]}:</caption>
  <thead>
  <tbody>
    <tr>
      <th>
        Вылет<br>
        <div style = 'margin-left: 10px;'>город:</div>
        <div style = 'margin-left: 10px;'>время:</div>
        <div style = 'margin-left: 10px;'>аэропорт:</div>
      </th>
      <td>
        &nbsp;<br>
        #{@flight[:departure_place]}<br>
        #{@flight[:departure_date]}<br>
        #{@flight[:departure_airport]}
      </td>
    </tr>
    <tr>
      <th>
        Посадка<br>
        <div style = 'margin-left: 10px;'>город:</div>
        <div style = 'margin-left: 10px;'>время:</div>
        <div style = 'margin-left: 10px;'>аэропорт:</div>
      </th>
      <td>
        &nbsp;<br>
        #{@flight[:arrival_place]}<br>
        #{@flight[:arrival_date]}<br>
        #{@flight[:arrival_airport]}
      </td>
    </tr>
    <tr>
      <th>Авиакомпания:</th>
      <td>#{@flight.company_name()}</td>
    </tr>
    <tr>
      <th>Рейс является:</th>
      <td>#{@flight[:is_departure] ? 'отлетающим' : 'прибывающим'}</td>
    </tr>
    <tr>
      <th>Ряд:</th>
      <td>#{@row}</td>
    </tr>
    <tr>
      <th>Место:</th>
      <td>#{@seat.upcase}</td>
    </tr>
    <tr>
      <th>Номер паспорта:</th>
      <td><input type = 'text' name = 'item[passport]' size = '30'></td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Приобрести авиабилет'>
        <input type = 'button' value = 'Назад, к списку мест'
               onclick = 'javascript:document.location=\"aero.rb?controller=Tickets&action=index&flight_id=#{@flight[:id]}\"'>
      </th>
    </tr>
  </tfoot>
</table>
"