# -*- coding: utf-8 -*-
#Orders.find(ORDER_ID).user.update_attributes(:billing_id => BILLING_ID)
puts "Create Users"

u = User.new(:login=>"luck-va", :password=>"qwerty", :password_confirmation=>"qwerty", :email=>"luck-va@msiu.ru")
u.role = 0
puts "Luck-va: " + u.save.to_s
u = User.new(:login=>"teacher", :password=>"teacher2", :password_confirmation=>"teacher2", :email=>"teacher@msiu.ru")
u.role = 2
puts "Teacher: " + u.save.to_s
u = User.new(:login=>"admin", :password=>"admin2", :password_confirmation=>"admin2", :email=>"admin@msiu.ru")
u.role = 1
puts "Admin: " + u.save.to_s
u = User.new(:login=>"user", :password=>"user22", :password_confirmation=>"user22", :email=>"user@msiu.ru")
u.role = 0
puts "FDO user: " + u.save.to_s

puts "Create Disciplines"
d1 = Discipline.create(:full_name=>"Математика",      :short_name=>"Мат")
d2 = Discipline.create(:full_name=>"Информатика",     :short_name=>"Инф")
d3 = Discipline.create(:full_name=>"Физика",          :short_name=>"Физ")
d4 = Discipline.create(:full_name=>"Русский язык",    :short_name=>"Рус. Яз")
d5 = Discipline.create(:full_name=>"Програмирование", :short_name=>"Прогм")
Discipline.create(:full_name=>"История",        :short_name=>"Ист")
Discipline.create(:full_name=>"Обществознание", :short_name=>"Общ")
Discipline.create(:full_name=>"Экология",       :short_name=>"Экл")
Discipline.create(:full_name=>"Химия",          :short_name=>"Хим")

puts "Create Course"
Course.create(:start_date=>"01.09.2000", :finish_date=>"01.06.2001", :discipline_id=>d1.id, :year=>"2000")
Course.create(:start_date=>"01.09.2001", :finish_date=>"01.06.2002", :discipline_id=>d1.id, :year=>"2001")
Course.create(:start_date=>"01.09.2002", :finish_date=>"01.06.2003", :discipline_id=>d1.id, :year=>"2002")
Course.create(:start_date=>"01.09.2003", :finish_date=>"01.06.2004", :discipline_id=>d1.id, :year=>"2003")
Course.create(:start_date=>"01.09.2004", :finish_date=>"01.06.2005", :discipline_id=>d1.id, :year=>"2004")
Course.create(:start_date=>"01.09.2005", :finish_date=>"01.06.2006", :discipline_id=>d1.id, :year=>"2005")
Course.create(:start_date=>"01.09.2006", :finish_date=>"01.06.2007", :discipline_id=>d1.id, :year=>"2006")
Course.create(:start_date=>"01.09.2007", :finish_date=>"01.06.2008", :discipline_id=>d1.id, :year=>"2007")
Course.create(:start_date=>"01.09.2008", :finish_date=>"01.06.2009", :discipline_id=>d1.id, :year=>"2008")
Course.create(:start_date=>"01.09.2009", :finish_date=>"01.06.2010", :discipline_id=>d1.id, :year=>"2009")
Course.create(:start_date=>"01.09.2010", :finish_date=>"01.06.2011", :discipline_id=>d1.id, :year=>"2010")
Course.create(:start_date=>"01.09.2011", :finish_date=>"01.06.2012", :discipline_id=>d1.id, :year=>"2011")
Course.create(:start_date=>"01.09.2012", :finish_date=>"01.06.2013", :discipline_id=>d1.id, :year=>"2012")

