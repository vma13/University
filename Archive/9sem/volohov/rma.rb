data, d_locks = [], []
n = gets.to_i
n.times { data << gets.split.map{|x| x.to_i} }
max = data[n-1][1]
(0...n).each do |i|
  t = data[i][1]
  while t < max
    d_locks << t
    t += data[i][1]
  end
end
d_locks << max
d_locks = d_locks.sort.uniq
(0...d_locks.size).each do |i|
  t = d_locks[i].to_f
  s = 0
  (0...n).each do |j|
    s += (t / data[j][1]).ceil.to_i * data[j][0].to_i
    print "#{(t / data[j][1]).ceil.to_i} * #{data[j][0].to_i} "
    print "+ " if j != n - 1          
  end
  print s > t ? " > " : " <= "
  print " #{t.to_i}\n"
end
