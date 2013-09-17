class CreateSchoolkidsGroups < ActiveRecord::Migration
  def self.up
    create_table :schoolkids_groups, :id=>false do |t|
      t.integer :schoolkid_id
      t.integer :group_id
      
      t.timestamps
    end
  end

  def self.down
    drop_table :schoolkids_groups
  end
end
