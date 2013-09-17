module Helper
  def companies_select(name, selected)
    "<select name = '#{name}'>" +
      Company.find_all(@db).map do |c|
        if c[:id].to_i == selected.to_i
          "<option value = '#{c[:id]}' selected>#{c[:name]}</option>"
        else
          "<option value = '#{c[:id]}'>#{c[:name]}</option>"
        end
      end.join("\n") +
      "</select>"
  end

  def is_departure_select(name, selected = true)
    options = {:true => 'отлетающий', :false => 'прилетающий'}
    "<select name = '#{name}'>" +
      options.map do |k, v|
        "<option value = '#{k}'#{k.to_s == selected.to_s ? ' selected' : ''}>#{v}</option>"
      end.join("\n") + 
      "</select>"
  end
    
  def place_type_select(name, selected)
    options = {:a => 'бизнес класс', :b => 'эконом класс', :c => 'премиум класс'}
    "<select name = '#{name}'>" +
      options.map do |k, v|
        "<option value = '#{v}'#{v.to_s == selected.to_s ? ' selected' : ''}>#{v}</option>"
      end.join("\n") + 
      "</select>"
  end
    
  def flights_select(name, selected)
   "<select name = '#{name}'>" +
      Flight.find_all(@db).map do |c|
        if c[:id].to_i == selected.to_i
          "<option value = '#{c[:id]}' selected>#{c[:code]}</option>"
        else
          "<option value = '#{c[:id]}'>#{c[:code]}</option>"
        end
      end.join("\n") +
      "</select>"
  end
    
end
