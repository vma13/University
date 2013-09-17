# -*- coding: utf-8 -*-
class SchoolGroup < ActiveRecord::Base
  default_scope order(:number)
  paginates_per 30

  has_many :schoolkids, :dependent => :destroy
  has_and_belongs_to_many :courses
  belongs_to :school
  
  validates :number, :presence => true,  
                     :length=>{:in => 3..20}

  validates :year,      :numericality => {:only_integer=>true, :greater_than=>1990}
  validates :school_id, :presence => true

  attr_reader :school_tokens

  def self.find_by_year(year)
    where('year = ?', year)
  end
  
  def school_group_type?
    !stype ? "ПШ": "ФДО"
  end
 
  def school_tokens=(ids)
    self.school_id = ids
  end
end
