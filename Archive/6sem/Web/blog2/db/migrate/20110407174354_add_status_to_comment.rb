class AddStatusToComment < ActiveRecord::Migration
  def self.up
    add_column :comments, :status, :boolean
  end

  def self.down
    remove_column :comments, :status
  end
end
