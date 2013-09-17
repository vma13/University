class CreateSchoolGroups < ActiveRecord::Migration
  def self.up
    create_table :school_groups do |t|
      t.string  :number
      t.integer :year
      t.integer :school_id
      t.boolean :stype, :default => false

      t.timestamps
    end
  end

  def self.down
    drop_table :school_groups
  end
end
