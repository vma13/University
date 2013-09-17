class Course < ActiveRecord::Base
  include ActiveSupport::Callbacks
  include ActiveModel::Validations
  extend ActiveModel::Callbacks

  after_validation :change_year
  paginates_per 30
  default_scope order(:start_date)

  belongs_to :discipline
  has_and_belongs_to_many :school_groups
  
  validates :start_date,    :presence => true
  validates :finish_date,   :presence => true
  validates :discipline_id, :presence => true

  def self.find_by_year(year)
    where('year = ?', year)
  end
  
  def groups_save(ids)
    self.school_group_ids = ids
  end
  
  private
  
  def change_year
    self.year = self.start_date.year
  end
end