Course.create(:start_date=>"01.09.2000", :finish_date=>"01.06.2001", :discipline_id=>d2.id, :year=>"2000")
Course.create(:start_date=>"01.09.2001", :finish_date=>"01.06.2002", :discipline_id=>d2.id, :year=>"2001")
Course.create(:start_date=>"01.09.2002", :finish_date=>"01.06.2003", :discipline_id=>d2.id, :year=>"2002")
Course.create(:start_date=>"01.09.2003", :finish_date=>"01.06.2004", :discipline_id=>d2.id, :year=>"2003")
Course.create(:start_date=>"01.09.2004", :finish_date=>"01.06.2005", :discipline_id=>d2.id, :year=>"2004")
Course.create(:start_date=>"01.09.2005", :finish_date=>"01.06.2006", :discipline_id=>d2.id, :year=>"2005")
Course.create(:start_date=>"01.09.2006", :finish_date=>"01.06.2007", :discipline_id=>d2.id, :year=>"2006")
Course.create(:start_date=>"01.09.2007", :finish_date=>"01.06.2008", :discipline_id=>d2.id, :year=>"2007")
Course.create(:start_date=>"01.09.2008", :finish_date=>"01.06.2009", :discipline_id=>d2.id, :year=>"2008")
Course.create(:start_date=>"01.09.2009", :finish_date=>"01.06.2010", :discipline_id=>d2.id, :year=>"2009")
Course.create(:start_date=>"01.09.2010", :finish_date=>"01.06.2011", :discipline_id=>d2.id, :year=>"2010")
Course.create(:start_date=>"01.09.2011", :finish_date=>"01.06.2012", :discipline_id=>d2.id, :year=>"2011")
Course.create(:start_date=>"01.09.2012", :finish_date=>"01.06.2013", :discipline_id=>d2.id, :year=>"2012")

Course.create(:start_date=>"01.09.2000", :finish_date=>"01.06.2001", :discipline_id=>d3.id, :year=>"2000")
Course.create(:start_date=>"01.09.2001", :finish_date=>"01.06.2002", :discipline_id=>d3.id, :year=>"2001")
Course.create(:start_date=>"01.09.2002", :finish_date=>"01.06.2003", :discipline_id=>d3.id, :year=>"2002")
Course.create(:start_date=>"01.09.2003", :finish_date=>"01.06.2004", :discipline_id=>d3.id, :year=>"2003")
Course.create(:start_date=>"01.09.2004", :finish_date=>"01.06.2005", :discipline_id=>d3.id, :year=>"2004")
Course.create(:start_date=>"01.09.2005", :finish_date=>"01.06.2006", :discipline_id=>d3.id, :year=>"2005")
Course.create(:start_date=>"01.09.2006", :finish_date=>"01.06.2007", :discipline_id=>d3.id, :year=>"2006")
Course.create(:start_date=>"01.09.2007", :finish_date=>"01.06.2008", :discipline_id=>d3.id, :year=>"2007")
Course.create(:start_date=>"01.09.2008", :finish_date=>"01.06.2009", :discipline_id=>d3.id, :year=>"2008")
Course.create(:start_date=>"01.09.2009", :finish_date=>"01.06.2010", :discipline_id=>d3.id, :year=>"2009")
Course.create(:start_date=>"01.09.2010", :finish_date=>"01.06.2011", :discipline_id=>d3.id, :year=>"2010")
Course.create(:start_date=>"01.09.2011", :finish_date=>"01.06.2012", :discipline_id=>d3.id, :year=>"2011")
Course.create(:start_date=>"01.09.2012", :finish_date=>"01.06.2013", :discipline_id=>d3.id, :year=>"2012")

