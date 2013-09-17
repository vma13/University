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
  if( f == NULL ) {
    if( errno == ENOENT ) f = fopen("./404.html", "r"); 
    else if( errno == EINVAL ) f = fopen("./500.html", "r");
  }
  while( 1 ) {
    i = fread(buf, sizeof(short), SIZE, f);
    write(newsockfd, buf, i*sizeof(short));
    if( feof(f) ) break;
  }
  fclose(f);
}

void send_html(void) {
  char data[DATA_SIZE];
  char head[] = "<!DOCTYPE html><html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'/><title>Канкулятор</title><link rel='stylesheet' type='text/css' href='main.css'>";
  char css[54] = "<link rel='stylesheet' type='text/css' href='";
  css[45] = (char)(cur_style+'0'); 
  strcat(css, ".css'/>");
  char head2[] = "</head><body><a id = 'lf' href='http://localhost:51000/style=0'>Style 1</a><br/><a href='http://localhost:51000/style=1'>Style 2</a><h1>Канкулятор +-/*</h1><table><thead><tr><th colspan='3'><div class='no'>";
  char tail[] = "</div></th></tr></thead><tr><td><div class='operation'><a href='http://localhost:51000/+'>+</a></div></td><td><div class='operation'><a href='http://localhost:51000/-'>-</a></div></td><td><div class='twocols'><a href='http://localhost:51000/C'>C/E</a></div></td></tr><tr><td><div class='operation'><a href='http://localhost:51000/D'>/</a></div></td><td><div class='operation'><a href='http://localhost:51000/*'>*</a></div></td><td>&nbsp;</td></tr><tr><td><div class='operation'><a href='http://localhost:51000/1'>1</a></div></td><td><div class='operation'><a href='http://localhost:51000/2'>2</a></div></td><td><div class='operation'><a href='http://localhost:51000/3'>3</a></div></td></tr><tr><td><div class='operation'><a href='http://localhost:51000/4'>4</a></div></td><td><div class='operation'><a href='http://localhost:51000/5'>5</a></div></td><td><div class='operation'><a href='http://localhost:51000/6'>6</a></div></td></tr><tr><td><div class='operation'><a href='http://localhost:51000/7'>7</a></div></td><td><div class='operation'><a href='http://localhost:51000/8'>8</a></div></td><td><div class='operation'><a href='http://localhost:51000/9'>9</a></div></td></tr><tr><td><div class='operation'><a href='http://localhost:51000/0'>0</a></div></td><td><div class='operation'><a href='http://localhost:51000/P'>.</a></div></td><td><div class='twocols'><a href='http://localhost:51000/='>=</a></div></td></tr></table></body></html>";
  _write(head);
  _write(css);
  _write(head2);
  if( disp ) _write(cur_num);
  else {
    snprintf(data, sizeof(data), "%.10g", res);
    _write(data);
  }
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
