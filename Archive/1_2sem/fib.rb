def fib(n)
  if n < 0 or n > 10000
    puts "wrong n"
  else
    a = 0
    b = 1
    for i in 2..n
      t = b
      b = b + a
      a = t
    end
  end
  b
end


def fib2(n)
  f = (1 + Math.sqrt(5))/2
  return ((f**n - (1-f**n))/Math.sqrt(5))
end 

a = gets.to_i
puts fib2(a)