Course.create(:start_date=>"01.09.2000", :finish_date=>"01.06.2001", :discipline_id=>d4.id, :year=>"2000")
Course.create(:start_date=>"01.09.2001", :finish_date=>"01.06.2002", :discipline_id=>d4.id, :year=>"2001")
Course.create(:start_date=>"01.09.2002", :finish_date=>"01.06.2003", :discipline_id=>d4.id, :year=>"2002")
Course.create(:start_date=>"01.09.2003", :finish_date=>"01.06.2004", :discipline_id=>d4.id, :year=>"2003")
Course.create(:start_date=>"01.09.2004", :finish_date=>"01.06.2005", :discipline_id=>d4.id, :year=>"2004")
Course.create(:start_date=>"01.09.2005", :finish_date=>"01.06.2006", :discipline_id=>d4.id, :year=>"2005")
Course.create(:start_date=>"01.09.2006", :finish_date=>"01.06.2007", :discipline_id=>d4.id, :year=>"2006")
Course.create(:start_date=>"01.09.2007", :finish_date=>"01.06.2008", :discipline_id=>d4.id, :year=>"2007")
Course.create(:start_date=>"01.09.2008", :finish_date=>"01.06.2009", :discipline_id=>d4.id, :year=>"2008")
Course.create(:start_date=>"01.09.2009", :finish_date=>"01.06.2010", :discipline_id=>d4.id, :year=>"2009")
Course.create(:start_date=>"01.09.2010", :finish_date=>"01.06.2011", :discipline_id=>d4.id, :year=>"2010")
Course.create(:start_date=>"01.09.2011", :finish_date=>"01.06.2012", :discipline_id=>d4.id, :year=>"2011")
Course.create(:start_date=>"01.09.2012", :finish_date=>"01.06.2013", :discipline_id=>d4.id, :year=>"2012")

Course.create(:start_date=>"01.09.2000", :finish_date=>"01.06.2001", :discipline_id=>d5.id, :year=>"2000")
Course.create(:start_date=>"01.09.2001", :finish_date=>"01.06.2002", :discipline_id=>d5.id, :year=>"2001")
Course.create(:start_date=>"01.09.2002", :finish_date=>"01.06.2003", :discipline_id=>d5.id, :year=>"2002")
Course.create(:start_date=>"01.09.2003", :finish_date=>"01.06.2004", :discipline_id=>d5.id, :year=>"2003")
Course.create(:start_date=>"01.09.2004", :finish_date=>"01.06.2005", :discipline_id=>d5.id, :year=>"2004")
Course.create(:start_date=>"01.09.2005", :finish_date=>"01.06.2006", :discipline_id=>d5.id, :year=>"2005")
Course.create(:start_date=>"01.09.2006", :finish_date=>"01.06.2007", :discipline_id=>d5.id, :year=>"2006")
Course.create(:start_date=>"01.09.2007", :finish_date=>"01.06.2008", :discipline_id=>d5.id, :year=>"2007")
Course.create(:start_date=>"01.09.2008", :finish_date=>"01.06.2009", :discipline_id=>d5.id, :year=>"2008")
Course.create(:start_date=>"01.09.2009", :finish_date=>"01.06.2010", :discipline_id=>d5.id, :year=>"2009")
Course.create(:start_date=>"01.09.2010", :finish_date=>"01.06.2011", :discipline_id=>d5.id, :year=>"2010")
Course.create(:start_date=>"01.09.2011", :finish_date=>"01.06.2012", :discipline_id=>d5.id, :year=>"2011")
Course.create(:start_date=>"01.09.2012", :finish_date=>"01.06.2013", :discipline_id=>d5.id, :year=>"2012")


