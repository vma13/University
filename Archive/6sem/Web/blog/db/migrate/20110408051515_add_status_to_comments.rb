class AddStatusToComments < ActiveRecord::Migration
  def self.up
   add_collumn :commands, :status, :boolean, :default=>false
  end

  def self.down
   remove_column :comments, :status
  end
end
