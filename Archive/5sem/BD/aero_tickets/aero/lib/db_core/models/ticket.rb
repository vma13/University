require 'db_core/models/model'

class Ticket < Model
  attr_reader :flight
  attr_writer :flight
  
  def Ticket.create_table(connection)
    begin 
      connection.do("
      CREATE TABLE tickets(
      id serial PRIMARY KEY,
      passport_number text NOT NULL,
      first_name text NOT NULL,
      second_name text NOT NULL,
      patronymc text NOT NULL,
      cost float NOT NULL,
      place_type text NOT NULL,
      flight_id integer REFERENCES flights(id) NOT NULL
      ) WITH OIDS
    ")
       return true
      rescue DBI::ProgrammingError => e
       return false
    end
  end
  
  def initialize(attributes={})
    @flight = nil
    @attributes={
      :id => nil,
      :passport_number => nil,
      :first_name => nil,
      :second_name => nil,
      :patronymc => nil,
      :cost => nil,
      :place_type => nil,
      :flight_id => nil
    }
    attributes.each do |k,v|
      @attributes[k.to_sym]=v unless v.nil? or v==''
    end
  end
  
  def flight_id()
    @flight.nil? ? '&nbsp;' :@flight[:code]
  end
  
  def Ticket.find_all(connection, flight_id=nil)
    query=[]
    res=[]
    if flight_id.nil?
      query = ["SELECT * FROM tickets ORDER BY passport_number"]
    else
      query=["SELECT * FROM tickets WHERE flight_id=? ORDER BY passport_number, flight_id"]
    end
    connection.select_all(*query) do |r|
      f=self.new
      r.column_names.each do |c|
        f[c.to_sym]=r[c]
      end
      f.flight = Flight.find_first(connection,f[:flight_id]) unless f[:flight_id].nil?
      res<<f
    end
    return res
  end
  
  def Ticket.find_first(connection, id)
    id=id.to_i
    query=["SELECT * FROM #{table_name()} WHERE id=?" , id]
    r=connection.select_one(*query)
    return nil if r.nil?
    f=self.new
    r.column_names.each do |c|
      f[c.to_sym]=r[c]
    end
    f.flight=Flight.find_first(connection,f[:flight_id]) unless f[:flight_id].nil?
    return f
  end
  
  def Ticket.find_first_pass(connection, id)
    id = id.to_i
    query = ["SELECT * FROM #{table_name()} WHERE passport_number = ? ORDER BY passport_number, second_name", id]
    r = connection.select_one(*query)
    return nil if r.nil?
    t = self.new
    r.column_names.each do |c|
      t[c.to_sym] = r[c]
    end
    t.flight = Flight.find_first(connection,
      t[:flight_id]) unless t[:flight_id].nil?
    return t
  end

  def Ticket.find_all_flight(connection, passport_number)
    query = []
    res1 = []
    if passport_number.nil?
      query = ["SELECT *  FROM flights"]
    else
query=["SELECT * FROM flights f INNER JOIN tickets a on a.flight_id=f.id WHERE passport_number = ? ORDER BY passport_number, second_name" , passport_number]
    end
    connection.select_all(*query) do |r|
      t = self.new
      r.column_names.each do |c|
        t[c.to_sym] = r[c]
      end
      t.flight = Flight.find_first(connection,
        t[:flight_id]) unless t[:flight_id].nil?
      res1 << t
    end
    return res1
  end
  
end


