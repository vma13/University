def chisla(a,r)
  arr=[]
  while a!=0
    arr << a%10
    a=a/10
  end
  arr=arr.reverse
  for i in 0... arr.size
    if arr[i]==1
      arr[i]=["   "," | ","   "," | ","   "]
    elsif arr[i]==2
      arr[i]=[" "+"-"*r+" "," "*r+" |"," "+"-"*r+" ","| "+" "*r," "+"-"*r+" "]
    elsif arr[i]==3
      arr[i]=[" "+"-"*r+" "," "*r+" |"," "+"-"*r+" "," "*r+" |"," "+"-"*r+" "]
    elsif arr[i]==4
      arr[i]=[" "+" "*r+" ","|"+" "*r+"|"," "+"-"*r+" "," "*r+" |"," "+" "*r+" "]
    elsif arr[i]==5
      arr[i]=[" "+"-"*r+" ","|"+" "+" "*r," "+"-"*r+" "," "*r+" |"," "+"-"*r+" "]
    elsif arr[i]==6
      arr[i]=[" "+"-"*r+" ","|"+" "+" "*r," "+"-"*r+" ","|"+" "*r+"|"," "+"-"*r+" "]
    elsif arr[i]==7
      arr[i]=[" "+"-"*r+" "," "*r+" |"," "+" "*r+" "," "*r+" |"," "+" "*r+" "]
    elsif arr[i]==8
      arr[i]=[" "+"-"*r+" ","|"+" "*r+"|"," "+"-"*r+" ","|"+" "*r+"|"," "+"-"*r+" "]
    elsif arr[i]==9
      arr[i]=[" "+"-"*r+" ","|"+" "*r+"|"," "+"-"*r+" "," "*r+" |"," "+"-"*r+" "]
    elsif arr[i]==0
      arr[i]=[" "+"-"*r+" ","|"+" "*r+"|"," "+" "*r+" ","|"+" "*r+"|"     ," "+"-"*r+" "]
    end
  end
  b=[]
  for i in 0... arr[0].size
    for j in 0... arr.size
      if i%2!=0
        b << arr[j][i]
      else
        print arr[j][i]
      end
    end
    if i%2!=0
      for k in 1..r
        print b
        if k!=r
          puts
        end
      end
    end
    puts
    b=[]
  end
end
chisla(1234,12)
