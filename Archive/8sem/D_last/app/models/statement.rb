class Statement < ActiveRecord::Base

has_many   :schoolkid_statements
has_many   :disciplines
belongs_to :group
has_many   :schoolkids
end
