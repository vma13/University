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

def get_max_priority(p)
  i, count = -1, 0
  (0...p.size).each do |j|
    if (p[j].priority <= p[i].priority) &&
	   (p[j].status > 0) && (p[j].priority <= 1000)
      i = j
    elsif p[j].status < 0
      count += 1
    end
  end
  i == -1 if count == p.size
  return i
end

def insert(index, p, i)
  tmp = i + p[index].status
  if tmp > p[index].next_deadline
    puts "not shedulable"
    print_result($rezult, $resourses)
    return -1
  end
  if p[index].offset_st == 0 &&
	 $index == -1 && index != -1 &&
	 p[index].res_n != 0
	 
    $index = index
  elsif p[index].res_st == 0 && p[index].res_n != 0
    $index = -1
  end
  if($rezult[i] != 0)
    tmp += 1
  elsif p[index].offset_st == 0 &&
		$index != -1 && $index != index && p[index].res_n != 0
    i -= 1
    p[$index].priority = p[index].priority - 1
  else		
    $rezult[i] = index + 1
    p[index].status-=1
    if p[index].offset_st == 0
      if p[index].res_st > 0
        p[index].res_st -= 1
        if (p[index].res_st == 0) and  (p[index].res_n != 0)
          p[index].priority = p[index].deadline + 1
          $index = -1 
        end
        $resourses[i] = 1
      elsif (p[index].res_st == 0) and  (p[index].res_n != 0)
        p[index].priority = p[index].deadline+1
        $index = -1
      end
    else
      p[index].offset_st -= 1
    end
  end
  p[index].next_deadline += p[index].deadline if p[index].status == 0   
  i += 1
  (0...p.size).each do |k|
    if i % p[k].deadline == 0
      p[k].status = p[k].takts
      p[k].res_st = p[k].res_n
      p[k].offset_st = p[k].offset
    end
  end 
  return [i, p]
end

def insert2(index, p, i)
  tmp = i + p[index].status
  if tmp > p[index].next_deadline
    puts "not shedulable"
    print_result($rezult, $resourses)
    return -1
  end
  if p[index].offset_st == 0
    $index = index
    p[index].priority = 0
  end
  if($rezult[i] != 0)
    tmp+=1
  else		
    $rezult[i] = index + 1
    p[index].status-=1
    if p[index].offset_st == 0
      if p[index].res_st > 0
        p[index].res_st -= 1
        if p[index].res_st == 0
          p[index].priority = p[index].deadline+1
          $index = -1 
        end
        $resourses[i] = 1
      elsif p[index].res_st == 0
        p[index].priority = p[index].deadline+1
        $index = -1
      end
    else
      p[index].offset_st -= 1
    end
  end
  if p[index].status == 0
    p[index].next_deadline += p[index].deadline
  end
  i += 1
  (0...p.size).each do |k|
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
  (0...p.size).each do |k|
    if i % p[k].deadline == 0
      p[k].status = p[k].takts
      p[k].res_st = p[k].res_n
      p[k].offset_st = p[k].offset
    end
  end 
  index = get_max_priority(p)
  while i < $rezult.size
    (0...p.size).each do |k|
      if i % p[k].deadline == 0
        p[k].status = p[k].takts
        p[k].res_st = p[k].res_n
        p[k].offset_st = p[k].offset
      end
    end 
    if index < 0
      i += 1
      (0...p.size).each do |k|
        if i % p[k].deadline == 0
          p[k].status = p[k].takts
          p[k].res_st = p[k].res_n
          p[k].offset_st = p[k].offset
        end
      end 
      index = get_max_priority(p)
    else
      flag == 0 ? temp = insert(index, p, i) : temp = insert2(index, p, i)
      if temp == -1
        return -1
      end
      i = temp[0]
      p = temp[1]
      index = get_max_priority(p)
    end
  end
end


def print_result(a, b)
  for i in 0...a.size
    b[i] == 0 ? (print "#{a[i]}  ") : (print "#{a[i]}) ")
  end
  puts
end

n, m, p = gets.to_i, gets.to_i, []
$rezult, $index, $resourses = Array.new(n, 0), -1, Array.new(n, 0)
(0...m).each do |i|
  takts, deadline, offset, res_n = gets.split.map{|x| x.to_i}
  p[i] = Proces.new(takts, deadline, offset, res_n)
end
if rma(p, 0) != -1
  print "inheritance: "
  print_result($rezult, $resourses)
end
(0...$rezult.size).each { |i| $rezult[i] = $resourses[i] = 0 }
if rma(p, 1) != -1
  print "celling:     "
  print_result($rezult, $resourses)
end