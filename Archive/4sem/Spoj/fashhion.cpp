#include<iostream>
using namespace std;
int main(){
  int n,t,temp=0,sum,i,j;
  cin>>t;
  while(t>0){
    
    cin>>n;
    sum = 0;
    int m[n];
    int w[n];
    for(i=0;i<n;i++)
      cin>>m[i];
    for(j=0;j<n;j++)
      cin>>w[j];
    
    
    for(i=1;i<n;i++){
      for(j=0;j<(n-i);j++){
        
        if(m[j]>m[j+1]){
          temp=m[j];
          m[j]=m[j+1];
          m[j+1]=temp;
        }
      }
    }

    
for(i=1;i<n;i++){
  for(j=0;j<(n-i);j++){
        
    if(w[j]>w[j+1]){
      temp=w[j];
      w[j]=w[j+1];
      w[j+1]=temp;
     }
   }
 }

for(int h=0;h<n;h++)
  sum += (m[h]*w[h]);
 cout << endl << sum << endl << endl;
t--;
}

return 0;
}
 
