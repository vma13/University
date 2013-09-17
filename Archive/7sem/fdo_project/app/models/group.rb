class Group < ActiveRecord::Base
  default_scope order(:number)
  paginates_per 20
  
  belongs_to :course
  has_and_belongs_to_many :schoolkids
 
  validates :number, :presence => true, 
                     :uniqueness => true, 
                     :length => {:in=>3...30}

  validates :course_id, :presence => true
  validates :year, :numericality => {:only_integer=>true, :greater_than=>1969}, :presence => true

  def group_type?
    gtype = 0 ? "ПШ": "ФДО"
  end
end
