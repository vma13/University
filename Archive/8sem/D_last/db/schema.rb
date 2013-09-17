# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20120607123707) do

  create_table "courses", :force => true do |t|
    t.date     "start_date"
    t.date     "finish_date"
    t.integer  "year"
    t.integer  "discipline_id"
    t.datetime "created_at",    :null => false
    t.datetime "updated_at",    :null => false
  end

  create_table "courses_school_groups", :id => false, :force => true do |t|
    t.integer  "course_id"
    t.integer  "school_group_id"
    t.datetime "created_at",      :null => false
    t.datetime "updated_at",      :null => false
  end

  create_table "disciplines", :force => true do |t|
    t.string   "full_name"
    t.string   "short_name"
    t.datetime "created_at", :null => false
    t.datetime "updated_at", :null => false
  end

  create_table "disciplines_lesson_dates", :id => false, :force => true do |t|
    t.integer  "discipline_id"
    t.integer  "lesson_date_id"
    t.datetime "created_at",     :null => false
    t.datetime "updated_at",     :null => false
  end

  create_table "group_schoolkids", :force => true do |t|
    t.integer "group_id"
    t.integer "schoolkid_id"
  end

  create_table "groups", :force => true do |t|
    t.string   "number"
    t.integer  "course_id"
    t.integer  "discipline_id"
    t.integer  "year"
    t.integer  "week_day"
    t.boolean  "gtype",         :default => false
    t.datetime "created_at",                       :null => false
    t.datetime "updated_at",                       :null => false
  end

  create_table "school_groups", :force => true do |t|
    t.string   "number"
    t.integer  "year"
    t.integer  "school_id"
    t.boolean  "stype",      :default => false
    t.datetime "created_at",                    :null => false
    t.datetime "updated_at",                    :null => false
  end

  create_table "schoolkid_statements", :force => true do |t|
    t.integer  "schoolkid_id"
    t.integer  "statement_id"
    t.integer  "mark"
    t.boolean  "pres"
    t.datetime "created_at",   :null => false
    t.datetime "updated_at",   :null => false
  end

  create_table "schoolkids", :force => true do |t|
    t.string   "first_name"
    t.string   "second_name"
    t.string   "last_name"
    t.date     "birthday"
    t.integer  "study_year"
    t.boolean  "male"
    t.string   "telephone"
    t.integer  "school_group_id"
    t.integer  "group_id"
    t.datetime "created_at",      :null => false
    t.datetime "updated_at",      :null => false
  end

  create_table "schools", :force => true do |t|
    t.integer  "number"
    t.boolean  "stype",                :default => false
    t.string   "first_name"
    t.string   "second_name"
    t.string   "last_name"
    t.string   "official_first_name"
    t.string   "official_second_name"
    t.string   "official_last_name"
    t.string   "telephone"
    t.datetime "created_at",                              :null => false
    t.datetime "updated_at",                              :null => false
  end

  create_table "statements", :force => true do |t|
    t.date     "date"
    t.integer  "group_id"
    t.datetime "created_at", :null => false
    t.datetime "updated_at", :null => false
  end

  create_table "users", :force => true do |t|
    t.string   "login",                     :limit => 40
    t.string   "email",                     :limit => 100
    t.string   "crypted_password",          :limit => 40
    t.string   "salt",                      :limit => 40
    t.datetime "created_at"
    t.datetime "updated_at"
    t.string   "remember_token",            :limit => 40
    t.datetime "remember_token_expires_at"
    t.integer  "role",                                     :default => 2
  end

  add_index "users", ["login"], :name => "index_users_on_login", :unique => true

end
