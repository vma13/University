require 'db_core/models/model'

class Menu < Model
  def Menu.create_table(connection)
    begin
      connection.do("
CREATE TABLE menues(
  id serial PRIMARY KEY,
  name text UNIQUE NOT NULL,
  price text NOT NULL,
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end

  def Menu.table_name()
    return 'menues'
  end

  def initialize(attributes = {})
    @attributes = {
      :id => nil,
      :price => nil,
      :name => nil,
    }
    attributes.each do |k, v|
      @attributes[k] = v
    end
  end
end
