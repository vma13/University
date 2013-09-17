require 'db_core/models/model'

class FlightStatus < Model
  STATUSES = {0 => 'отменен', 1 => 'задержан', 2 => 'вылетел', 3 => 'сел'}

  def FlightStatus.create_table(connection)
    begin
      connection.do("
CREATE TABLE flight_statuses(
  id serial PRIMARY KEY,
  flight_id integer REFERENCES flights(id) NOT NULL,
  status_id integer NOT NULL CONSTRAINT status_id_ck CHECK(status_id in(0, 1, 2, 3)),
  event_date timestamp NOT NULL,
  UNIQUE(flight_id, event_date)
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
      :flight_id => nil,
      :status_id => nil,
      :event_date => nil
    }
    attributes.each do |k, v|
      @attributes[k.to_sym] = v unless v.nil? or v == ''
    end
  end

  def self.table_name
    return "flight_statuses"
  end
end

