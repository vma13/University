class TicketsController < Controller
  # Любой пользователь может приобрести билет
  def is_authorized_action?()
    return false
  end

  # Формирует список всех мест на рейсе
  def index()
    raise 'need flight id' unless @cgi.params.has_key?('flight_id') and @cgi.params['flight_id'][0] != ''
    @flight = Flight.find_first(@db, @cgi.params['flight_id'][0])
    raise 'bad flight' if @flight.nil?
    render_template(@action)
  end

  # Позволяет приобрести авиабилет
  def new()
    @row, @seat = @cgi.params['row'][0], @cgi.params['seat'][0]
    raise 'need flight id' unless @cgi.params.has_key?('flight_id') and @cgi.params['flight_id'][0] != ''
    @flight = Flight.find_first(@db, @cgi.params['flight_id'][0])
    raise 'bad flight' if @flight.nil?
    return render_template(@action) unless @cgi.params.has_key?('is_commit')
    params = filter_for_params()
    @ticket = Ticket.new
    @coupon = Coupon.new
    @ticket[:flight_id] = @flight[:id]
    ['passport'].each do |key|
      @ticket[key] = params[key][0]
    end
    ['row', 'seat'].each do |key|
      @coupon[key] = params[key][0]
    end
    # Проверяем, правильные ли переданы ряд и место
    raise 'bad row or seat' unless (1..20).include?(@coupon[:row].to_i) and ('a'..'f').include?(@coupon[:seat])
    # Проверяем, не занято ли заданное место
    raise 'double ticket' unless @flight.free?(@db, @coupon[:row], @coupon[:seat])
    @ticket.save(@db)
    @coupon[:ticket_id] = @ticket[:id]
    @coupon.save(@db)
    @controller = 'Coupons'
    render_template('show')
  end

  # Уничтожаем билет и талон
=begin def destroy()
    raise 'need id' unless @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
    @ticket = Ticket.find_first(@db, @cgi.params['id'][0])
    raise 'bad id' if @ticket.nil?
    @flight = @ticket.flight(@db)
    @ticket.coupon.destroy()
    @ticket.destroy()
    render_template('index')
  end
=end

def destroy()
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Ticket.find_first(@db, @cgi.params['id'][0])
      unless @item.nil?
        @item.destroy(@db)
        @message = 'Объект удален!'
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end
  
  def destroy()
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Coupon.find_first(@db, @cgi.params['id'][0])
      unless @item.nil?
        @item.destroy(@db)
        @message = 'Объект удален!'
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end
#def destroy_coupon(coupon)

#end

# В меню никаких пунктов для данного контроллера быть не должно
  def TicketsController.actions(user)
    []
  end
end
