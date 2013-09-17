a=gets.to_i
b=gets.to_i
c=gets.to_i
def fact(n)
  s=1
  for i in 1..n
    s*=i
  end
  return s
end
puts fact(a)

def fib(n)
  return 0 if n==0
  return 1 if n==1
  return (fib(n-1)+fib(n-2)) if n>1
end
puts fib(b)

require 'matrix'
def fib2(n)
  (Matrix[[1,1],[1,0]]**n)[0,1]
end
puts fib2(c)

def fib3(n)
  sq=Math.sqrt(5)
  1/sq*(((1+sq)/2)**n-((1-sq)/2**n))
end
puts fib3(5)

def fact2(n)
  (2..n).inject(1){|p,e| p*e}
end
puts fact2(5)
