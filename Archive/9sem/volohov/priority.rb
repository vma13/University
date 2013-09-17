class Proces
  attr_accessor :priority, :status, :takts, :deadline, :offset, :res_st, :res_n, :offset_st, :next_deadline
 def initialize(takts, deadline, offset, res_n)
  @takts = takts # number of tacts
  @priority =  deadline+1 # priority
  @status = takts # ready to execute
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
  if (data[j].priority <= data[i].priority) and (data[j].status > 0) and (data[j].priority <= 1000)
   i = j
  elsif data[j].status < 0
   count += 1
  end
 end
 i == -1 if count == data.size
 return i
end

def insert(ins, data, i)
 tmp = i + data[ins].status
 if tmp > data[ins].next_deadline
  puts "not shedulable"
  printing($res, $resourses)
  return -1
 end
 if (data[ins].offset_st == 0) and ($index == -1) and (ins !=-1) and (data[ins].res_n !=0)
  $index = ins
 elsif(data[ins].res_st == 0) and (data[ins].res_n != 0)
  $index = -1
 end
 if($res[i] != 0)
  tmp+=1
 elsif (data[ins].offset_st == 0) and ($index != -1) and ($index != ins) and (data[ins].res_n != 0)
  i-=1
  data[$index].priority = data[ins].priority-1
 else		
  $res[i] = ins + 1
  data[ins].status-=1
  if data[ins].offset_st == 0
   if data[ins].res_st > 0
    data[ins].res_st -= 1
    if (data[ins].res_st == 0) and  (data[ins].res_n != 0)
     data[ins].priority = data[ins].deadline+1
     $index = -1 
    end
   $resourses[i] = 1
   elsif (data[ins].res_st == 0) and  (data[ins].res_n != 0)
    data[ins].priority = data[ins].deadline+1
    $index = -1
   end
  else
   data[ins].offset_st -= 1
  end
 end
 if data[ins].status == 0
  data[ins].next_deadline += data[ins].deadline
 end
 i+=1
 for k in 0...data.size
  if i % data[k].deadline == 0
   data[k].status = data[k].takts
   data[k].res_st = data[k].res_n
   data[k].offset_st = data[k].offset
  end
 end 
 return [i, data]
end

def insert_alternate(ins, data, i)
 tmp = i + data[ins].status
 if tmp > data[ins].next_deadline
  puts "not shedulable"
  printing($res, $resourses)
  return -1
 end
 if data[ins].offset_st == 0
  $index = ins
  data[ins].priority = 0
 end
 if($res[i] != 0)
  tmp+=1
 else		
  $res[i] = ins + 1
  data[ins].status-=1
  if data[ins].offset_st == 0
   if data[ins].res_st > 0
    data[ins].res_st -= 1
    if data[ins].res_st == 0
     data[ins].priority = data[ins].deadline+1
     $index = -1 
    end
    $resourses[i] = 1
   elsif data[ins].res_st == 0
    data[ins].priority = data[ins].deadline+1
    $index = -1
   end
  else
   data[ins].offset_st -= 1
  end
 end
 if data[ins].status == 0
  data[ins].next_deadline += data[ins].deadline
 end
 i += 1
 for k in 0...data.size
  if i % data[k].deadline == 0
   data[k].status = data[k].takts
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
   data[k].status = data[k].takts
   data[k].res_st = data[k].res_n
   data[k].offset_st = data[k].offset
  end
 end 
 ins = greatest_priority(data)
 while i < $res.size
  for k in 0...data.size
   if i % data[k].deadline == 0
    data[k].status = data[k].takts
    data[k].res_st = data[k].res_n
    data[k].offset_st =data[k].offset
   end
  end 
  if ins < 0
   i += 1
   for k in 0...data.size
    if i % data[k].deadline == 0
     data[k].status = data[k].takts
     data[k].res_st = data[k].res_n
     data[k].offset_st = data[k].offset
    end
   end 
  ins = greatest_priority(data)
  else
   flag == 0 ? tmp = insert(ins, data, i) : tmp = insert_alternate(ins, data, i)
   if tmp == -1
    return -1
   end
   i = tmp[0]
   p = tmp[1]
   ins = greatest_priority(data)
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
