char* basename(char* path, char* ext) {
char* b;      /* указатель базового имени файла */
char* e;      /* указатель расширения имени файла */

 /* Найти адрес базового имени */
if((b = strrchr(path, '/')) != NULL)
  b++;
else  b = path;

/* Отделить расширение */
if((e = strstr(b, ext)) != NULL)
  *e ='\0';
return(b);     /* Вернуть адрес базового имени */
} /* basename */