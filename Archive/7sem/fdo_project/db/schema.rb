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

ActiveRecord::Schema.define(:version => 20111209120623) do

  create_table "courses", :force => true do |t|
    t.datetime "start_date"
    t.datetime "finish_date"
    t.integer  "discipline_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "disciplines", :force => true do |t|
    t.string   "full_name"
    t.string   "short_name"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "groups", :force => true do |t|
    t.string   "number"
    t.integer  "course_id"
    t.integer  "year"
    t.boolean  "gtype"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "school_groups", :force => true do |t|
    t.string   "number"
    t.integer  "year"
    t.integer  "school_id"
    t.boolean  "stype",      :default => false
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "schoolkids", :force => true do |t|
    t.string   "first_name"
    t.string   "second_name"
    t.string   "last_name"
    t.datetime "birthday"
    t.boolean  "male"
    t.string   "addres"
    t.string   "telephone"
    t.integer  "school_group_id"
    t.integer  "group_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "schoolkids_groups", :id => false, :force => true do |t|
    t.integer  "schoolkid_id"
    t.integer  "group_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "schools", :force => true do |t|
    t.string   "number"
    t.string   "director_name"
    t.string   "director_sername"
    t.string   "director_pathname"
    t.string   "telephone"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "users", :force => true do |t|
    t.string   "login",                     :limit => 40
    t.string   "name",                      :limit => 100, :default => ""
    t.string   "email",                     :limit => 100
    t.string   "crypted_password",          :limit => 40
    t.string   "salt",                      :limit => 40
    t.datetime "created_at"
    t.datetime "updated_at"
    t.string   "remember_token",            :limit => 40
    t.datetime "remember_token_expires_at"
    t.integer  "role"
  end

  add_index "users", ["login"], :name => "index_users_on_login", :unique => true

end
