require 'db_core/models/model'

class Plane < Model
  attr_reader :company
  attr_writer :company

  def Flight.create_table(connection)
    begin
      connection.do("
CREATE TABLE planes(
  id serial PRIMARY KEY,
  mark text  NOT NULL,
  status text,
  age integer NOT NULL,
  all_price integer NOT NULL,
  company_id integer REFERENCES companies(id) NOT NULL,
  
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
      :mark => nil,
      :status => nil,
      :age => nil,
      :all_price => nil,
      :company_id => nil,
    }
    attributes.each do |k, v|
      @attributes[k.to_sym] = v unless v.nil? or v == ''
    end
  end

  def company_name()
    @company.nil? ? '&nbsp;' : @company[:name]
  end

  def Plane.find_all(connection)
    query = []
    res = []
    query = ["SELECT * FROM planes
          ORDER BY mark"]
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

  def Plane.find_first(connection, id)
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
end
