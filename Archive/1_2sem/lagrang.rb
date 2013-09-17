def lagr(x,mx,my,n)
 l=0
 for k in 0 .. n
  p=1
  for j in 0 .. n
    if j!=k
      p=p*(x-mx[j])/(mx[k]-mx[j])
    end
  end
  lagr=l+my[k]*p
 end
end
puts lagr(1,5,5,4)    