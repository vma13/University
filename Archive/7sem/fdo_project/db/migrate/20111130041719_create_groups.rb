class CreateGroups < ActiveRecord::Migration
  def self.up
    create_table :groups do |t|
      t.string :number
      t.integer :course_id
      t.integer :year
      t.boolean :gtype

      t.timestamps
    end
  end

  def self.down
    drop_table :groups
  end
end
