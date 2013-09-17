class Schoolkid < ActiveRecord::Base
  default_scope order(:second_name)
  paginates_per 40

  belongs_to :school_group
  belongs_to :school
      
  validates :first_name, :presence => true, :length => {:in=>3...30}
  validates :second_name, :presence => true, :length => {:in=>3...30}
  validates :last_name, :presence => true, :length => {:in=>3...30}
  validates :school_group_id, :numericality => {:only_integer => true}, :presence => true
  
  attr_reader :school_group_tokens
  
  def school_group_tokens=(ids)
    self.school_group_id = ids
  end

  def self.search(first_name, second_name, last_name)
    if (!first_name.blank? or !second_name.blank? or !last_name.blank?) 
      where('lower(first_name) LIKE lower(?) AND lower(second_name) LIKE lower(?) AND 
lower(last_name) LIKE lower(?)', "%#{first_name}%", "%#{second_name}%", "%#{last_name}%")
    end
  end
end
