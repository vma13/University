class AddCategoryIdToFSbjs < ActiveRecord::Migration
  def self.up
    add_column :f_sbjs,:category_id,:integer
  end

  def self.down
   remove_column :f_sbjs,:category_id
  end
end
