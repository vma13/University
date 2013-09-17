class CreateCoursesSchoolGroups < ActiveRecord::Migration
  def self.up
    create_table :courses_school_groups, :id=>false do |t|
      t.integer :course_id
      t.integer :school_group_id
      
      t.timestamps
    end
  end

  def self.down
    drop_table :courses_school_groups
  end
end
