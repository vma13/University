#include <stdio.h>
#include <malloc.h>
#include <string.h>


char x[] = "[F+F+F+F[--X-Y]+++++F++++++++F-F-F-F]";
char y[] = "[F+F+F+F[--Y]+++++F++++++++F-F-F-F]";
char atom[] = "X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X";

int cal_size(char *buf) {
  int i, s;
  int x_l = strlen(x);
  int y_l = strlen(y);
  int buf_l = strlen(buf);
  s = 0;
  for(i = 0; i < buf_l; i++) {
    if(buf[i] == 'X')
      s += x_l;
    else if(buf[i] == 'Y')
      s += y_l;
    else s++;
  }
  return s;
}

int main(int argc, char *argv[]) {
  FILE *file;
  char *out, *tmp;
  if(argc > 1) {
    int s = cal_size(atom);
    int d, i, j, t_l;
    d = atoi(argv[1]);
    out = (char *)malloc(s*sizeof(char));
    tmp = (char *)malloc(strlen(atom)*sizeof(char));
    strcpy(tmp, atom);
    for(j = 0; j < d; j++) {
      t_l = strlen(tmp);
      for(i = 0; i < t_l; i++) {
	if(tmp[i] == 'X')
	  strcat(out, x);
	else if(tmp[i] == 'Y')
	  strcat(out, y);
	else if(tmp[i] == 'F')
	  strcat(out, "F");
	else if(tmp[i] == '+')
	  strcat(out, "+");
	else if(tmp[i] == '-')
	  strcat(out, "-");
	else if(tmp[i] == '[')
	  strcat(out, "[");
	else if(tmp[i] == ']')
	  strcat(out, "]");
      }
      free(tmp);
      tmp = (char *)malloc(s*sizeof(char));
      strcpy(tmp, out);
      s = cal_size(out);
      free(out);
      out = (char *)malloc(s*sizeof(char));
    }
    file = fopen("out", "w+");
    fprintf(file, "%s", tmp);
    close(file);
    free(tmp);
    free(out);
  }  
  return 0;
}
