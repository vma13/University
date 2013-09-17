class Schoolkid < ActiveRecord::Base
  default_scope order(:second_name)
  paginates_per 10
  
  has_many :schoolkid_statements
  has_many :statements, :through => :schoolkid_statements 
  belongs_to :school_group
  belongs_to :school
  has_many :group_schoolkids
  
  validates :first_name,      :presence => true, :length => {:in=>2...30}
  validates :second_name,     :presence => true, :length => {:in=>2...30}
  validates :last_name,       :presence => true, :length => {:in=>2...30}
  validates :birthday,        :presence => true
  validates :school_group_id, :presence => true
  
  accepts_nested_attributes_for :schoolkid_statements, :reject_if => proc {|attributes| attributes['mark', 'pres'].blank?}
 
  accepts_nested_attributes_for :group_schoolkids, :reject_if => lambda { |a| a[:number].blank? }, :allow_destroy => true

  
  attr_reader :school_group_tokens

  def self.find_by_year(year)
    where('year = ?', year)
  end

  def fio
    second_name + " " + first_name + " " + last_name 
  end
  
  def school_group_tokens=(ids)
    self.school_group_id = ids
  end

  def self.search(fname, sname, lname)
    if (!fname.blank? or !sname.blank? or !lname.blank?) 
      where('lower(first_name) LIKE lower(?) AND lower(second_name) LIKE lower(?) AND lower(last_name) LIKE lower(?)', "%#{fname}%", "%#{sname}%", "%#{lname}%")
    end
  end
end

=begin
  .fields
    %h4 Группы
    = f.fields_for :groups do |builder|
      =render 'group_fields', :f => builder
    .field      
      = link_to_add_fields image_tag("/assets/images/add_class.png", :size => "32x32", :title => "Добавить группу"), f, :groups 
=end
