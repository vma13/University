class Task
  attr_accessor :st, :t, :dl, :nded
  def initialize(t, dl)
    @t = t 			
    @st = t        
    @dl = dl    
    @nded = dl    
  end
end

def greatest_priority(data)
  min = 0
    while data[min].st == 0
    return -1 if min == data.size-1
    min += 1
  end  
  for i in 0...data.size
    x = data[i].dl <= data[min].dl
    y = data[i].st != 0
    if x && y
      min = i 
    end
  end
  return min
end

def insert_edf(ins, data, i)
  tmp = i + data[ins].st
  if tmp > data[ins].nded
    puts "EDF is not shedulable"
    exit (0)
    main()
  end  
  if($matrix[i] != 0)
    tmp+=1    
  else			
    $matrix[i] = ins + 1
    data[ins].st -= 1
  end  
  if data[ins].st == 0
    data[ins].nded += data[ins].dl
  end
  i+=1
  for k in 0...data.size
    x = i % data[k].dl
    if x == 0
      data[k].st = data[k].t
    end
  end 
  return [i, data]
end

def insert_rma(ins, data, i)
  tmp = i + data[ins].st
  if tmp > data[ins].nded
    puts "RMA is not shedulable"
    p $matrix
    exit (0)
    main()
  end  
  if($matrix[i] != 0)
    tmp += 1
  else			
    $matrix[i] = ins + 1
    data[ins].st -= 1
  end  
  if data[ins].st == 0
    data[ins].nded += data[ins].dl
  end  
  i += 1
  for k in 0...data.size
    x = i % data[k].dl
    if x == 0
      data[k].st = data[k].t
    end
  end  
  return [i, data]
end

def next_deadl(data)
  cl = 0
  while data[cl].st == 0
    return -1 if cl == data.size-1
    cl += 1
  end
  for i in 1...data.size
    x = data[cl].nded >= data[i].nded 
    y = data[i].st != 0
    if x && y
      cl = i
    end
  end
  return cl
end

def edf(data)
  j = 0
  ins = next_deadl(data)
  while j < $matrix.size
    
    for k in 0...data.size
      jj = j % data[k].dl
      if jj == 0
        data[k].st = data[k].t
      end
    end 
    
    if ins < 0
      j+=1
      for k in 0...data.size
        jj = j % data[k].dl
        if jj == 0
          data[k].st = p[k].t
        end
        ins = greatest_priority(data)
      end 
    else
      ins = insert_edf(ins, data, j)
      tmp = ins
      j = tmp[0]
      p = tmp[1]
      ins = next_deadl(data)
    end
  end
end

def rma(data)
  i = 0
  ins = greatest_priority(data)
  while i < $matrix.size
    for k in 0...data.size
      x = i % data[k].dl
      if x == 0
        data[k].st = data[k].t
      end
    end     
    if ins < 0
      i += 1
      for k in 0...data.size
        x = i % data[k].dl
        if x == 0
          data[k].st = data[k].t
        end
      end 
      ins = greatest_priority(data)
    else
      temp = insert_rma(ins, data, i)
      i = temp[0]
      data = temp[1]
      ins = greatest_priority(data)
    end
  end
end

def main()
  puts "Enter number of tasks"
  n = gets.to_i
  t = 15
  a = []
  puts "Enter tasks themselves:"
  n.times do
    a << gets.split(' ').map{|x| x.to_i}
  end
  
  data=[]
  $matrix=Array.new(t,0)
  for i in 0...n
    data[i] = Task.new(a[i][0],a[i][1])
  end
  puts #{\n}
  puts "******************************************************"
  puts "Enter 1 and you will see EDF result"
  puts "Enter 2 and you will see RMA result"	
  puts "If you enter something other, program will be restated"
  puts "******************************************************"
  puts #{\n}
  puts "Your choice:"
  $result = gets.to_i
  puts #{\n}
  if $result == 1
   edf(data)
  elsif $result == 2
   rma(data)
  elsif $result == 3 
   all(data)
  elsif $result != 1 || $result != 2 || $result != 3
  puts "Programm restarting ..."  
  puts #{\n}
  main()
  end
  puts #{\n}
  puts "Result:"
  p $matrix


end
main()
