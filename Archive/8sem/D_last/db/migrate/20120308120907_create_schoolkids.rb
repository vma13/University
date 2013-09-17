class CreateSchoolkids < ActiveRecord::Migration
  def self.up
    create_table :schoolkids do |t|
      t.string   :first_name
      t.string   :second_name
      t.string   :last_name
      t.date     :birthday
      t.integer  :study_year
      t.boolean  :male
      t.string   :telephone
      t.integer  :school_group_id
      t.integer  :group_id

      t.timestamps
    end
  end

  def self.down
    drop_table :schoolkids
  end
end
