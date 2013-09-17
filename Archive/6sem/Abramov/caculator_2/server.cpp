#include <sys/socket.h>	
#include <netinet/in.h>	
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;

#define SIZE 1000
#define ADRESS_SIZE 30

double res = 0.0;
string cur_num = "";
bool flag = 0, disp = 0;
char address[ADRESS_SIZE], sign;
int sockfd, newsockfd;

#include "calc.h"

void perform(void) {
  switch( sign ) {
    case '-':
      res -= (double)atof(cur_num.data());
      break;
    case '+':
      res += (double)atof(cur_num.data());
      break;
    case '*':
      res *= (double)atof(cur_num.data());
      break;
    case 'D':
      res /= (double)atof(cur_num.data());
      break;
  }
  cur_num = "";
  disp = 0;
}

void address_process(char* str) {
  get_address(str);
  cout << address << endl;
  if( strncmp(address, "index.html", 10) == 0 ) send_html();
  else if( strlen(address) == 1 ) {
    cout << "found" << endl;
    if( isdigit(address[0]) || address[0] == 'P' ) {
      cout << "digit" <<endl;
      disp = 1;
      cur_num += (address[0] == 'P') ? '.': address[0];
    }
    else  {
      switch( address[0] ) {
        cout << "sign" << endl;
        case '-':
        case '+':
        case 'D':
        case '*':
          if( flag ) perform();
          else {
            flag = 1;
            res = (double)atof(cur_num.data());
            cur_num = "";
            disp = 0;
          }
          sign = address[0];
          break;
        case '=':
          flag = 1;
          perform();
          sign = address[0];
          cout << res << endl;
          break;
        case 'C':
          flag = 0;
          res = 0.0;
          disp = 0;
          cur_num = "";
          break;
      }
    }
    send_html();      
    cout << "res: " << res << ", cur_num: " << cur_num << endl;  
  } else send_file(address);
}

int main(int argc, char **argv) {
  char line[SIZE];			
  int optval = 1, clilen;			
  struct sockaddr_in servaddr, cliaddr; 
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(51000);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  listen(sockfd, 5);
  while( 1 ) {
    clilen = sizeof(cliaddr);
    bzero(line, sizeof(line));
    newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, (socklen_t*) &clilen);
    read(newsockfd, line, SIZE-1);
    address_process(line); 
    close(newsockfd);
  }
  return EXIT_SUCCESS;
}
