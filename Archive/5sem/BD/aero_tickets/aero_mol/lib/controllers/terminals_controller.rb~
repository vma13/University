class TerminalsController < Controller
  def is_authorized_action?()
    !([:list, :show].include?(@action))
  end

  def list
    @items = Terminal.find_all(@db)
    render_template(@action)
  end

  def show
    @item = nil

    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Terminal.find_first(@db, @cgi.params['id'][0])
    end

    @message = 'Данный терминал не найден' unless @item
    render_template(@item ? 'show' : 'not_found')
  end

  def edit
    if @cgi.params.has_key?('is_commit')
      params = filter_for_params
      if params.has_key?('id') and params['id'][0] != ''
        @item = Terminal.find_first(@db, params['id'][0])
        @header = 'Редактирование информации о посадочном терминале'
        @message = 'Информация о посадочном терминале записана'
        if @item.nil?
          @item = Terminal.new
          @header = 'Внесение новой информации о посадочном терминале'
          @message = 'Информация о новом посадочном терминале внесена в БД'
        end
      else
        @item = Terminal.new
        @header = 'Внесение новой информации о посадочном терминале'
        @message = 'Информация о новом посадочном терминале внесена в БД'
      end
      @item[:needs_bus] = false
      params.each do |k, v|
        @item[k] = v[0] if k != 'id' and v != ''
      end
      @item.save(@db)
    else
      if @cgi.params.has_key?('id')
        @item = Terminal.find_first(@db, @cgi.params['id'][0])
        @header = 'Редактирование информации о посадочном терминале'
        if @item.nil?
          @item = Terminal.new
          @header = 'Внесение новой информации о посадочном терминале'
        end
      else
        @item = Terminal.new
        @header = 'Внесение новой информации о посадочном терминале'
      end
    end
    render_template('edit')
  end

  def destroy
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Terminal.find_first(@db, @cgi.params['id'][0])
      unless @item.nil?
        if @item.flights(@db).empty?
          @item.destroy(@db)
          @message = 'Объект удален!'
        else
          @message = 'Удаление невозможно, т.к. существуют рейсы связанные с данным терминалом!'
        end
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end

  def self.actions(user)
    result = []
    result += [[:list, 'Посадочные терминалы']]
    result
  end
end