puts "Create Groups"
c = Course.create(:start_date=>"01.09.2012", :finish_date=>"25.10.2012", :discipline_id=>d1.id, :year=>"2012")
c1 = Course.create(:start_date=>"01.09.2011", :finish_date=>"25.10.2011", :discipline_id=>d2.id, :year=>"2011")
c2 = Course.create(:start_date=>"01.09.2010", :finish_date=>"25.10.2010", :discipline_id=>d3.id, :year=>"2010")
c3 = Course.create(:start_date=>"01.09.2009", :finish_date=>"25.10.2009", :discipline_id=>d4.id, :year=>"2009")
c4 = Course.create(:start_date=>"01.09.2008", :finish_date=>"25.10.2008", :discipline_id=>d5.id, :year=>"2008")
c5 = Course.create(:start_date=>"01.09.2007", :finish_date=>"25.10.2007", :discipline_id=>d5.id, :year=>"2007")
Group.create(:number=>"1361", :course_id=>c.id, :discipline_id=>"2", :year=>"2012", :gtype=>"false", :week_day=>"2")
Group.create(:number=>"1362", :course_id=>c.id, :discipline_id=>"2", :year=>"2012", :gtype=>"false", :week_day=>"4")
Group.create(:number=>"2361", :course_id=>c.id, :discipline_id=>"2", :year=>"2012", :gtype=>"false", :week_day=>"0")
Group.create(:number=>"2362", :course_id=>c1.id, :discipline_id=>"2", :year=>"2011", :gtype=>"false", :week_day=>"0")
Group.create(:number=>"3361", :course_id=>c1.id, :discipline_id=>"2", :year=>"2011", :gtype=>"false", :week_day=>"2")
Group.create(:number=>"3362", :course_id=>c1.id, :discipline_id=>"2", :year=>"2011", :gtype=>"false", :week_day=>"4")
Group.create(:number=>"4361", :course_id=>c2.id, :discipline_id=>"2", :year=>"2010", :gtype=>"false", :week_day=>"0")
Group.create(:number=>"4362", :course_id=>c2.id, :discipline_id=>"2", :year=>"2010", :gtype=>"false", :week_day=>"0")
Group.create(:number=>"5361", :course_id=>c2.id, :discipline_id=>"2", :year=>"2010", :gtype=>"false", :week_day=>"2")
Group.create(:number=>"5362", :course_id=>c3.id, :discipline_id=>"2", :year=>"2009", :gtype=>"false", :week_day=>"4")
Group.create(:number=>"6361", :course_id=>c3.id, :discipline_id=>"2", :year=>"2009", :gtype=>"false", :week_day=>"0")
Group.create(:number=>"6362", :course_id=>c3.id, :discipline_id=>"2", :year=>"2009", :gtype=>"false", :week_day=>"0")
Group.create(:number=>"7361", :course_id=>c4.id, :discipline_id=>"2", :year=>"2008", :gtype=>"false", :week_day=>"2")
Group.create(:number=>"7362", :course_id=>c4.id, :discipline_id=>"2", :year=>"2008", :gtype=>"false", :week_day=>"4")
Group.create(:number=>"8361", :course_id=>c4.id, :discipline_id=>"2", :year=>"2008", :gtype=>"false", :week_day=>"0")
Group.create(:number=>"8362", :course_id=>c5.id, :discipline_id=>"2", :year=>"2007", :gtype=>"false", :week_day=>"0")
Group.create(:number=>"9361", :course_id=>c5.id, :discipline_id=>"2", :year=>"2007", :gtype=>"false", :week_day=>"2")
Group.create(:number=>"9362", :course_id=>c5.id, :discipline_id=>"2", :year=>"2007", :gtype=>"false", :week_day=>"4")


puts "Create School"
s1 = School.create(:number=>"100", :second_name=>"Бугаенко", :first_name=>"Игорь", :last_name=>"Викторович", :telephone=>"84990000000", 
                   :official_first_name=>"Игоря", :official_second_name=>"Бугаенко", :official_last_name=>"Викторовича")

s2 = School.create(:number=>"200", :second_name=>"Егармина", :first_name=>"Екатерина", :last_name=>"Сергеевна", :telephone=>"84990000000", 
                   :official_first_name=>"Екатерины", :official_second_name=>"Егарминой", :official_last_name=>"Сергеевны")

s3 = School.create(:number=>"300", :second_name=>"Сидельникова", :first_name=>"Екатерина", :last_name=>"Борисовна", :telephone=>"84990000000", 
                   :official_first_name=>"Екатерины", :official_second_name=>"Сидельниковой", :official_last_name=>"Борисовны")

School.create(:number=>"400", :second_name=>"Дорофеев", :first_name=>"Сергей", :last_name=>"Игоревич", :telephone=>"84990000000", 
              :official_first_name=>"Сергея", :official_second_name=>"Дорофеева", :official_last_name=>"Игоревича")

School.create(:number=>"500", :second_name=>"Теплов", :first_name=>"Виталий", :last_name=>"Валерьевич", :telephone=>"84990000000", 
              :official_first_name=>"Сергея", :official_second_name=>"Теплова", :official_last_name=>"Валерьевича")

