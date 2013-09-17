class CreateCourses < ActiveRecord::Migration
  def self.up
    create_table :courses do |t|
      t.date     :start_date
      t.date     :finish_date
      t.integer  :year
      t.integer  :discipline_id

      t.timestamps
    end
  end

  def self.down
    drop_table :courses
  end
end
