require 'db_core/models/model'

class Coupon < Model
  def Coupon.create_table(connection)
    begin
      connection.do("
CREATE TABLE coupons(
  id serial PRIMARY KEY,
  ticket_id integer REFERENCES tickets(id) NOT NULL,
  row integer NOT NULL,
  seat varchar(1) NOT NULL
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
      :ticket_id => nil,
      :row => nil,
      :seat => nil
    }
    attributes.each do |k, v|
      @attributes[k.to_sym] = v unless v.nil? or v == ''
    end
  end

  # Возвращает билет данного талона
  def ticket(connection)
    Ticket.find_first(connection, @attributes[:ticket_id])
  end

  # Возвращает рейс данного талона
  def flight(connection)
    ticket(connection).flight(connection)
  end

end
