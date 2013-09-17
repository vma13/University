#include <stdio.h>
#include <conio.h>
int vibor (int in[], int n);
void main (){
  int m=0; int s; int vvh [100]; char f [80];
  printf("\nvvedite chislo elementov v massive: ", f);
  scanf ("%d", &m); //Узнаем размер массива
  printf("\n vvedite cherez probel celie chisla:", f);
   for (int j=0; j<m; j++) scanf ("%d", &vvh[j]); //Заполнение массива
    printf ("\n");
    s = vibor (vvh, m); //Сортировка методом выбора
    printf("sravneniy", f);
    printf ("%d", s);
    getch();
   }
      int vibor (int in[], int n){  
       int sravnen=0; //Характеристика трудоемкости (число стравнений)
       char f [80];
        printf("\nsortirovka metodom vibora:\n", f);
        int i;
          for (i=0; i<n-1; i++){
            int imin=i; //принимаем за наименьший первый из рассматриваемых элементов
             for (int j= i + 1; j<n; j++){
              if (in[j]<in[imin]) imin = j; sravnen++;
             }
             int a = in[i]; in[i]=in[imin]; in[imin]=a; //Обмен элементов
          }
             for (i=0; i<n; i++) printf ("%d ", in[i]);
             printf ("\n");
            return sravnen; //Возвращаем число сравнений
}