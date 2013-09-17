class CreateSchoolkidStatements < ActiveRecord::Migration
  def self.up
    create_table :schoolkid_statements do |t|
      t.integer :schoolkid_id
      t.integer :statement_id
      t.integer :mark
      t.boolean :pres

      t.timestamps
  end
  
  def self.down
    drop_table :schoolkid_statements
  end
end
  
end
