require 'db_core/models/model'

class Flight < Model
  attr_reader :company
  attr_writer :company

  def Flight.create_table(connection)
    begin
      connection.do("
CREATE TABLE flights(
  id serial PRIMARY KEY,
  code varchar(16) UNIQUE NOT NULL,
  arrival_date timestamp NOT NULL,
  departure_date timestamp NOT NULL,
  arrival_place text NOT NULL,
  departure_place text NOT NULL,
  arrival_airport text NOT NULL,
  departure_airport text NOT NULL,
  company_id integer REFERENCES companies(id) NOT NULL,
  is_departure boolean NOT NULL DEFAULT true
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end

  def initialize(attributes = {})
    @company = nil
    @attributes = {
      :id => nil,
      :code => nil,
      :arrival_date => nil,
      :departure_date => nil,
      :arrival_place => nil,
      :departure_place => nil,
      :arrival_airport => nil,
      :departure_airport => nil,
      :company_id => nil,
      :is_departure => nil
    }
    attributes.each do |k, v|
      @attributes[k.to_sym] = v unless v.nil? or v == ''
    end
  end

  def company_name()
    @company.nil? ? '&nbsp;' : @company[:name]
  end

  def Flight.find_all(connection, departure = nil)
    query = []
    res = []
    if departure.nil?
      query = ["SELECT * FROM flights
          ORDER BY departure_place, departure_date"]
    else
      query = ["SELECT * FROM flights
          WHERE is_departure = ?
          ORDER BY departure_place, departure_date", departure]
    end
    connection.select_all(*query) do |r|
      f = self.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      f.company = Company.find_first(connection,
        f[:company_id]) unless f[:company_id].nil?
      res << f
    end
    return res
  end

  def Flight.find_first(connection, id)
    id = id.to_i
    query = ["SELECT * FROM #{table_name()} WHERE id = ?", id]
    r = connection.select_one(*query)
    return nil if r.nil?
    f = self.new
    r.column_names.each do |c|
      f[c.to_sym] = r[c]
    end
    f.company = Company.find_first(connection,
      f[:company_id]) unless f[:company_id].nil?
    return f
  end
  
   def terminals(connection)
    query = []
    res  = []

    query = ["SELECT t.*, ft.id AS ft_id FROM terminals t JOIN flight_terminals ft ON (ft.terminal_id = t.id) WHERE ft.flight_id = ?", self[:id]]
    
    connection.select_all(*query) do |r|
      f = Terminal.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end
    return res
  end
  
  def statuses(connection)
    query = []
    res  = []

    query = ["SELECT fs.* FROM flight_statuses fs WHERE fs.flight_id = ? ORDER BY fs.event_date DESC", self[:id]]

    connection.select_all(*query) do |r|
      f = FlightStatus.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end
    return res
  end
  
  def check_in_desks(connection)
    res = []
    query = ["SELECT cd.*, cdf.id AS cdf_id
    FROM check_in_desks cd JOIN check_in_desk_flights cdf
    ON (cdf.check_in_desk_id = cd.id)
    WHERE cdf.flight_id = ?", self[:id]]
    connection.select_all(*query) do |r|
      f = CheckInDesk.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end
    return res
  end
  
  def links(connection)
    query = []
    res  = []

    query = ["SELECT cdf.* FROM check_in_desk_flights cdf WHERE cdf.flight_id = ?", self[:id]]

    connection.select_all(*query) do |r|
      f = CheckInDeskFlight.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end

    query = ["SELECT ft.* FROM flight_terminals ft WHERE ft.flight_id = ?", self[:id]]

    connection.select_all(*query) do |r|
      f = FlightTerminal.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end

    return res
  end

  # Возвращает все забронированные билеты к текущему рейсу
  def tickets(connection)
    Ticket.find_by(connection, 'flight_id', @attributes[:id])
  end

  # Возвращает все талоны, связанные с текущим рейсом
  def coupons(connection)
    Coupon.find_range(connection, tickets(connection).map{ |ticket| ticket[:id] })
  end

  # Ищет талон, у которого ряд и место совпадают с переданным
  def coupon_at(connection, row, seat)
    coupons(connection) and coupons(connection).detect{ |coupon| coupon[:row] == row and coupon[:seat] == seat }
  end

  # Узнаёт, свободно ли данное место
  def free?(connection, row, seat)
    not coupon_at(connection, row, seat)
  end
end
