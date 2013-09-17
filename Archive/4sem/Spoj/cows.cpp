#include <iostream>


using namespace std;

int main(){
  int size;
  cout << "vvedite size" << endl;
  cin >> size;
  int t=1;
  int k;
  int l=0;
  int a[size];
  int b[size];
  srand (unsigned(time(NULL)));
  for (int i=0;i<size;i++){
    a[i]=rand()%10+1;
  }
  
  
  while(k!=1){
    for (int i=0;i<size;i++){
    cout<<"vvedite element"<<endl;
    cin>>b[i];
  }
  for (int i=0;i<size;i++){
    k=0;
    if (a[i]==b[i]){k++;}
  }
  for (int i=0;i<size;i++){
  for (int j=0;j<size;j++){
    l=0;
  if (b[i]==a[j] && (i!=j)){l++;break;}
  }
  }
  cout<<"byki:"<<k<<endl; 
  cout<<"cows:" <<l<<endl;
  for (int i=0;i<size;i++){if (a[i]!=b[i]){k=0;break;}else{k=1;}}
    
} 
  
  cout<<"YRA!"<<endl; 
    
  return 0;
}
