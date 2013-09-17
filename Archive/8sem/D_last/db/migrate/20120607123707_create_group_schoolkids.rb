class CreateGroupSchoolkids < ActiveRecord::Migration  
  def self.up
    create_table :group_schoolkids do |t|
      t.integer :group_id
      t.integer :schoolkid_id      
    end
  end
  
  def self.down
    drop_table :group_schoolkids
  end
 
end
