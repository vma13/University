class Course < ActiveRecord::Base
  paginates_per 30
  default_scope order(:start_date)

  belongs_to :discipline
  
  validates :start_date, :presence => true
  validates :finish_date, :presence => true
  validates :discipline_id, :presence => true

  attr_reader :discipline_token

  def discipline_token=(id)
    self.discipline_id = id
  end
end
