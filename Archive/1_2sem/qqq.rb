n=gets.to_i
while (n>0) do
  n-=1
  t=gets.to_i
  z=0
  kindex=0
  a.each_with_index {|a1,i|
    if (a1>t)
      kindex=i
      break
    end
  }
  for i in (0...kindex) do
    z += t/a[i]
  end
  puts z
end