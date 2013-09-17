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

  def check_in_desk_select(name, selected, is_nil)
    "<select name = '#{name}'>" +
      CheckInDesk.find_all(@db).map do |c|
        if c[:id].to_i == selected.to_i && selected!=0
          "<option value = '#{c[:id]}' selected>#{c[:name]}</option>"
        else
          "<option value = '#{c[:id]}'>#{c[:name]}</option>"
        end
      end.join("\n") + (is_nil ? (selected==0 ? "<option value = '' selected> </option>" : "<option value = ''> </option>") : "") +
      "</select>" 
  end

  def terminal_select(name, selected, is_nil)
    "<select name = '#{name}'>" +
      Terminal.find_all(@db).map do |c|
        if c[:id].to_i == selected.to_i && selected!=0
          "<option value = '#{c[:id]}' selected>#{c[:name]}</option>"
        else
          "<option value = '#{c[:id]}'>#{c[:name]}</option>"
        end
      end.join("\n") + (is_nil ? (selected==0 ? "<option value = '' selected> </option>" : "<option value = ''> </option>") : "") +
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

  def statuses_select(name)
    options=FlightStatus.new
    options=options.get_event()
    "<select name = '#{name}'><option value='nil' selected> </option>"+
       options.map do |k, v|
         "<option value='#{k}'>#{v}</option>"
       end.join("\n") + 
      "</select>"
  end

  def convert_to_status(id)
    options=FlightStatus.new
    options=options.get_event()
    return options[id]
  end

  def convert_to_cid_name(id)
    ans = CheckInDesk.find_first(@db, id)
    return ans[:name]
  end

  def convert_to_cid_description(id)
    ans = CheckInDesk.find_first(@db, id)
    return ans[:description]
  end

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

  def statuses_select(name, selected = -1)
    "<select name = '#{name}'>" +
      FlightStatus::STATUSES.map do |k, v|
        if k.to_i == selected.to_i
          "<option value = '#{k}' selected>#{v}</option>"
        else
          "<option value = '#{k}'>#{v}</option>"
        end
      end.join("\n") +
    "</select>"
  end

  def check_in_desks_select_for_flight(name, flight, selected = -1)
    "<select name = '#{name}'>" +
      (CheckInDesk.find_all_for_select(@db, flight)).map do |c|
        if c[:id].to_i == selected.to_i
          "<option value = '#{c[:id]}' selected>#{c[:name]}</option>"
        else
          "<option value = '#{c[:id]}'>#{c[:name]}</option>"
        end
      end.join("\n") +
    "</select>"
  end

  def terminals_select_for_flight(name, flight, selected = -1)
    "<select name = '#{name}'>" +
      Terminal.find_all_for_select(@db, flight).map do |c|
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

  def create_link(controller, prompt = "Создать новую запись")
    link(controller, "edit", nil, prompt)
  end
  
  def view_link(controller, id, prompt = "Подробнее")
    link(controller, "show", id, prompt)
  end

  def edit_link(controller, id, prompt = "Редактировать")
    link(controller, "edit", id, prompt)
  end

  def destroy_link(controller, id, prompt = "Удалить")
    link(controller, "destroy", id, prompt)
  end

  def cancel_link(controller, id, prompt = "Отменить")
    link(controller, "cancel", id, prompt)
  end

  def link(controller, action, id, prompt)
    args = [controller, action, id ? "&id=#{id}" : "", prompt]
    "<a href = 'aero.rb?controller=%s&action=%s%s'>%s</a>" % args
  end

  def action_links(controller, id, user)
    links = [view_link(controller, id)]
    links += [edit_link(controller, id), destroy_link(controller, id)] if user
    
    links.join("\n")
  end

  def status(flight)
    s = flight.my_status(@db)
    s ? FlightStatus::STATUSES[s[:status_id]] : "Нет статуса"
  end


end
