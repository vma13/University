require 'db_core/models/model'

class Ticket < Model
  def Ticket.create_table(connection)
    begin
      connection.do("
CREATE TABLE tickets(
  id serial PRIMARY KEY,
  flight_id integer REFERENCES flights(id) NOT NULL,
  passport varchar(20) NOT NULL
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end

  def initialize(attributes = {})
    @attributes = {
      :id => nil,
      :flight_id => nil,
      :passport => nil
    }
    attributes.each do |k, v|
      @attributes[k] = v.to_sym unless v.nil? or v == ''
    end
  end

  # Возвращает рейс данного билета
  def flight(connection)
    Flight.find_first(connection, @attributes[:flight_id])
  end

  # Возвращает талон данного билета
  def coupon(connection)
    Coupon.find_by(connection, 'ticket_id', @attributes[:id])
  end

end
