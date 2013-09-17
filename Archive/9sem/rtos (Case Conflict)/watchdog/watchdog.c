#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int main(int argc, char **argv) {
  int pid, fd;
  int determinant, num; 

  determinant = -1;
  pid = vfork();
  if( pid == -1 )
    perror("can't create child process");
  if( pid == 0 ) {
    execl("./threads", "./threads", NULL);
  }
  else {
    while( 1 ){
      usleep( 2000000 );
      fd = open("out", O_RDWR);
      read(fd, &num, sizeof(num));
      close( fd );
      if( determinant == num ) { 
        kill(pid, SIGTERM);
        printf("Killed\n");
        pid = vfork();
        if( pid == -1 )
          perror("can't create child process");
        if( pid == 0 ) {
          execl("./threads", "./threads", NULL);
        }
      }
      else {
        determinant = num;
      }
    }
  }	
  return 0;
}
