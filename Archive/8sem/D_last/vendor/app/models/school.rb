# -*- coding: utf-8 -*-
class School < ActiveRecord::Base
  default_scope order(:number)
  paginates_per 15

  has_many :schoolkids, :through=> :sgroups
  has_many :school_groups, :dependent => :destroy

  accepts_nested_attributes_for :school_groups, :reject_if=>lambda{|a| (a[:year].blank? and a[:number].blank?)}, :allow_destroy=>true  

  validates :number, :numericality => {:only_integer => true, :greater_than => 0},   
                     :presence   => true,
                     :uniqueness => true

  #validates :stype,       :presence => true
  validates :first_name,  :presence => true, :length => {:in=>2...30}
  validates :second_name, :presence => true, :length => {:in=>2...30}
  validates :last_name,   :presence => true, :length => {:in=>2...30}
  validates :official_first_name,  :presence => true, :length => {:in=>2...30}
  validates :official_second_name, :presence => true, :length => {:in=>2...30}
  validates :official_last_name,   :presence => true, :length => {:in=>2...30}
  validates :telephone, :presence => true, :format => /^8\d{3}?\d{7}$/

  def self.find_by_year(year)
    where('year = ?', year)
  end
  
  def fio?
    second_name + " " + first_name + " " + last_name
  end

  def official_fio?
    official_second_name + " " + official_first_name + " " + official_last_name
  end
      
  def school_type?
    stype = 0 ? "ПШ": "ФДО"
  end
end
