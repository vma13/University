class CreateDisciplinesLessonDates < ActiveRecord::Migration
  def self.up
    create_table :disciplines_lesson_dates, :id=>false do |t|
      t.integer :discipline_id
      t.integer :lesson_date_id
      
      t.timestamps
    end
  end

  def self.down
    drop_table :disciplines_lesson_dates
  end
end
