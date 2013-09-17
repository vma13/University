class Proces
  attr_accessor :priority, :status, :takts, :deadline, :offset, :res_st, :res_n, :offset_st, :next_deadline
  
  def initialize(takts, deadline, offset, res_n)
    @takts = takts
    @priority =  deadline+1
    @status = takts     
    @deadline = deadline
    @next_deadline = deadline
    @res_st = res_n
    @res_n = res_n
    @offset = offset
    @offset_st = offset
  end
end

def arrays_print(a, b)
  for i in 0...a.size
    b[i] == 0 ? (print "#{a[i]}  ") : (print "#{a[i]}) ")
  end
  puts
end

def find_max_priority(p)
  i, count = -1, 0
  for j in 0...p.size
    if (p[j].priority <= p[i].priority) and (p[j].status > 0) and (p[j].priority <= 1000)
      i = j
    elsif p[j].status < 0
      count += 1
    end
  end
  i == -1 if count == p.size
  return i
end

def insert(ins, p, i)
  tmp = i + p[ins].status
  if tmp > p[ins].next_deadline
    puts "not shedulable"
    arrays_print($rezult, $resourses)
    return -1
  end
  if (p[ins].offset_st == 0) and ($index == -1) and (ins !=-1) and (p[ins].res_n !=0)
    $index = ins
  elsif(p[ins].res_st == 0) and (p[ins].res_n != 0)
    $index = -1
  end
  if($rezult[i] != 0)
    tmp+=1
  elsif (p[ins].offset_st == 0) and ($index != -1) and ($index != ins) and (p[ins].res_n != 0)
    i-=1
    p[$index].priority = p[ins].priority-1
  else		
    $rezult[i] = ins + 1
    p[ins].status-=1
    if p[ins].offset_st == 0
      if p[ins].res_st > 0
        p[ins].res_st -= 1
        if (p[ins].res_st == 0) and  (p[ins].res_n != 0)
          p[ins].priority = p[ins].deadline+1
          $index = -1 
        end
        $resourses[i] = 1
      elsif (p[ins].res_st == 0) and  (p[ins].res_n != 0)
        p[ins].priority = p[ins].deadline+1
        $index = -1
      end
    else
      p[ins].offset_st -= 1
    end
  end
  if p[ins].status == 0
    p[ins].next_deadline += p[ins].deadline
  end
  i+=1
  for k in 0...p.size
    if i % p[k].deadline == 0
      p[k].status = p[k].takts
      p[k].res_st = p[k].res_n
      p[k].offset_st = p[k].offset
    end
  end 
  return [i, p]
end

def insert2(ins, p, i)
  tmp = i + p[ins].status
  if tmp > p[ins].next_deadline
    puts "not shedulable"
    arrays_print($rezult, $resourses)
    return -1
  end
  if p[ins].offset_st == 0
    $index = ins
    p[ins].priority = 0
  end
  if($rezult[i] != 0)
    tmp+=1
  else		
    $rezult[i] = ins + 1
    p[ins].status-=1
    if p[ins].offset_st == 0
      if p[ins].res_st > 0
        p[ins].res_st -= 1
        if p[ins].res_st == 0
          p[ins].priority = p[ins].deadline+1
          $index = -1 
        end
        $resourses[i] = 1
      elsif p[ins].res_st == 0
        p[ins].priority = p[ins].deadline+1
        $index = -1
      end
    else
      p[ins].offset_st -= 1
    end
  end
  if p[ins].status == 0
    p[ins].next_deadline += p[ins].deadline
  end
  i += 1
  for k in 0...p.size
    if i % p[k].deadline == 0
      p[k].status = p[k].takts
      p[k].res_st = p[k].res_n
      p[k].offset_st = p[k].offset
    end
  end 
  return [i, p]
end

def rma(p, flag)
  i = 0
  for k in 0...p.size
    if i % p[k].deadline == 0
      p[k].status = p[k].takts
      p[k].res_st = p[k].res_n
      p[k].offset_st = p[k].offset
    end
  end 
  ins = find_max_priority(p)
  while i < $rezult.size
    for k in 0...p.size
      if i % p[k].deadline == 0
        p[k].status = p[k].takts
        p[k].res_st = p[k].res_n
        p[k].offset_st = p[k].offset
      end
    end 
    if ins < 0
      i += 1
      for k in 0...p.size
        if i % p[k].deadline == 0
          p[k].status = p[k].takts
          p[k].res_st = p[k].res_n
          p[k].offset_st = p[k].offset
        end
      end 
      ins = find_max_priority(p)
    else
      flag == 0 ? temp = insert(ins, p, i) : temp = insert2(ins, p, i)
      if temp == -1
        return -1
      end
      i = temp[0]
      p = temp[1]
      ins = find_max_priority(p)
    end
  end
end

n, m = gets.to_i, gets.to_i
arr, p = [], []
$rezult = Array.new(n, 0)
$index = -1
$resourses = Array.new(n, 0)
for i in 0...m
  arr << gets.split.map{|x| x.to_i}
  p[i] = Proces.new(arr[i][0], arr[i][1], arr[i][2], arr[i][3])
end
if rma(p, 0) != -1
  print "inheritance: "
  arrays_print($rezult, $resourses)
end
for i in 0...$rezult.size
  $rezult[i] = $resourses[i] = 0	
end
if rma(p, 1) != -1
  print "celling:     "
  arrays_print($rezult, $resourses)
end
