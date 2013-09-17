data, deadlocks = [], []
n = gets.to_i
n.times do
  data << gets.split.map{|x| x.to_i}
end
max = data[n-1][1]
for i in 0...n
  t = data[i][1]
  while t < max
    deadlocks << t
    t += data[i][1]
  end
end
deadlocks << max
deadlocks = deadlocks.sort.uniq
for i in 0...deadlocks.size
  t = deadlocks[i].to_f
  s = 0
  for j in 0...n
    s += (t/data[j][1]).ceil.to_i*data[j][0].to_i
    print "#{(t/data[j][1]).ceil.to_i}*#{data[j][0].to_i} "
    if j != n-1
      print "+ "
    end
  end
  if s > t
    print " > "
  else
    print " <= "
  end
  print " #{t.to_i}\n"
end
