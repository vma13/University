class CreateStatements < ActiveRecord::Migration
def self.up
    create_table :statements do |t|
      
      t.date     :date  
      t.integer  :group_id


      t.timestamps
    end
  end

  def self.down
    drop_table :statements
  end
end
