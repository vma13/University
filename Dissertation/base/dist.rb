norma1 = File.open("data_norm_1", "r")
norma1data = []
3.times{|i| norma1data << norma1.readline.split(" ").map{|j| j.to_f}}

norma2 = File.open("data_norm_2", "r")
norma2data = []
3.times{|i| norma2data << norma2.readline.split(" ").map{|j| j.to_f}}

ibs1 = File.open("data_ibs_1", "r")
ibs1data = []
3.times{|i| ibs1data << ibs1.readline.split(" ").map{|j| j.to_f}}

ibs2 = File.open("data_ibs_2", "r")
ibs2data = []
3.times{|i| ibs2data << ibs2.readline.split(" ").map{|j| j.to_f}}

sum = 0
for i in 0...3 do
  for j in 0...64 do
    sum += (norma1data[i][j] - norma2data[i][j])*(norma1data[i][j] - norma2data[i][j])
  end
end
puts "норма и норма"
p sum**0.5

sum = 0
for i in 0...3 do
  for j in 0...64 do
    sum += (norma1data[i][j] - ibs2data[i][j])*(norma1data[i][j] - ibs2data[i][j])
  end
end
puts "норма и больные"
p sum**0.5

sum = 0
for i in 0...3 do
  for j in 0...64 do
    sum += (ibs1data[i][j] - norma2data[i][j])*(ibs1data[i][j] - norma2data[i][j])
  end
end
puts "больные и норма"
p sum**0.5

sum = 0
for i in 0...3 do
  for j in 0...64 do
    sum += (ibs1data[i][j] - ibs2data[i][j])*(ibs1data[i][j] - ibs2data[i][j])
  end
end
puts "больные и больные"
p sum**0.5
