"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Flights'>
<input type = 'hidden' name = 'action' value = 'edit'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<input type = 'hidden' name = 'item[id]' value = '#{@item[:id]}'>
<table class = 'list'>
  <thead><td colspan=2>
    #{@header}<br>
    <span style = 'color: Red;'>#{@message}</span>
  </td></thead>
  <tbody>
    <tr>
      <th>Номер рейса:</th>
      <td><input type = 'text' name = 'item[code]' value = '#{@item[:code]}'></td>
    </tr>
    <tr>
      <th>
        Вылет<br>
        <div style = 'margin-left: 10px;'>город:</div>
        <div style = 'margin-left: 10px;'>время:</div>
        <div style = 'margin-left: 10px;'>аэропорт:</div>
      </th>
      <td>
        &nbsp;<br>
        <input type = 'text' name = 'item[departure_place]' value = '#{@item[:departure_place]}' size = '30'><br>
        <input type = 'text' name = 'item[departure_date]' value = '#{@item[:departure_date]}' size = '30'><br>
        <input type = 'text' name = 'item[departure_airport]' value = '#{@item[:departure_airport]}' size = '30'>
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
        <input type = 'text' name = 'item[arrival_place]' value = '#{@item[:arrival_place]}' size = '30'><br>
        <input type = 'text' name = 'item[arrival_date]' value = '#{@item[:arrival_date]}' size = '30'><br>
        <input type = 'text' name = 'item[arrival_airport]' value = '#{@item[:arrival_airport]}' size = '30'><br>
      </td>
    </tr>
    <tr>
      <th>Авиакомпания:</th>
      <td>#{companies_select('item[company_id]', "#{@item[:company_id]}")}</td>
    </tr>
    <tr>
      <th>Каким рейс является для нашего аэропорта:</th>
      <td>#{is_departure_select('item[is_departure]', "#{@item[:is_departure]}")}</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=Flights&action=list\"'>
      </th>
    </tr>
  </tfoot>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
      </th>
    </tr>
  </tfoot>
<!--</table>-->
</form>


<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'FlightTerminals'>
<input type = 'hidden' name = 'action' value = 'attach'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<input type = 'hidden' name = 'item[flight_id]' value = '#{@item[:id]}'>

<!--<table class = 'list'>-->
<thead><td colspan=2>
Список терминалов:<br/>
</td></thead>
  <tbody>" +
@item.terminals(@db).map do |t|
  "<tr>
  <th>#{view_link(:Terminals, t[:id], t[:name])}</th>
  <td>#{view_link(:FlightTerminals, t[:ft_id])} |
  #{edit_link(:FlightTerminals, t[:ft_id])} |
  #{destroy_link(:FlightTerminals, t[:ft_id])}</td>
  </tr>"
end.join("<br/>") +
    "<tr>
      <th>Терминал:</th>
      <td>#{terminals_select_for_flight('item[terminal_id]', @item)}</td>
    </tr>
    <tr>
      <th>Информация:</th>
      <td><textarea name = 'item[info]'></textarea></td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Добавить терминал'>
      </th>
    </tr>
  </tfoot>
<!--</table>-->
</form>

</br>
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Flights'>
<input type = 'hidden' name = 'action' value = 'set_status'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<input type = 'hidden' name = 'item[flight_id]' value = '#{@item[:id]}'>

<!--<table class = 'list'>-->
<thead><td colspan=2>
История статусов:
</td></thead>
  <tbody>" +
@item.statuses(@db).map do |s|
  "<tr>
  <th>#{FlightStatus::STATUSES[s[:status_id]]}</th>
  <td>#{s[:event_date]}</td>
  </tr>"
end.join("<br/>") +
    "<tr>
      <th>Статус:</th>
      <td>#{statuses_select('item[status_id]')}</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Установить статус'>
      </th>
    </tr>
  </tfoot>
<!--</table>-->
</form>

</br>
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'CheckInDeskFlights'>
<input type = 'hidden' name = 'action' value = 'attach'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<input type = 'hidden' name = 'item[flight_id]' value = '#{@item[:id]}'>

<!--<table class = 'list'>-->
<thead><td colspan=2>
   Список регистрационных стоек:<br/>
</td></thead>
   <tbody>" +
@item.check_in_desks(@db).map do |cd|
  "<tr>
  <th>#{view_link(:CheckInDesks, cd[:id], cd[:name])}</th>
  <td>#{view_link(:CheckInDeskFlights, cd[:cdf_id])} |
  #{edit_link(:CheckInDeskFlights, cd[:cdf_id])} |
  #{destroy_link(:CheckInDeskFlights, cd[:cdf_id])}</td>
  </tr>"
end.join("<br/>") +
    "<tr>
      <th>Регистрационная стойка:</th>
      <td>#{check_in_desks_select_for_flight('item[check_in_desk_id]', @item)}</td>
    </tr>
    <tr>
      <th>Информация:</th>
      <td><textarea name = 'item[info]'></textarea></td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Добавить регистрационную стойку'>
      </th>
    </tr>
  </tfoot>
</table>
</form>

"
