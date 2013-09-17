class TicketsController < Controller
  def is_authorized_action?()
    !([:easy_list].include?(@action))
  end

  def list()
    @items = Ticket.find_all(@db)
    render_template(@action)
  end

  def easy_list()
    @items = Ticket.find_all(@db)
    @header = 'Все авиабилеты'
    render_template('easy_list')
  end

def search()
      params = filter_for_params()
      if params.has_key?('passport_number') and params['passport_number'][0] != ''
        @res = Ticket.find_all_flight(@db, params['passport_number'][0])
        @header = 'Поиск информации'
        @message = 'Запрос подан'
        if @res == []
          @message = 'Введите номер паспорта'
        end
      else
        @res = []
        @header = 'Введите номер паспорта'
	end
    render_template('search')
  end

  def edit()
    if @cgi.params.has_key?('is_commit')
      params = filter_for_params()

      if params.has_key?('id') and params['id'][0] != ''
        @item = Ticket.find_first(@db, params['id'][0])
        @header = 'Редактирование информации о рейсе'
        @message = 'Информация о рейсе записана'

        if @item.nil?
          @item = Ticket.new
          @header = 'Внесение новой информации о рейсах'
          @message = 'Информация о новом рейсе внесена в БД'
        end
      else
        @item = Ticket.new
        @header = 'Внесение новой информации о рейсах'
        @message = 'Информация о новом рейсе внесена в БД'
      end

      params.each do |k, v|
	@item[k] = v[0] if k != 'id' and v != '' 
      end
	@it = Ticket.find_first_pass(@db, params['passport_number'][0])
	if !@it.nil?
		@item['second_name']=@it['second_name']
		@item['first_name']=@it['first_name']
		@item['patronymc']=@it['patronymc']
	end
      @item.save(@db)
    else
      if @cgi.params.has_key?('id')
        @item = Ticket.find_first(@db, @cgi.params['id'][0])
        @header = 'Редактирование информации о рейсе'
        if @item.nil?
          @item = Ticket.new
          @header = 'Внесение новой информации о рейсах'
        end
      else
        @item = Ticket.new
        @header = 'Внесение новой информации о рейсах'
      end
    end
    render_template('edit')
  end

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

  def TicketsController.actions(user)
    result = [[:easy_list, 'Билеты']]
    unless user.nil?
      result += [[:list, 'Все билеты'],[:search, 'Поиск']]
    end
    result
  end
end
