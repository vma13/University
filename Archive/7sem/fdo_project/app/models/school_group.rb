# -*- coding: utf-8 -*-
class SchoolGroup < ActiveRecord::Base
  default_scope order(:number)
  paginates_per 30

  has_many :schoolkids, :dependent => :destroy
  belongs_to :school
  
  validates :number, :presence => true,  
                     :length=>{:in => 1..20}

  validates :year, :numericality => {:only_integer=>true, :in => 1960..2100}
  validates :school_id, :presence => true
  attr_reader :school_tokens
  
  def school_group_type?
    stype = 0 ? "ПШ": "ФДО"
  end
 
  def school_tokens=(ids)
    self.school_id = ids
  end
end
