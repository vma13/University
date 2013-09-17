#a= "\033[2J\033[0;0H\n\n\n"

a="\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

#---------Variables----------------
delay_koment=2                  
group=2362                      
turtle_position=0 
bunny_position=0
track_length=69                 
NUM_RAND=10                     
min_delay=1                     
#Turtle
fast_move=3                     
sliding=-6                     
slow_move=1                    
#Bunny 
dream=0                        
big_jump=9                     
force_sliding=-12              
small_jump=1                   
weak_sliding=-2                
#Messages
bunny_win="Bunny win!"
turtle_win="turtle win!"
game_over="Game Over!"
oups="Oups!"
#----------------------------------


#~ sleep(delay_koment)
#~ puts "Сегодня соревнуются Заяц и Черепаха!"
#~ sleep(delay_koment)
#~ puts "Делайте Ваши ставки ;)"
#~ sleep(delay_koment)
#~ puts "Итак начнем..."
#~ sleep(delay_koment)
#~ puts "Черепаха на старт!Заяц на старт!"

for i in 1...4
   puts "#{4-i}"
   sleep(min_delay)
end
 
#puts "ГОНГ!!!\nИ ОНИ ПОШЛИ!"
sleep(min_delay)
srand(group)

while true
  race = Array.new(track_length, "-")
  turtle_num = rand(NUM_RAND)
  bunny_num = rand(NUM_RAND)
     case turtle_num
       when 0 .. 5
         turtle_position += fast_move
       when 6 .. 7
         turtle_position += sliding
       when 8 .. 10
         turtle_position += slow_move
     end
       
    case bunny_num
       when 0..2
         bunny_position += big_jump
       when 3..4
         bunny_position += dream
       when 5..6
         bunny_position += small_jump
       when 7..8
         bunny_position += force_sliding
       when 9..10
         bunny_position += weak_sliding
    end
   
    distance=turtle_position-bunny_position
    case distance 
       when 7..race.size
        #puts "\nЧерепаха отрывается от зайца!"
       when -race.size..-7
        #puts "\nЗаяц лидирует!"
    end
    
    if bunny_position >= race.size
       puts bunny_win
       break
      elsif turtle_position >= race.size
        puts turtle_win
       break 
       elsif turtle_position==race.size && bunny_position==race.size
        puts game_over
       break
    end
     
    if turtle_position == bunny_position && 
       turtle_position !=0 && bunny_position !=0
       race[turtle_position] = "Oh!"
       puts oups
     else
       race[turtle_position] = "T"
       race[bunny_position] = "B"
    end
     
     puts "race: #{race*""} :finish"
     puts a
     sleep(min_delay)
end