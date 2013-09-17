"<h3 style='align: center'>Рейс #{@flight[:code]}:</h3>
<table id='tickets'>\n" + (1..20).to_a.map do |i|
  "  <tr>\n" + ('a'..'f').to_a.map do |j|
    "    <td>" + (@flight.free?(@db, i, j) ? "<a href='aero.rb?controller=#{@controller}&action=new&flight_id=#{@flight[:id]}&row=#{i}&seat=#{j}'>Место #{i}#{j.upcase}</a>" : "#{@user ? "<a href='aero.rb?controller=Coupons&action=show&id=#{@flight.coupon_at(@db, i, j)[:id]}'>" : ''}Бронь#{@user ? '</a>' : ''}") + "</td>\n"
  end.join + "  </tr>\n"
end.join + "</table>\n"