School.create(:number=>"600", :second_name=>"Тишин", :first_name=>"Денис", :last_name=>"Алексеевич", :telephone=>"84990000000", 
              :official_first_name=>"Дениса", :official_second_name=>"Тишина", :official_last_name=>"Алексеевича")


School.create(:number=>"700", :second_name=>"Чикин", :first_name=>"Иван", :last_name=>"Николаевич", :telephone=>"84990000000", 
              :official_first_name=>"Ивана", :official_second_name=>"Чикина", :official_last_name=>"Николаевича")

School.create(:number=>"800", :second_name=>"Тишин", :first_name=>"Денис", :last_name=>"Алексеевич", :telephone=>"84990000000", 
              :official_first_name=>"Дениса", :official_second_name=>"Тишина", :official_last_name=>"Алексеевича")

puts "Create SchoolGroups"
SchoolGroup.create(:number=>"10а - ПШ(#{s1.number.to_s})", :year=>"2006", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s1.number.to_s})", :year=>"2006", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s1.number.to_s})", :year=>"2006", :school_id=>s1.id, :stype=>true)
SchoolGroup.create(:number=>"11б - ПШ(#{s1.number.to_s})", :year=>"2006", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s1.number.to_s})", :year=>"2007", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s1.number.to_s})", :year=>"2007", :school_id=>s1.id, :stype=>true)
SchoolGroup.create(:number=>"11а - ПШ(#{s1.number.to_s})", :year=>"2007", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s1.number.to_s})", :year=>"2007", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s1.number.to_s})", :year=>"2008", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s1.number.to_s})", :year=>"2008", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s1.number.to_s})", :year=>"2008", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s1.number.to_s})", :year=>"2008", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s1.number.to_s})", :year=>"2009", :school_id=>s1.id, :stype=>true)
SchoolGroup.create(:number=>"10б - ПШ(#{s1.number.to_s})", :year=>"2009", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s1.number.to_s})", :year=>"2009", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s1.number.to_s})", :year=>"2009", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s1.number.to_s})", :year=>"2010", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s1.number.to_s})", :year=>"2010", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s1.number.to_s})", :year=>"2010", :school_id=>s1.id, :stype=>true)
SchoolGroup.create(:number=>"11б - ПШ(#{s1.number.to_s})", :year=>"2010", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s1.number.to_s})", :year=>"2011", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s1.number.to_s})", :year=>"2011", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s1.number.to_s})", :year=>"2011", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s1.number.to_s})", :year=>"2011", :school_id=>s1.id, :stype=>true)
SchoolGroup.create(:number=>"10а - ПШ(#{s1.number.to_s})", :year=>"2012", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s1.number.to_s})", :year=>"2012", :school_id=>s1.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s1.number.to_s})", :year=>"2012", :school_id=>s1.id, :stype=>false)
g1 = SchoolGroup.create(:number=>"11б - ПШ(#{s1.number.to_s})", :year=>"2012", :school_id=>s1.id, :stype=>false)

SchoolGroup.create(:number=>"10а - ПШ(#{s2.number.to_s})", :year=>"2006", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s2.number.to_s})", :year=>"2006", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s2.number.to_s})", :year=>"2006", :school_id=>s2.id, :stype=>true)
SchoolGroup.create(:number=>"11б - ПШ(#{s2.number.to_s})", :year=>"2006", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s2.number.to_s})", :year=>"2007", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s2.number.to_s})", :year=>"2007", :school_id=>s2.id, :stype=>true)
SchoolGroup.create(:number=>"11а - ПШ(#{s2.number.to_s})", :year=>"2007", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s2.number.to_s})", :year=>"2007", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s2.number.to_s})", :year=>"2008", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s2.number.to_s})", :year=>"2008", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s2.number.to_s})", :year=>"2008", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s2.number.to_s})", :year=>"2008", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s2.number.to_s})", :year=>"2009", :school_id=>s2.id, :stype=>true)
SchoolGroup.create(:number=>"10б - ПШ(#{s2.number.to_s})", :year=>"2009", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s2.number.to_s})", :year=>"2009", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s2.number.to_s})", :year=>"2009", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s2.number.to_s})", :year=>"2010", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s2.number.to_s})", :year=>"2010", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s2.number.to_s})", :year=>"2010", :school_id=>s2.id, :stype=>true)
SchoolGroup.create(:number=>"11б - ПШ(#{s2.number.to_s})", :year=>"2010", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s2.number.to_s})", :year=>"2011", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s2.number.to_s})", :year=>"2011", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s2.number.to_s})", :year=>"2011", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s2.number.to_s})", :year=>"2011", :school_id=>s2.id, :stype=>true)
SchoolGroup.create(:number=>"10а - ПШ(#{s2.number.to_s})", :year=>"2012", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s2.number.to_s})", :year=>"2012", :school_id=>s2.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s2.number.to_s})", :year=>"2012", :school_id=>s2.id, :stype=>false)
g2 = SchoolGroup.create(:number=>"11б - ПШ(#{s2.number.to_s})", :year=>"2012", :school_id=>s2.id, :stype=>false)

