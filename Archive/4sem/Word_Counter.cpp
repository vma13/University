#include <iostream>
using namespace std;


int main(int argc,char * argv []){
  string str,word;
  if(argc == 2)
    word = argv[1];
  else {
    cout << "Enter the word:";
    cin >> word;
  }
  cout << "Enter your text:\n";
  cin>> str;

  int i = 0;
  while (!cin.eof()){
    if(word == str)
      i++;
    cin >> str;
  }
  cout <<  i  << endl;
  return 0;
}
