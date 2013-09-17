class CreateSchools < ActiveRecord::Migration
  def self.up
    create_table :schools do |t|
      t.string :number
      t.string :director_name
      t.string :director_sername
      t.string :director_pathname
      t.string :telephone

      t.timestamps
    end
  end

  def self.down
    drop_table :schools
  end
end
