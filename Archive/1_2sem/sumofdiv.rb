def sumofdiv(n)
 if n <= 500000
  d=2
  sum=1
  while d<=Math.sqrt(n)
    if (n mod d == 0)
       sum+=d
    end
    return sum
  end
 #~ else 
  #~ break
 #~ end
end
puts sumofdiv(sum)