class School < ActiveRecord::Base
  has_many :schoolkids, :through=> :school_groups
  has_many :school_groups, :dependent => :destroy

  accepts_nested_attributes_for :school_groups, :reject_if => lambda { |a| (a[:year].blank? and a[:number].blank?) }, :allow_destroy => true  

  default_scope order(:number)
  paginates_per 30

  validates :number, :length => {:in => 3...30},  
                     :presence   => true,
                     :uniqueness => true

  validates :director_name, :presence   => true, :length => {:in=>3...30}
  validates :director_sername, :presence   => true, :length => {:in=>3...30}
  validates :director_pathname, :presence   => true, :length => {:in=>3...30}
  validates :telephone, :presence => true, :format => /^8\d{3}?\d{7}$/
end
