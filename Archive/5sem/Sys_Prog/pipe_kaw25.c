#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define BUF_LEN 64

void on_pipe_error(){
	printf("Ooooops!\n");
	return;
}

int child(int filedes){
	signal(SIGPIPE, on_pipe_error);
	char buf[BUF_LEN];
	while(read(filedes, buf, BUF_LEN) != 1){
		printf("Read:  %s\n", buf);
	}
	return 0;
}

int main(int argc, char** argv){
	int filedes[2];
	char buf[BUF_LEN];
	int i;
	int pid;
	signal(SIGPIPE, on_pipe_error);
	for(i=0;i<BUF_LEN-1;i++){
		buf[i]='a';
	}
	buf[BUF_LEN-1]='\0';
	if(pipe(filedes)){
		printf("Pipe creation error: %s!\n", strerror(errno));
		exit(1);
	}
	if(!(pid=fork())){
		child(filedes[0]);
		close(filedes[0]);
		close(filedes[1]);
		exit(0);
	}
	for(i=0;i<10;i++){
		write(filedes[1], buf, BUF_LEN);
		printf("Write: %s\n", buf);
	}
	write(filedes[1], buf, 1);
	close(filedes[0]);
	close(filedes[1]);
	wait(NULL);
	return 0;
}
