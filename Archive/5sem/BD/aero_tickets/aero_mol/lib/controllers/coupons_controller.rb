class CouponsController < Controller
  # Все действия в данном контроллере требуют авторизации
  def is_authorized_action?
    return true
  end

  # Отображение талона
  def show
    raise 'need id' unless @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
    @coupon = Coupon.find_first(@db, @cgi.params['id'][0])
    @ticket = @coupon.ticket(@db)
    @flight = @ticket.flight(@db)
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

  # В меню никаких пунктов для ээээээээданного контроллера быть не должно
  def CouponsController.actions(user)
    []
  end
end
