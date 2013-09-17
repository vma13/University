class Proces
  attr_accessor :priority, :st, :tacts, :deadline, :offset, :res_st, :res_n, :offset_st, :next_deadline
 def initialize(tacts, deadline, offset, res_n)
  @tacts = tacts # number of tacts
  @priority =  deadline+1 # priority
  @st = tacts # ready to execute
  @deadline = deadline 
  @next_deadline = deadline
  @res_st = res_n # number of tacts with resource, ready to execute
  @res_n = res_n  # number o tacts with resource
  @offset = offset
  @offset_st = offset
 end
end

def printing(x, y)
  for i in 0...x.size
    y[i] == 0 ? (print "#{x[i]}  ") : (print "#{x[i]}+ ")
  end
  puts #{/n}
end

def greatest_priority(data)
 i, count = -1, 0
 for j in 0...data.size
  if (data[j].priority <= data[i].priority) && (data[j].st > 0) && (data[j].priority <= 1000)
   i = j
  elsif data[j].st < 0
   count += 1
  end
 end
 i == -1 if count == data.size
 return i
end

def insert(enter, data, i)
 tmp = i + data[enter].st
 if tmp > data[enter].next_deadline
  puts "not shedulable"
  printing($res, $resourses)
  return -1
 end
 if (data[enter].offset_st == 0) && ($index == -1) && (enter !=-1) && (data[enter].res_n !=0)
  $index = enter
 elsif(data[enter].res_st == 0) && (data[enter].res_n != 0)
  $index = -1
 end
 if($res[i] != 0)
  tmp+=1
 elsif (data[enter].offset_st == 0) && ($index != -1) && ($index != enter) && (data[enter].res_n != 0)
  i-=1
  data[$index].priority = data[enter].priority-1
 else		
  $res[i] = enter + 1
  data[enter].st-=1
  if data[enter].offset_st == 0
   if data[enter].res_st > 0
    data[enter].res_st -= 1
    if (data[enter].res_st == 0) &&  (data[enter].res_n != 0)
     data[enter].priority = data[enter].deadline+1
     $index = -1 
    end
   $resourses[i] = 1
   elsif (data[enter].res_st == 0) &&  (data[enter].res_n != 0)
    data[enter].priority = data[enter].deadline+1
    $index = -1
   end
  else
   data[enter].offset_st -= 1
  end
 end
 if data[enter].st == 0
  data[enter].next_deadline += data[enter].deadline
 end
 i+=1
 for k in 0...data.size
  if i % data[k].deadline == 0
   data[k].st = data[k].tacts
   data[k].res_st = data[k].res_n
   data[k].offset_st = data[k].offset
  end
 end 
 return [i, data]
end

def insert_alternate(enter, data, i)
 tmp = i + data[enter].st
 if tmp > data[enter].next_deadline
  puts "not shedulable"
  printing($res, $resourses)
  return -1
 end
 if data[enter].offset_st == 0
  $index = enter
  data[enter].priority = 0
 end
 if($res[i] != 0)
  tmp+=1
 else		
  $res[i] = enter + 1
  data[enter].st-=1
  if data[enter].offset_st == 0
   if data[enter].res_st > 0
    data[enter].res_st -= 1
    if data[enter].res_st == 0
     data[enter].priority = data[enter].deadline+1
     $index = -1 
    end
    $resourses[i] = 1
   elsif data[enter].res_st == 0
    data[enter].priority = data[enter].deadline+1
    $index = -1
   end
  else
   data[enter].offset_st -= 1
  end
 end
 if data[enter].st == 0
  data[enter].next_deadline += data[enter].deadline
 end
 i += 1
 for k in 0...data.size
  if i % data[k].deadline == 0
   data[k].st = data[k].tacts
   data[k].res_st = data[k].res_n
   data[k].offset_st = data[k].offset
  end
 end 
 return [i, data]
end

def rma(data, flag)
 i = 0
 for k in 0...data.size
  if i % data[k].deadline == 0
   data[k].st = data[k].tacts
   data[k].res_st = data[k].res_n
   data[k].offset_st = data[k].offset
  end
 end 
 enter = greatest_priority(data)
 while i < $res.size
  for k in 0...data.size
   if i % data[k].deadline == 0
    data[k].st = data[k].tacts
    data[k].res_st = data[k].res_n
    data[k].offset_st =data[k].offset
   end
  end 
  if enter < 0
   i += 1
   for k in 0...data.size
    if i % data[k].deadline == 0
     data[k].st = data[k].tacts
     data[k].res_st = data[k].res_n
     data[k].offset_st = data[k].offset
    end
   end 
  enter = greatest_priority(data)
  else
   flag == 0 ? tmp = insert(enter, data, i) : tmp = insert_alternate(enter, data, i)
   if tmp == -1
    return -1
   end
   i = tmp[0]
   p = tmp[1]
   enter = greatest_priority(data)
  end
 end
end

def main()
 n = gets.to_i
 m = gets.to_i
 arr = []
 data = []
 $res = Array.new(n, 0)
 $index = -1
 $resourses = Array.new(n, 0)
 for i in 0...m
  arr << gets.split.map{|x| x.to_i}
  data[i] = Proces.new(arr[i][0], arr[i][1], arr[i][2], arr[i][3])
 end
 if rma(data, 0) != -1
  print "inheritance: "
  printing($res, $resourses)
 end
 for i in 0...$res.size
  $res[i] = $resourses[i] = 0	
 end
 if rma(data, 1) != -1
  print "celling:     "
  printing($res, $resourses)
 end
end
main()
