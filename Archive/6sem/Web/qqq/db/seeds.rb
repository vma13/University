# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rake db:seed (or created alongside the db with db:setup).
#
# Examples:
#
#   cities = City.create([{ :name => 'Chicago' }, { :name => 'Copenhagen' }])
#   Mayor.create(:name => 'Daley', :city => cities.first)

u = User.new(:login => "admin", :name => "Орленко Николай Иванович", :email => "oni3@mail.msiu.ru")
u.password = u.password_confirmation = "qwerty"
puts u.save
