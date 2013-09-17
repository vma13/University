#include <iostream>


using namespace std;

int main(){
  
  int bulls = 0;
  int cows = 0;
  int arr1[4] = {1,2,3,4};
  int arr2[4];
  srand (unsigned(time(NULL)));
  
   for (int i = 0; i < 4; i++){
     cout << "Введите предполагаемое число:" << endl;
    cin >> arr2[i];
  }
  for (int i = 0; i < 4; i++){
    if (arr1[i] == arr2[i]){
      bulls++;
    }
  }
  for (int i = 0 ; i < 4; i++){
    for (int j = 0; j < 4; j++){
      if (arr2[i] == arr1[j] && (i != j)){
        cows++;
        break;
      }
    }
  }
  for (int i = 0; i < 4; i++){
    if (arr1[i] != arr2[i]){
      break;
    }
  }
  
  if (bulls == 4){
    cout << endl << endl << "Число угадано!" << endl;
  }

  cout << endl << endl << "bulls:" << bulls << endl; 
  cout << endl << endl << "cows:" << cows << endl;
   return 0;
}
