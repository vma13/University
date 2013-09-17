def Fact(x)
  fact=1
  for i in 1..x
    fact*=i
  end
  return fact
end

def CreateArray(n,m)
  a=Array.new
  for i in 0...n
    a[i]=Array.new
    for j in 0...m
      a[i][j]=i+j
    end
  end
  return a
end

def Main(arr,n,m)
  for i in 0...n
    for j in 0...m
      arr[i][j]=Fact(arr[i][j])
    end
  end
end

def OutputArray(arr,n,m)
  for i in 0...n
    for j in 0...m
      print arr[i][j],' '
    end
    puts
  end
end

print('puts n: '); n=gets.to_i
print('puts m: '); m=gets.to_i
a=CreateArray(n,m)
OutputArray(a,n,m)
puts
Main(a,n,m)
OutputArray(a,n,m)
