# -*- coding: utf-8 -*-
class Group < ActiveRecord::Base
  default_scope order(:number)
  paginates_per 20
 
  after_create :create_statements
   
  has_many :schoolkids
  has_many :statements

  validates :number, :presence => true, 
                     :uniqueness => true, 
                     :length => {:in=>3...30}
  
  validates :course_id, :presence => true
  
  validates :year,      :numericality => {:only_integer=>true, :greater_than=>1990},  
                        :presence => true
  
  validates :week_day,  :presence => true
 
  accepts_nested_attributes_for :schoolkids, :reject_if => lambda { |a| a[:number].blank? }, :allow_destroy => true 
  
  def check_date
    statement = Statement.find(self.statement_id)
    now = Time.now
    date = statement.date
    if now >= date
      Statement.select(:date)
    end    
  end
  
  def self.find_by_year(year)
    where('year = ?', year)
  end
    
  def group_type?
    !gtype ? "ПШ": "ФДО"
  end
  
  def create_statements
    course = Course.find(self.course_id)
    day = self.week_day
    start  = course.start_date

    puts day
    puts start

    while start.wday != day
      start += 1.days
    end
    
    finish = course.finish_date
    while start <= finish
      puts start

      Statement.create(:group_id => self.id, :date => start)
      start += 7.days
    end
  end
  
  def groups_save(ids)
    self.schoolkid_ids = ids
    self.statements.each do |statement|
      statement.schoolkid_ids = ids
    end
  end 
end
