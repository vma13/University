class CompaniesController < Controller
  def is_authorized_action?()
    !([:list, :show].include?(@action))
  end

  def list
    @items = Company.find_all(@db)
    render_template(@action)
  end
  
  def show
    @item = nil

    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Company.find_first(@db, @cgi.params['id'][0])
    end

    @message = 'Компания не найдена' unless @item
    render_template(@item ? 'show' : 'not_found')
  end

  def edit
    if @cgi.params.has_key?('is_commit')
      params = filter_for_params
      if params.has_key?('id') and params['id'][0] != ''
        @item = Company.find_first(@db, params['id'][0])
        @header = 'Редактирование информации об авиакомпании'
        @message = 'Информация об авиакомпании записана'
        if @item.nil?
          @item = Company.new
          @header = 'Внесение новой информации об авиакомпании'
          @message = 'Информация о новой авиакомпании внесена в БД'
        end
      else
        @item = Company.new
        @header = 'Внесение новой информации об авиакомпании'
        @message = 'Информация о новой авиакомпании внесена в БД'
      end
      params.each do |k, v|
        @item[k] = v[0] if k != 'id' and v != ''
      end
      @item.save(@db)
    else
      if @cgi.params.has_key?('id')
        @item = Company.find_first(@db, @cgi.params['id'][0])
        @header = 'Редактирование информации об авиакомпании'
        if @item.nil?
          @item = Company.new
          @header = 'Внесение новой информации об авиакомпании'
        end
      else
        @item = Company.new
        @header = 'Внесение новой информации об авиакомпании'
      end
    end
    render_template('edit')
  end

  def destroy
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Company.find_first(@db, @cgi.params['id'][0])
      unless @item.nil?
        if @item.flights(@db).empty?
          @item.destroy(@db)
          @message = 'Объект удален!'
        else  
          @message = 'Удаление невозможно, т.к. существуют рейсы принадлежащие данной авиакомпании!'
        end
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end

  def self.actions(user)
    result = []
    result += [[:list, 'Авиакомпании']]
    result
  end
end
