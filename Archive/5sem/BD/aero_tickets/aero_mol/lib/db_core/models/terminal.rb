require 'db_core/models/model'

class Terminal < Model
  def Terminal.create_table(connection)
    begin
      connection.do("
CREATE TABLE terminals(
  id serial PRIMARY KEY,
  name varchar(8) UNIQUE NOT NULL,
  description text,
  needs_bus boolean NOT NULL DEFAULT false
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
      :name => nil,
      :description => nil,
      :needs_bus => nil
    }
    attributes.each do |k, v|
      @attributes[k] = v
    end
  end

  def self.find_all_for_select(connection, flight)
    query = []
    res  = []

    query = ["SELECT * FROM terminals WHERE id NOT IN (SELECT t.id FROM terminals t JOIN flight_terminals ft ON (ft.terminal_id = t.id) WHERE ft.flight_id = ?)", flight[:id]]

    connection.select_all(*query) do |r|
      f = Terminal.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end
    return res
  end

  def flights(connection)
    query = []
    res  = []

    query = ["SELECT f.* FROM flights f JOIN flight_terminals ft ON (ft.flight_id = f.id) WHERE ft.terminal_id = ?", self[:id]]
    connection.select_all(*query) do |r|
        f = Flight.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end
    return res
  end
end

