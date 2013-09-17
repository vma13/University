"
<div id='coupon' style='border-tickness: 2'>
  <p>Рейс: #{@flight[:code]}</p>
  <p>Вылет: #{@flight[:departure_date]} #{@flight[:departure_place]} (#{@flight[:departure_airport]})</p>
  <p>Посадка: #{@flight[:arrival_date]} #{@flight[:arrival_place]} (#{@flight[:arrival_airport]})</p>
  <p>Номер паспорта: #{@ticket[:passport]}</p>
  <p>Место: #{@coupon[:row]}#{@coupon[:seat].upcase}</p>
</div>
<p><a href='aero.rb?controller=Tickets&action=destroy&id=#{@ticket[:id]}'>Снять бронь</a></p>
<p><a href='aero.rb?controller=Tickets&action=index&flight_id=#{@flight[:id]}'>Назад, к списку мест</a></p>
"
