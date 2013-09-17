$deadline, $process = 0, []
tact = gets.to_i
$n = gets.to_i
$n.times do
  $process << gets.split.map{|x| x.to_i}
end

$process = $process.sort_by{|x| x[1]}
timeout, rests = [], []
space = $process[0][1]

for i in 0...$process.size
  timeout << $process[i][1]
  rests << $process[i][0]
end

def check_timeouts(timeout, index, rests)
  for i in index...$n
    if timeout[i] == 0
      if rests[i] > 0 && rests[i] != $process[i][0]
        $deadline = i
      end
      timeout[i] = $process[i][1]
    end
  end
  for i in 0...index
    if timeout[i] == 0
      return false
    end
  end
  return true
end

def next_task(timeout, index, rests)
  for i in index..$n-1
    if rests[i] > 0 && check_timeouts(timeout, i, rests)
      return i
    end
  end
  for i in 0..$n-1
    if rests[i] > 0 && check_timeouts(timeout, i, rests)
      return i
    end
  end
  return index
end

i = 0
tact.times do
  if $deadline != 0
    puts " DEADLINE #{$deadline+1}\n"
    break
  else
    if check_timeouts(timeout,i,rests)
      if rests[i]!=0
        print "#{i+1}"
        timeout.map!{|x| x-=1}
        rests[i] -= 1
      else 
        print "*"
        timeout.map!{|x| x-=1}
      end
    end
  
    for x in 0...$n
      if timeout[x]==0 && rests[x]==0
        rests[x] = $process[x][0]
      end
    end
    i = next_task(timeout,i,rests)
  end
end
puts