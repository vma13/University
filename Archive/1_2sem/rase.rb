srand 2362
s= "\033[2J\033[0;0H\n"
t=1
r=1
a=[]
for i in 0..69
  a[i]="."
end

puts "Гонг!!!"
 
while true
  tnum=rand(10)
  if tnum < 5 then
    t+=3
    elsif tnum < 7 then
      t-=6
    else
      t+=1
  end
  rnum=rand(10)
  if rnum < 2 
    r=r
  elsif rnum < 4 
    r+=9
  elsif rnum < 5
    r-=12
  elsif rnum < 8
    r+=1
  else 
    r-=2
  end
if r<0 then 
  r=0 
end
if t<0 then 
  t=0 
end
a[t]="T"
a[r]="B"

if t>69
  p "Turtle win!!!"
  break
end
if r>69
  p "Bunny win!!!"
end
puts s
puts a*""
sleep 1
for i in 0..69
  a[i]="."
end
end
