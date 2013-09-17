class CreateSchools < ActiveRecord::Migration
  def self.up
    create_table :schools do |t|
      t.integer :number
      t.boolean :stype, :default => false
      t.string  :first_name
      t.string  :second_name
      t.string  :last_name
      t.string  :official_first_name
      t.string  :official_second_name
      t.string  :official_last_name
      t.string  :telephone

      t.timestamps
    end
  end

  def self.down
    drop_table :schools
  end
end
