require 'db_core/models/model'

class Company < Model
  def Company.create_table(connection)
    begin
      connection.do("
CREATE TABLE companies(
  id serial PRIMARY KEY,
  name text UNIQUE NOT NULL,
  code varchar(8) UNIQUE NOT NULL,
  description text
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end

  def Company.table_name()
    return 'companies'
  end

  def initialize(attributes = {})
    @attributes = {
      :id => nil,
      :name => nil,
      :code => nil,
      :description => nil
    }
    attributes.each do |k, v|
      @attributes[k] = v
    end
  end

  def flights(connection)
    query = []
    res  = []
    query = ["SELECT * FROM flights WHERE company_id = ?", self[:id]]
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
