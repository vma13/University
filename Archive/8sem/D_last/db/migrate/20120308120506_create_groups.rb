class CreateGroups < ActiveRecord::Migration
  def self.up
    create_table :groups do |t|
      t.string  :number
      t.integer :course_id
      t.integer :discipline_id
      t.integer :year
      t.integer :week_day
      t.boolean :gtype, :default => false

      t.timestamps
    end
  end

  def self.down
    drop_table :groups
  end
end
