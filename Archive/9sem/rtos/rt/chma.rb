def main()
 arr = []
 deadline = []
 n = gets.to_i
 n.times do
  arr << gets.split.map{|x| x.to_i}
 end
 max = arr[n-1][1]
 for i in 0...n
  task = arr[i][1]
  while task < max
   deadline << task
   task += arr[i][1]
  end
 end
 deadline << max
 deadline = deadline.sort.uniq
 for i in 0...deadline.size
  task = deadline[i].to_f
  s = 0
  for j in 0...n
   s += (task/arr[j][1]).ceil.to_i*arr[j][0].to_i #ceil - окркгление до ближайшего целого 
   print "#{(task/arr[j][1]).ceil.to_i}*#{arr[j][0].to_i} "
   if j != n-1
    print "+ "
   end
  end
  if s > task
   print " > "
  else
   print " <= "
  end
  print " #{task.to_i}\n"
 end
end
main()
