#include <iostream>
#include <list>

using namespace std;

class proc {
public: 
  proc ( int max, int curr ): max ( max ), curr ( curr ) {}; //конструктор класса, в нем полям макс и кар присваиваються значения перемекнных макс и кар
  int max;
  int curr;
};

bool banker (list<proc>& procl, int res ){//данному методу передаються аргументы перем рес и лист(подобие л1, которое способно хранить переменные класса прок)
  while ( !procl.empty () ) {//пока что-то хран в списке
    bool found = false; //объяв перем типа булл, и выставляем в ложь
    for ( list<proc>::iterator p = procl.begin (); p != procl.end (); ++p){//проходимся по всем эл-м списка
      if ( p -> max - p -> curr <= res ) {//если максимально знач - текщее меньше переменной рез
        res = res + p -> curr;//переменная рез получает значение реч   текущий
        list<proc>::iterator pp = p;//
        ++pp;//след экх класса, 
        procl.erase ( p );//удаляется первый в списке экз-р класса прок
        p = pp;//перепресваивание -) переходим на след аргумент списка
        found = true; //присваиваем переменной занчение правда
      }
    }
    if ( !found )
      return 0;
  }
  return 1; 
}

int main () { 
  list<proc> procl;
  procl.push_back ( proc ( 12, 4 ) );
  procl.push_back ( proc ( 4, 2 ) );
  procl.push_back ( proc ( 8, 4 ) );
  cout << banker ( procl, 2 );
  cout << "\n";
  cout << "0";
  cout << "\n";
  return 0; 
}
