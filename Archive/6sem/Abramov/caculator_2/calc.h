#ifndef _SOURSE_CODE_H_
#define _SOURSE_CODE_H_

void _write(char *line) {
  int i, j;
  i = strlen(line);
  while( i != 0 ) {
    j = write(newsockfd, line, i*sizeof(char));
    i -= j;
    line += j;
  }
}

void send_file(const char *file_name) {
  FILE *f;
  short buf[SIZE];
  int i;
  f = fopen(file_name, "r");
  if( f == NULL ) return;
  while( 1 ) {
    i = fread(buf, sizeof(short), SIZE, f);
    write(newsockfd, buf, i*sizeof(short));
    if( feof(f) ) break;
  }
  fclose(f);
}

string convert(double d) {
  ostringstream os;
  os << d;
  return os.str();
} 

void send_html(void) {
  string str;
  char head[] = "<!DOCTYPE html><html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'/><title>Канкулятор</title><link rel='stylesheet' type='text/css' href='main.css'></head><body><h1>Канкулятор +-/*</h1><table><thead><tr><th colspan='3'><div class='no'>";
  char tail[] = "</div></th></tr></thead><tr><td><div class='operation'><a href='http://localhost:51000/+'>+</a></div></td><td><div class='operation'><a href='http://localhost:51000/-'>-</a></div></td><td><div class='twocols'><a href='http://localhost:51000/C'>C/E</a></div></td></tr><tr><td><div class='operation'><a href='http://localhost:51000/D'>/</a></div></td><td><div class='operation'><a href='http://localhost:51000/*'>*</a></div></td><td>&nbsp;</td></tr><tr><td><div class='operation'><a href='http://localhost:51000/1'>1</a></div></td><td><div class='operation'><a href='http://localhost:51000/2'>2</a></div></td><td><div class='operation'><a href='http://localhost:51000/3'>3</a></div></td></tr><tr><td><div class='operation'><a href='http://localhost:51000/4'>4</a></div></td><td><div class='operation'><a href='http://localhost:51000/5'>5</a></div></td><td><div class='operation'><a href='http://localhost:51000/6'>6</a></div></td></tr><tr><td><div class='operation'><a href='http://localhost:51000/7'>7</a></div></td><td><div class='operation'><a href='http://localhost:51000/8'>8</a></div></td><td><div class='operation'><a href='http://localhost:51000/9'>9</a></div></td></tr><tr><td><div class='operation'><a href='http://localhost:51000/0'>0</a></div></td><td><div class='operation'><a href='http://localhost:51000/P'>.</a></div></td><td><div class='twocols'><a href='http://localhost:51000/='>=</a></div></td></tr></table></body></html>";
  str = (disp == 1) ? cur_num : convert(res); 
  _write(head);
  write(newsockfd, str.data(), strlen(str.data()));
  _write(tail);
}

void get_address(char *line) {
  char *tmp;
  int i = 7;
  tmp = strchr(line, '/');
  if( tmp != NULL ) {
    tmp++;
    bzero(address, sizeof(address));
    if( *tmp == ' ' ) strcpy(address, "index.html");
    else i = 0;
    for(; *tmp != ' '; i++, tmp++ )
      address[i] = *tmp;
  }
}


#endif
