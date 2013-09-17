class Discipline < ActiveRecord::Base
  paginates_per 10
  default_scope order(:full_name)

  has_many :courses, :dependent => :destroy
  belongs_to :statement
 
  validates :full_name, :presence => true, 
                        :uniqueness => true, 
                        :length => {:in=>3...30}
  
  validates :short_name, :presence => true,
                         :uniqueness => true, 
                         :length => {:in=>2...30}
end
