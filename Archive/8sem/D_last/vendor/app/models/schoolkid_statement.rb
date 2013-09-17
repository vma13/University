class SchoolkidStatement < ActiveRecord::Base

  belongs_to :schoolkid
  belongs_to :statement

  validates :mark, :numericality => {:only_integer => true, :greater_than => 1, :less_than => 6}, :if => "pres == nil"
  validates :pres, :presence => true, :if => "mark == nil"
end
