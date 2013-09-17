#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void sleep_for_ever() {
  fork();
  sleep_for_ever();
}

int main(void) {
  sleep_for_ever(1);
  return 0;
}