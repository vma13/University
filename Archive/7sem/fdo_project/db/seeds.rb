# -*- coding: utf-8 -*-
u = User.new(:login=>"admin", :password=>"admin2", :password_confirmation=>"admin2", :email=>"admin@msiu.ru")
u.role = 1
p u.save

puts "Create Discipline"
math = Discipline.create(:full_name=>"Математика", :short_name=>"Мат")
info = Discipline.create(:full_name=>"Информатика", :short_name=>"Инф")
fiz = Discipline.create(:full_name=>"Физика", :short_name=>"Физ")
Discipline.create(:full_name=>"Дисциплина 1", :short_name=>"Д1")
Discipline.create(:full_name=>"Дисциплина 2", :short_name=>"Д2")
Discipline.create(:full_name=>"Дисциплина 3", :short_name=>"Д3")
Discipline.create(:full_name=>"Дисциплина 4", :short_name=>"Д4")
Discipline.create(:full_name=>"Дисциплина 5", :short_name=>"Д5")
Discipline.create(:full_name=>"Дисциплина 6", :short_name=>"Д6")

puts "Create Course"
Course.create(:start_date=>"01.09.2007", :finish_date=>"01.12.2007", :discipline_id=>math.id)
Course.create(:start_date=>"01.11.2007", :finish_date=>"01.04.2008", :discipline_id=>math.id)
Course.create(:start_date=>"10.01.2008", :finish_date=>"01.06.2008", :discipline_id=>math.id)
Course.create(:start_date=>"01.09.2008", :finish_date=>"01.12.2008", :discipline_id=>math.id)
Course.create(:start_date=>"01.11.2008", :finish_date=>"01.04.2009", :discipline_id=>math.id)
Course.create(:start_date=>"10.01.2009", :finish_date=>"01.06.2009", :discipline_id=>math.id)
Course.create(:start_date=>"01.09.2009", :finish_date=>"01.12.2009", :discipline_id=>math.id)
Course.create(:start_date=>"01.11.2009", :finish_date=>"01.04.2010", :discipline_id=>math.id)
Course.create(:start_date=>"10.01.2010", :finish_date=>"01.06.2010", :discipline_id=>math.id)

Course.create(:start_date=>"01.09.2007", :finish_date=>"01.12.2007", :discipline_id=>info.id)
Course.create(:start_date=>"01.11.2007", :finish_date=>"01.04.2008", :discipline_id=>info.id)
Course.create(:start_date=>"10.01.2008", :finish_date=>"01.06.2008", :discipline_id=>info.id)
Course.create(:start_date=>"01.09.2008", :finish_date=>"01.12.2008", :discipline_id=>info.id)
Course.create(:start_date=>"01.11.2008", :finish_date=>"01.04.2009", :discipline_id=>info.id)
Course.create(:start_date=>"10.01.2009", :finish_date=>"01.06.2009", :discipline_id=>info.id)
Course.create(:start_date=>"01.09.2009", :finish_date=>"01.12.2009", :discipline_id=>info.id)
Course.create(:start_date=>"01.11.2009", :finish_date=>"01.04.2010", :discipline_id=>info.id)
Course.create(:start_date=>"10.01.2010", :finish_date=>"01.06.2010", :discipline_id=>info.id)

Course.create(:start_date=>"01.01.2007", :finish_date=>"01.06.2007", :discipline_id=>fiz.id)
Course.create(:start_date=>"01.01.2008", :finish_date=>"01.06.2008", :discipline_id=>fiz.id)
Course.create(:start_date=>"01.01.2009", :finish_date=>"01.06.2009", :discipline_id=>fiz.id)
Course.create(:start_date=>"01.01.2010", :finish_date=>"01.06.2010", :discipline_id=>fiz.id)

puts "Create School"
s1 = School.create(:number=>"100", :director_sername=>"Иванов", :director_name=>"Иван", 
                   :director_pathname=>"Иванович", :telephone=>"84990000000")
s2 = School.create(:number=>"200", :director_sername=>"Иванов", :director_name=>"Петр", 
                   :director_pathname=>"Иванович", :telephone=>"84990000000")
s3 = School.create(:number=>"300", :director_sername=>"Петров", :director_name=>"Иван", 
              :director_pathname=>"Иванович", :telephone=>"84990000000")
School.create(:number=>"400", :director_sername=>"Петров", :director_name=>"Петр", 
              :director_pathname=>"Иванович", :telephone=>"84990000000")
School.create(:number=>"500", :director_sername=>"Сидоров", :director_name=>"Иван", 
              :director_pathname=>"Иванович", :telephone=>"84990000000")
School.create(:number=>"600", :director_sername=>"Сидоров", :director_name=>"Сергей", 
              :director_pathname=>"Иванович", :telephone=>"84990000000")

puts "Create Schoolkid"
Schoolkid.create(:first_name=>"Тест",:second_name=>"Рэилсович",:last_name=>"Гемфайлов",:birthday=>"1950-01-11 00:00:00",:male=>false,:telephone=>"84444444433",:school_group_id=>3)

