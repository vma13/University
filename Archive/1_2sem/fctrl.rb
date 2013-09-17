  n=gets.to_i
  f = 1
  if n <= 1
   puts 1
  else	
    for i in 1..n
      f *= i
    end
  end
puts f