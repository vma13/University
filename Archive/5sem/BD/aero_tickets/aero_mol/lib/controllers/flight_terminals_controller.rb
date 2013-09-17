class FlightTerminalsController < Controller
  def is_authorized_action?()
    !([:show].include?(@action))
  end

  def show
    @item = nil

    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != '' and
      @item = FlightTerminal.find_first(@db, @cgi.params['id'][0])
    end

    @message = 'Данная свзяи терминала с рейсом не найдено' unless @item
    render_template(@item ? 'show' : 'not_found')
  end

  def attach
    params = filter_for_params()
    @item = FlightTerminal.new
    params.each do |k, v|
     @item[k] = v[0] if k != 'id' and v != ''
    end
    @item.save(@db)
    @message = "Терминал добавлен к рейсу"
    render_template(@action)
  end

  def destroy
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = FlightTerminal.find_first(@db, @cgi.params['id'][0])
      unless @item.nil?
        @flight_id = @item[:flight_id]
        @item.destroy(@db)
        @message = 'Объект удален!'
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end

  def edit()
    if @cgi.params.has_key?('is_commit')
      params = filter_for_params()
      if params.has_key?('id') and params['id'][0] != ''
        @item = FlightTerminal.find_first(@db, params['id'][0])
        @message = 'Информация о связи рейса с терминалом записана'
      end
      if @item
        params.each do |k, v|
            @item[k] = v[0] if k != 'id' and v != ''
        end
        @item.save(@db)
      end
    else
      if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
        @item = FlightTerminal.find_first(@db, @cgi.params['id'][0])
        @header = 'Редактирование информации о связи рейса с терминалом'
      end
    end
    render_template(@item ? 'edit' : 'not_found')
  end
end
