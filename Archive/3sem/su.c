#include <stdio.h>
#include <stdlib.h>

char* sum( const unsigned char* p_array, unsigned int p_array_len, char** out) {
    unsigned char* str = malloc(p_array_len*2+1);
    const unsigned char* p_end = p_array + p_array_len;
    size_t pos=0;
    const unsigned char* p;
    for( p = p_array; p != p_end; p++, pos+=2 ) {
       str[pos] = out[*p][0];
       str[pos+1] = out[*p][1];
    }
    return (char*)str;
}

int main() {
  size_t out_len = 128;
  char** out;
  int i;
  out = malloc(out_len*sizeof(char*));
  for(i=0; i<out_len; i++) {
    out[i] = malloc(3*sizeof(char));
    snprintf(out[i], 3,"%02X", i);
  }
  size_t len = 8;
  const unsigned char a[] = "DO NOT WANT";
  printf("%s\n", sum((const unsigned char*)a, len, (char**)out));
  return 0;
}
