fd_set rfds;

FD_ZERO(&rfds);
FD_SET(socket, &rfds);

while(1){
    int channel;
    char msg_string[MSG_STRING_LENGTH];
    if(select(socket + 1, &rfds, NULL, NULL, NULL) < 0){
      continue;
    }

    if((channel = accept(socket, (struct sockaddr *)(&cli_addr), &sin_size)) <= 0){
      perror(NULL);
      continue;
    }
    if(recv(channel, msg, MSG_STRING_LENGTH, 0) <= 0){
      perror(NULL);
      close(channel);
      continue;
    }
    /* здесь можно работать с полученным msg */
    close(channel);
 }

/*
  struct hostent* server
  server = gethostbyname("127.0.0.1");
  sin_port = htons(51000);
  cli_addr.sin_addr = *((struct in.addr *)server -> h.addr);
 */
