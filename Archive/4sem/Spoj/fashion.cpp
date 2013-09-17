#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main(){
  int t = 0;
  cin >> t;
  for(int k = 0; k<t ;k++){
    int sum = 0;
    int n = 0;
    int i;
    int j;
    cin >> n;
    int men[n];
    int women[n];
    for(i = 0; i < n; i++){
      cin >> men[i];
    }
    
    for(j = 0; j < n; j++){
      cin >> women[j];
    }

    for(i = 0; i < n; i++){
    sum += (men[i] * women[i]);
    }
    cout << sum << endl;
    }
  return 0;
 }


    