SchoolGroup.create(:number=>"10а - ПШ(#{s3.number.to_s})", :year=>"2006", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s3.number.to_s})", :year=>"2006", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s3.number.to_s})", :year=>"2006", :school_id=>s3.id, :stype=>true)
SchoolGroup.create(:number=>"11б - ПШ(#{s3.number.to_s})", :year=>"2006", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s3.number.to_s})", :year=>"2007", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s3.number.to_s})", :year=>"2007", :school_id=>s3.id, :stype=>true)
SchoolGroup.create(:number=>"11а - ПШ(#{s3.number.to_s})", :year=>"2007", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s3.number.to_s})", :year=>"2007", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s3.number.to_s})", :year=>"2008", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s3.number.to_s})", :year=>"2008", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s3.number.to_s})", :year=>"2008", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s3.number.to_s})", :year=>"2008", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s3.number.to_s})", :year=>"2009", :school_id=>s3.id, :stype=>true)
SchoolGroup.create(:number=>"10б - ПШ(#{s3.number.to_s})", :year=>"2009", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s3.number.to_s})", :year=>"2009", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s3.number.to_s})", :year=>"2009", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s3.number.to_s})", :year=>"2010", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s3.number.to_s})", :year=>"2010", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s3.number.to_s})", :year=>"2010", :school_id=>s3.id, :stype=>true)
SchoolGroup.create(:number=>"11б - ПШ(#{s3.number.to_s})", :year=>"2010", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10а - ПШ(#{s3.number.to_s})", :year=>"2011", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s3.number.to_s})", :year=>"2011", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s3.number.to_s})", :year=>"2011", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11б - ПШ(#{s3.number.to_s})", :year=>"2011", :school_id=>s3.id, :stype=>true)
SchoolGroup.create(:number=>"10а - ПШ(#{s3.number.to_s})", :year=>"2012", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"10б - ПШ(#{s3.number.to_s})", :year=>"2012", :school_id=>s3.id, :stype=>false)
SchoolGroup.create(:number=>"11а - ПШ(#{s3.number.to_s})", :year=>"2012", :school_id=>s3.id, :stype=>false)
g3 = SchoolGroup.create(:number=>"11б - ПШ(#{s3.number.to_s})", :year=>"2012", :school_id=>s3.id, :stype=>false)

puts "Create Schoolkids"
s = Schoolkid.new(:first_name=>"Антон", :second_name=>"Константинов", :last_name=>"Юрьевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Максим", :second_name=>"Илларионов", :last_name=>"Александрович", :birthday=>"7.05.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Сергей", :second_name=>"Печкин", :last_name=>"Иванович", :birthday=>"15.08.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Андрей", :second_name=>"Деточкин", :last_name=>"Александрович", :birthday=>"13.12.1990", :male=>"1",
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Антон", :second_name=>"Путин", :last_name=>"Валериевич", :birthday=>"8.04.1989", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Татьяна", :second_name=>"Медведева", :last_name=>"Николаевна", :birthday=>"10.02.1990", :male=>"0",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Максим", :second_name=>"Онегин", :last_name=>"Сергеевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Николай", :second_name=>"Овечкин", :last_name=>"Иванович", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Никита", :second_name=>"Калинин", :last_name=>"Геннадьевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Антон", :second_name=>"Яковлев", :last_name=>"Сергеевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Антон", :second_name=>"Аршанвин", :last_name=>"Сергеевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
p s.save
s = Schoolkid.new(:first_name=>"Антон", :second_name=>"Подставной", :last_name=>"Сергеевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "7", :school_group_id=>g1.id)
                  
p s.save
s = Schoolkid.new(:first_name=>"Антон", :second_name=>"Деревлёв", :last_name=>"Сергеевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "6", :school_group_id=>g1.id)
                  
p s.save
s = Schoolkid.new(:first_name=>"Антон", :second_name=>"Фомин", :last_name=>"Сергеевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "6", :school_group_id=>g1.id)
                  
p s.save
s = Schoolkid.new(:first_name=>"Антон", :second_name=>"Дмитриев", :last_name=>"Сергеевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "6", :school_group_id=>g1.id)
                  
                  
p s.save
s = Schoolkid.new(:first_name=>"Александр", :second_name=>"Филипов", :last_name=>"Николаевич", :birthday=>"10.02.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "6", :school_group_id=>g1.id)
p s.save

s = Schoolkid.new(:first_name=>"Мария", :second_name=>"Гутеева", :last_name=>"Алексеевна", :birthday=>"8.06.1989", :male=>"0",  
                  :telephone=>"84990000000",:group_id => "6",  :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Анна", :second_name=>"Нагорная", :last_name=>"Владимировна", :birthday=>"8.06.1990", :male=>"0",  
                  :telephone=>"84990000000",:group_id => "6", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Павел", :second_name=>"Бурьянов", :last_name=>"Игоревич", :birthday=>"12.05.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "6", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Станислав", :second_name=>"Лаврушкин", :last_name=>"Юрьевич", :birthday=>"8.06.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "6", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Михаил", :second_name=>"Глушанков", :last_name=>"Викторович", :birthday=>"25.07.1990", :male=>"1",  
                  :telephone=>"84990000000",:group_id => "6", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Михаил", :second_name=>"Булатов", :last_name=>"Валерьевич", :birthday=>"6.08.1989", :male=>"1",  
                  :telephone=>"84990000000", :group_id => "6", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Алексей", :second_name=>"Ипатов", :last_name=>"Андреевич", :birthday=>"17.03.1990", :male=>"1",  
                  :telephone=>"84990000000", :group_id => "6", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Петр", :second_name=>"Караваев", :last_name=>"Дмитриевич", :birthday=>"10.01.1990", :male=>"1",  
                  :telephone=>"84990000000", :group_id => "6", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Татьяна", :second_name=>"Кау", :last_name=>"Георгиевна", :birthday=>"18.07.1989", :male=>"0",  
                  :telephone=>"84990000000", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Алина", :second_name=>"Кожина", :last_name=>"Сергеевна", :birthday=>"8.02.1990", :male=>"0",  
                  :telephone=>"84990000000", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Сергей", :second_name=>"Пономарев", :last_name=>"Павлович", :birthday=>"22.11.1990", :male=>"1",  
                  :telephone=>"84990000000", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Юлия", :second_name=>"Рыбакова", :last_name=>"Александровна", :birthday=>"14.1.1990", :male=>"0",  
                  :telephone=>"84990000000", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Алексей", :second_name=>"Скоторенко", :last_name=>"Сергеевич", :birthday=>"9.12.1990", :male=>"1", 
                  :telephone=>"84990000000", :school_group_id=>g2.id)
p s.save
s = Schoolkid.new(:first_name=>"Борис", :second_name=>"Смолянинов", :last_name=>"Николаевич", :birthday=>"16.04.1990", :male=>"1", 
                  :telephone=>"84990000000", :school_group_id=>g2.id)
p s.save

#g = Group.find(1)
#g.groups_save([1, 2, 3, 4, 5, 6, 7, 8])
