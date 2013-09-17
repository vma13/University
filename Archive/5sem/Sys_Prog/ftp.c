#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <locale.h>
#include <signal.h>
#include <fcntl.h>

#define DEFAULT_PORT_NUM 8821
#define MAIN_FTP_CMD_BUF 512
#define MAIN_SERVER_PREFIX "SRV"
#define CHILD_SERVER_PREFIX "CLI"
#define ERROR_TYPE "ERR"
#define NOTICE_TYPE "NOT"
#define ROOT_PATH "./"
#define FILE_BLOCK 1024
#define HELLO_MSG "Welcome to MegaFTP Server"
#define CMD_NUM 44
#define CMD_LENGTH 5
#define PASSIVE_PORT_START 2220
#define PASSIVE_PORT_END 2720

int main_server_socket = -1;
extern char **environ;

void child_quit_handler(int s) {
    wait(NULL);
}

void my_exit(int i)
{
    printf("[%s]:[%s] -> Завершение программы...\n", NOTICE_TYPE, MAIN_SERVER_PREFIX);
    if(main_server_socket != -1)
    {
        close(main_server_socket);
    }
    exit(0);
}

void print_errors (int x, char * type1, char * type2, int quit_after_error)
{
    char * error_text;
    error_text = (char*)malloc(256);
    switch(x)
    {
        case 0:
            sprintf(error_text, "Ошибка вызова socket()");
            break;
        case 1:
            sprintf(error_text, "Ошибка вызова bind()");
            break;
        case 2:
            sprintf(error_text, "Сервер готов принимать данные");
            break;
        case 3:
            sprintf(error_text, "ошибка вызова listen()");
            break;
        case 4:
            sprintf(error_text, "Ошибка вызова accept()");
            break;
        case 5:
            sprintf(error_text, "Ошибка вызова fork()");
            break;
        case 6:
            sprintf(error_text, "Unable to setsockopt");
            break;
        case 7:
            sprintf(error_text, "ошибка функции read()");
            break;
        case 8:
            sprintf(error_text, "Невозможно выполнить stat() для root-директории FTP сервера");
            break;
        case 9:
            sprintf(error_text, "Невозможно перейти в root-директорию FTP сервера");
            break;
        case 10:
            sprintf(error_text, "Ошибка запуска /bin/ls");
            break;
        case 11:
            sprintf(error_text, "Ошибка open()");
            break;
        case 12:
            sprintf(error_text, "Ошибка connect()");
            break;
        default:
            sprintf(error_text, "Неправильный номер ошибки");
    }
    fprintf(stderr, "[%s]:[%s] -> %s\n", type1, type2, error_text);
    free(error_text);
    if(quit_after_error == 1)
    {
        my_exit(0);
    }
}

int check_user_pass(char * username, char * password)
{
    return 1;
}

char ** split (char * string, int type) {
  int elems = 0, i, st = 0, **sf, size, length, x=0;
  char ** result;
  if(string[strlen(string)-1]=='\n'){
    length = strlen(string)-1;
  }else{
    length = strlen(string);
  }
  if(length%2==0){
    size=length/2;
  }else{
    size=(length+1)/2;
  }
  sf=(int**)malloc(size*4);
  for(i=0;i<size;i++){
    sf[i]=(int*)malloc(2*4);
    sf[i][0]=-1;
    sf[i][1]=-1;
  }
  for(i=0;i<length;i++){
    if(((string[i]==' '||string[i]=='\t')&&type==0)||((string[i]==',')&&type==1)){
      if(st==1){
        sf[x][1]=i-1;
        st=0;
      }
    }else{
      if(st==0){
        st=1;
        sf[x][0]=i;
      }
    }
    if(st==0&&sf[x][0]!=-1&&sf[x][1]!=-1){
      elems++;
      x++;
    }
  }
  if(st==1){
    sf[x][1]=i-1;
    elems++;
  }
  result=(char**)malloc((elems+1)*4);
  result[elems]=NULL;
  for(i=0;i<elems;i++){
    result[i]=(char*)malloc(sf[i][1]-sf[i][0]+2);
    memcpy(result[i], string+sf[i][0], sf[i][1]-sf[i][0]+1);
    result[i][sf[i][1]-sf[i][0]+1]=0;
  }
  return result;
}

int create_passive_socket(int port, char * host)
{
    int psocket, flag = 1;
    struct sockaddr_in serv_addr;
    if((psocket = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        print_errors(0,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
    }
    if(setsockopt( psocket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0 )
    {
        print_errors(6,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(host);
    serv_addr.sin_port = htons(port);

    if(bind(psocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        print_errors(1,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
    }
    print_errors(2,NOTICE_TYPE,CHILD_SERVER_PREFIX,0);
    
    if(listen(psocket, 20)<0)
    { 
        print_errors(3,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
    }  
    return psocket;
}

int connect_to_active_port(int port, char * host)
{
    struct sockaddr_in addr;
    int asock;
    if((asock = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        print_errors(0,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
        return -1;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(host);
    addr.sin_port = htons(port);
    print_errors(2,NOTICE_TYPE,CHILD_SERVER_PREFIX,0);
    if(connect(asock, (struct sockaddr *)&addr, sizeof(addr))<0)
    {
        print_errors(12,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
        close(asock);
        return -1;
    }
    return asock;
}

void strip(char * string){
  char * result = (char*)malloc(MAIN_FTP_CMD_BUF);
  int start=0, end=0, x=0, i;
  for(i=0;i<(int)strlen(string);i++){
    if(string[i]!=32 && string[i]!=9 && string[i]!='\n' && string[i]!=13) {
      start=i;
      break;
    }
  }
  for(i=strlen(string)-1;i>=0;i--){
    if(string[i]!=32 && string[i]!=9 && string[i]!='\n' && string[i]!=13) {
      end=i;
      break;
    }
  }
  for(i=start;i<=end;i++){
    if(i==end && ( string[i]==32 || string[i]==9 || string[i]=='\n' || string[i]==13))break;
    result[x]=string[i];
    x++;
  }
  result[x]=0;
  memset(string,0,strlen(string));
  memcpy(string, result, strlen(result));
  free(result);
}

void free_mass(char ** mycmd, int n)
{
    int x;
    for(x=0;x<n;x++)free(mycmd[x]);
    free(mycmd);
}

void close_all_data_sockets(int pasv_sock, int data_sock)
{
    if(pasv_sock!=-1)close(pasv_sock);
    if(data_sock!=-1)close(data_sock);
    pasv_sock=-1;
    data_sock=-1;
}

void main_funct(int new_sock)
{
    
    int length, yo, data_port = -1, num_blocks, rest, identifed = 0, x, y, z, pasv_sock = -1, data_sock = -1, lspid, data_type = -1;
    unsigned int addrlen;
    //-----------------------------------------------------------------------------------------------------
    struct sockaddr_in clnt_addr, serv_addr;
    struct stat fstat;
    struct timezone tz;
    struct timeval tv;
    //-----------------------------------------------------------------------------------------------------
    fd_set rfds;
    //-----------------------------------------------------------------------------------------------------
    char user[256], pass[256], text[MAIN_FTP_CMD_BUF], tmp[256], pwd[256], mask[10], buffer[MAIN_FTP_CMD_BUF], **mycmd, **double_tmp, filebuff[FILE_BLOCK];
    char cmds[CMD_NUM][CMD_LENGTH] = { 
        "ABOR","ACCT","ALLO","APPE","CDUP","CWD ","DELE","EPRT","EPSV","FEAT","HELP","LIST","MDTM","MKD ",
        "MODE","NLST","NOOP","OPTS","PASS","PASV","PORT","PWD ","QUIT","REIN","REST","RETR","RMD ","RNFR",
        "RNTO","SITE","SIZE","SMNT","STAT","STOR","STOU","STRU","SYST","TYPE","USER","XCUP","XCWD","XMKD",
        "XPWD","XRMD"
    };
    char *path = (char*)malloc(256);
    char *user_arg = (char*)malloc(256);
    char *cmd[] = { "ls", user_arg, path, (char *)0 };
    char *env[] = { "LANG=C", (char *)0 };
    //-----------------------------------------------------------------------------------------------------
    sprintf(pwd,"/");
    gettimeofday(&tv, &tz);
    srand(tv.tv_usec);
    //-----------------------------------------------------------------------------------------------------
    memset(user,0,256);
    memset(pass,0,256);
    memset(&clnt_addr, 0, sizeof(clnt_addr));
    //-----------------------------------------------------------------------------------------------------
    addrlen = sizeof(clnt_addr);
    getpeername(new_sock,(struct sockaddr *)&clnt_addr, &addrlen);
    memset(&serv_addr, 0, sizeof(serv_addr));
    addrlen = sizeof(serv_addr);
    getsockname(new_sock, (struct sockaddr *)&serv_addr, &addrlen);
    //-----------------------------------------------------------------------------------------------------
    sprintf(buffer, "220 %s (%s)\r\n", HELLO_MSG,inet_ntoa(serv_addr.sin_addr));
    send(new_sock, buffer, strlen(buffer), 0);
    while(1)
    {
        memset(text,           0,MAIN_FTP_CMD_BUF);
        memset(buffer,         0,MAIN_FTP_CMD_BUF);
        memset(tmp            ,0,             256);
        memset(mask           ,0,              10);
        FD_ZERO( &rfds );
        FD_SET( new_sock, &rfds );
        tv.tv_sec  = 600; 
        tv.tv_usec =   0; 
        select(new_sock+1, &rfds, NULL, NULL, &tv);
        if (!FD_ISSET(new_sock, &rfds))
        {
            sprintf(buffer, "421 No Transfer Timeout (600 seconds): closing control connection\r\n");
            send(new_sock, buffer, strlen(buffer), 0);
            break;
        }      
        length = recv(new_sock, buffer, sizeof(buffer), 0);
        buffer[strlen(buffer)-1]=32;
        strip(buffer);
        mycmd=split(buffer,0);
        z=0;
        while(mycmd[z]!=NULL)z++;
        memset(buffer,32,strlen(mycmd[0]));
        strip(buffer);
        for(x=0;x<strlen(mycmd[0]);x++)mycmd[0][x] = toupper(mycmd[0][x]);
        if (length > 0)
        {
            yo = 0;
//-QUIT-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "QUIT")==0 && yo == 0)
            {
                yo = 1;
                sprintf(buffer, "221 Goodbye\r\n");
                send(new_sock, buffer, strlen(buffer), 0);
                free_mass(mycmd, z);
                break;
            }
//-USER-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "USER")==0 && yo == 0)
            {
                yo = 1;
                memcpy(user, buffer, strlen(buffer));
                sprintf(buffer, "331 Please specify the password\r\n");
                identifed = 1;
            }
//-PASS-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "PASS")==0 && yo == 0)
            {
                yo = 1;
                if(identifed == 1)
                {
                    memcpy(pass, buffer, strlen(buffer));
                    if(check_user_pass(user,pass)==1)
                    {
                        identifed = 2;
                        sprintf(buffer, "230 Login successful\r\n");
                    }
                    else
                    {
                        identifed = 0;
                        sprintf(buffer, "530 Login incorrect\r\n");
                    }
                }
                else
                {
                    sprintf(buffer, "503 Login with USER first\r\n");
                }               
            }
            if(identifed != 2 && yo == 0)
            {
                yo = 1;
                sprintf(buffer, "530 Please login with USER and PASS\r\n");
            }
//-TYPE-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "TYPE")==0 && yo == 0)
            {
                yo = 1;
                sprintf(buffer, "200 Switching to Binary mode\r\n");
            }
//-SYST-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "SYST")==0 && yo == 0)
            {
                yo = 1;
                sprintf(buffer, "215 UNIX Type: L8\r\n");
            }
//-PWD--------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "PWD")==0 && yo == 0)
            {
                yo = 1;
                sprintf(buffer, "257 \"%s\"\r\n", pwd);
            }
//-CWD--------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "CWD")==0 && yo == 0)
            {
                if(buffer[0] == '/')
                {
                    sprintf(tmp, "%s%s", ROOT_PATH,buffer);
                }
                else
                {
                    sprintf(tmp, "%s%s%s", ROOT_PATH,pwd,buffer);
                }
                if(chdir(tmp)<0)
                {
                    sprintf(buffer, "550 Failed to change directory\r\n");
                }
                else
                {
                    memset(tmp,0,256);
                    getcwd(tmp,256);
                    if(strncmp(ROOT_PATH,tmp,strlen(ROOT_PATH))!=0)
                    {
                        chdir(ROOT_PATH);
                        fprintf(stderr, "1='%s'\n2='%s'\n", ROOT_PATH, tmp);
                        sprintf(buffer, "250 Directory successfully changed\r\n");
                    }
                    else
                    {
                        memset(pwd,0,256);
                        memcpy(pwd,tmp+strlen(ROOT_PATH),strlen(tmp)-strlen(ROOT_PATH));
                        if(pwd[strlen(pwd)-1]!='/')pwd[strlen(pwd)]='/';
                        sprintf(buffer, "250 Directory successfully changed\r\n");
                    }
                }
                yo = 1;
            }
//-SIZE-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "SIZE")==0 && yo == 0)
            {
                if(buffer[0] == '/')
                {
                    sprintf(tmp, "%s%s", ROOT_PATH,buffer);
                }
                else
                {
                    sprintf(tmp, "%s%s%s", ROOT_PATH,pwd,buffer);
                }
                if(stat(tmp, &fstat)<0)
                {
                    sprintf(buffer, "550 Could not get file size\r\n");
                }
                else
                {
                    sprintf(buffer, "213 %d\r\n", (int)fstat.st_size);
                }
                yo = 1;
            }
//-RETR-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "RETR")==0 && yo == 0)
            {
                x = 1;
                if(data_type==-1)
                {
                    sprintf(buffer, "425 Use PORT or PASV first\r\n");
                }
                else
                {
                    if(buffer[0] == '/')
                    {
                        sprintf(tmp, "%s%s", ROOT_PATH,buffer);
                    }
                    else
                    {
                        sprintf(tmp, "%s%s%s", ROOT_PATH,pwd,buffer);
                    }
                    y = stat(tmp, &fstat);
                    sprintf(mask, "%o", fstat.st_mode);
                    if(!y && atoi(mask)/10000 == 10)
                    {
                        if(data_type==0)
                        {
                            FD_ZERO( &rfds );
                            FD_SET( pasv_sock, &rfds );
                            tv.tv_sec = 60; 
                            tv.tv_usec = 0; 
                            select(pasv_sock+1, &rfds, NULL, NULL, &tv);
                            if (FD_ISSET(pasv_sock, &rfds))
                            {
                                memset(&clnt_addr, 0, sizeof(clnt_addr));
                                addrlen = sizeof(clnt_addr);
                                if((data_sock = accept(pasv_sock, (struct sockaddr *)&clnt_addr, &addrlen))<0)
                                {
                                    print_errors(4,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
                                    sprintf(buffer, "425 Failed to establish connection\r\n");
                                    x = 0;
                                }
                            }
                        }
                        if(x == 1)
                        {
                            sprintf(buffer, "150 Opening BINARY mode data connection for %s (%d bytes).\r\n", text, (int)fstat.st_size);
                            send(new_sock, buffer, strlen(buffer), 0);
                            if((y = open(tmp, O_RDONLY))<0)
                            {
                                print_errors(11,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
                                sprintf(buffer, "550 Failed to open file.\r\n");
                                x=0;
                            }
                            if(x==1)
                            {
                                num_blocks = fstat.st_size/FILE_BLOCK;
                                rest = fstat.st_size%FILE_BLOCK;
                                x = 0;
                                for(x=0;x<num_blocks;x++)
                                {
                                    read(y, filebuff, FILE_BLOCK);
                                    send(data_sock, filebuff, FILE_BLOCK, 0);
                                }
                                if(rest != 0)
                                {
                                    read(y, filebuff, rest);
                                    send(data_sock, filebuff, rest, 0);   
                                }
                                sprintf(buffer, "226 File send OK\r\n");
                            }
                        }
                    }
                    else
                    {
                        sprintf(buffer, "550 Failed to open file.\r\n");
                    }               
                }
                close_all_data_sockets(pasv_sock,data_sock);
                data_type=-1;
                data_port=-1;
                yo=1;                
            }
//-STOR-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "STOR")==0 && yo == 0)
            {
                x = 1;
                if(data_type==-1)
                {
                    sprintf(buffer, "425 Use PORT or PASV first\r\n");
                }
                else
                {
                    if(buffer[0] == '/')
                    {
                        sprintf(tmp, "%s%s", ROOT_PATH,buffer);
                    }
                    else
                    {
                        sprintf(tmp, "%s%s%s", ROOT_PATH,pwd,buffer);
                    }
                    y = stat(tmp, &fstat);
                    sprintf(mask, "%o", fstat.st_mode);
                    if(!y && atoi(mask)/10000 != 10)
                    {
                        sprintf(tmp, "550 %s: Not a regular file\r\n", buffer);
                        memcpy(buffer,tmp,strlen(tmp));
                    }
                    else 
                    {
                        if((y = open(tmp, O_RDWR))<0)
                        {
                            if((y = open(tmp, O_RDWR | O_CREAT, 0644))<0)
                            {
                                print_errors(11,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
                                sprintf(tmp, "550 %s: Can't create file\r\n", buffer);
                                x=0;
                            }
                            if(!(y<0))
                            {
                                close(y);
                                remove(tmp);
                            }
                        }
                        if(!(y<0))close(y);
                        if(x==1)
                        {
                            if(data_type==0)
                            {
                                FD_ZERO( &rfds );
                                FD_SET( pasv_sock, &rfds );
                                tv.tv_sec = 60; 
                                tv.tv_usec = 0; 
                                select(pasv_sock+1, &rfds, NULL, NULL, &tv);
                                if (FD_ISSET(pasv_sock, &rfds))
                                {
                                    memset(&clnt_addr, 0, sizeof(clnt_addr));
                                    addrlen = sizeof(clnt_addr);
                                    if((data_sock = accept(pasv_sock, (struct sockaddr *)&clnt_addr, &addrlen))<0)
                                    {
                                        print_errors(4,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
                                        sprintf(buffer, "425 Failed to establish connection\r\n");
                                        x=0;
                                    }
                                }
                            }
                            if(x == 1)
                            {
                                if((y = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 0644))<0)
                                {
                                    print_errors(11,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
                                    sprintf(tmp, "550 %s: Can't create file\r\n", buffer);
                                    x=0;
                                }
                                if(x==1)
                                {
                                    sprintf(buffer, "150 Opening BINARY mode data connection for %s\r\n", text);
                                    send(new_sock, buffer, strlen(buffer), 0);
                                    yo=1;
                                    do{
                                        yo=recv(data_sock, &filebuff, FILE_BLOCK,0);
                                        write(y, &filebuff, yo);
                                    }while(yo>0);
                                    close(y);
                                    sprintf(buffer, "226 Transfer complete.\r\n");
                                }
                            }
                        }    
                    }    
                }
                close_all_data_sockets(pasv_sock,data_sock);
                data_type=-1;
                data_port=-1;
                yo=1;                
            }
//-LIST-&-NLST-------------------------------------------------------------------------------------
            if((strcmp(mycmd[0], "LIST")==0 || strcmp(mycmd[0], "NLST")==0) && yo == 0)
            {
                x = 1;
                y = 0;
                if(data_type==-1)
                {
                    sprintf(buffer, "425 Use PORT or PASV first\r\n");
                }
                else
                {
                    if(z>1&&mycmd[1][0]=='-')
                    {
                        memset(buffer,32,strlen(mycmd[1]));
                        strip(buffer);
                        y=1;
                    }
                    if(buffer[0] == '/')
                    {
                        sprintf(tmp, "%s%s", ROOT_PATH,buffer);
                    }
                    else
                    {
                        sprintf(tmp, "%s%s%s", ROOT_PATH,pwd,buffer);
                    }
                    if(!stat(tmp, &fstat)||!strcmp(mycmd[0], "NLST"))
                    {
                        if(data_type==0)
                        {
                            FD_ZERO( &rfds );
                            FD_SET( pasv_sock, &rfds );
                            tv.tv_sec = 60; 
                            tv.tv_usec = 0; 
                            select(pasv_sock+1, &rfds, NULL, NULL, &tv);
                            if (FD_ISSET(pasv_sock, &rfds))
                            {
                                memset(&clnt_addr, 0, sizeof(clnt_addr));
                                addrlen = sizeof(clnt_addr);
                                if((data_sock = accept(pasv_sock, (struct sockaddr *)&clnt_addr, &addrlen))<0)
                                {
                                    print_errors(4,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
                                    sprintf(buffer, "425 Failed to establish connection\r\n");
                                    x = 0;
                                }
                            }
                        }
                        if(x == 1)
                        {
                            lspid=fork();
                            if(lspid==0)
                            {
                                dup2( data_sock, 0 );
                                dup2( data_sock, 1 );
                                if(!strcmp(mycmd[0], "NLST"))
                                {
                                    sprintf(cmd[1], "-1");
                                    sprintf(cmd[2], "%s", buffer);                                    
                                }
                                else
                                {
                                    if(y==0)
                                    {
                                        sprintf(cmd[1], "-l");
                                        sprintf(cmd[2], "%s", tmp);
                                    }
                                    else
                                    {
                                        sprintf(cmd[1], "%s", mycmd[1]);
                                        sprintf(cmd[2], "%s", tmp);
                                    }
                                }
                                sprintf(buffer, "150 Here comes the directory listing\r\n");
                                send(new_sock, buffer, strlen(buffer), 0);
                                if(execve("/bin/ls", cmd, env)<0)
                                {
                                    print_errors(10,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
                                }
                                sprintf(buffer, "\r\n");
                                send(new_sock, buffer, strlen(buffer), 0);
                                exit(0);
                            }
                            if(lspid<0)
                            {
                                print_errors(5,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
                            }
                            wait(NULL);
                        }
                    }
                    sprintf(buffer, "226 Directory send OK\r\n");                    
                }
                close_all_data_sockets(pasv_sock,data_sock);
                data_type=-1;
                data_port=-1;
                yo=1;
            }
//-PASV-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "PASV")==0 && yo == 0)
            {
                close_all_data_sockets(pasv_sock,data_sock);
                data_type=-1;
                data_port = PASSIVE_PORT_START+(int)((double)(PASSIVE_PORT_END-PASSIVE_PORT_START)*rand()/(RAND_MAX+1.0));
                sprintf(buffer, "227 Entering Passive Mode (%s,%u,%u)\r\n", inet_ntoa(serv_addr.sin_addr),(data_port >> 8) & 255, data_port & 255);
                for(y=0;y<strlen(buffer);y++)
                {
                    if(buffer[y]=='.')buffer[y]=',';
                }
                pasv_sock = create_passive_socket(data_port, inet_ntoa(serv_addr.sin_addr));
                if(pasv_sock!=-1)
                {   
                    data_type=0;
                }
                else
                {
                    data_port=-1;
                }
                yo=1;
            }
//-PORT-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "PORT")==0 && yo == 0)
            {
                close_all_data_sockets(pasv_sock,data_sock);
                data_type=-1;
                double_tmp=split(buffer,1);
                y=0,x=0;
                while(double_tmp[y]!=NULL)y++;
                if(y==6)
                {
                    sprintf(buffer, "200 PORT command successful\r\n");
                    data_port=atoi(double_tmp[4])*256+atoi(double_tmp[5]);
                    if(data_port <=0 || data_port >= 65536)
                    {
                        x=-1;
                    }
                    else
                    {
                        sprintf(tmp, "%s.%s.%s.%s", double_tmp[0],double_tmp[1],double_tmp[2],double_tmp[3]);
                        if((data_sock=connect_to_active_port(data_port, tmp))<0)
                        {
                            x=-1;
                        }
                        else
                        {
                            data_type=1;
                        }
                    }
                }
                if(x!=0)
                {
                    sprintf(buffer, "500 Illegal PORT command\r\n");
                    data_sock=-1;
                    data_port=-1;
                }
                free_mass(double_tmp, y);
                yo = 1;
            }
//-HELP-------------------------------------------------------------------------------------------
            if(strcmp(mycmd[0], "HELP")==0 && yo == 0)
            {
                y = 0;
                sprintf(buffer, "214-The following commands are recognized.\r\n");
                for(x=0;x<CMD_NUM;x++)
                {
                    if(y == 15 && x+1 < CMD_NUM)
                    {
                        strcat(buffer, "\n ");
                        y = 0;
                    }
                    else
                    {
                        strcat(buffer, " ");
                    }
                    sprintf(tmp, "%s", cmds[x]);
                    strcat(buffer, tmp);
                    y++;
                }
                strcat(buffer, "\n");
                strcat(buffer, "214 Help OK\r\n");
                yo = 1;
            }
//-MDTM-------------------------------------------------------------------------------------------            
            if(strcmp(mycmd[0], "MDTM")==0 && yo == 0)
            {
                if(buffer[0] == '/')
                {
                    sprintf(tmp, "%s%s", ROOT_PATH,buffer);
                }
                else
                {
                    sprintf(tmp, "%s%s%s", ROOT_PATH,pwd,buffer);
                }
                if(stat(tmp, &fstat)<0)
                {
                    sprintf(buffer, "550 Could not get file modification time\r\n");
                }
                else
                {
                    strftime(tmp,256,"%Y%m%d%H%M%S",localtime(&fstat.st_mtime));
                    sprintf(buffer, "213 %s\r\n",tmp);
                }
                yo = 1;
            }
            if(yo == 0)
            {
                sprintf(buffer, "500 Unknown command\r\n");
            }
            send(new_sock, buffer, strlen(buffer), 0);         
        }
        else if (length == 0)
        {
            fprintf(stderr, "[%s]:[%s] -> Подключение к клиенту %s утеряно\n", NOTICE_TYPE,CHILD_SERVER_PREFIX,inet_ntoa(clnt_addr.sin_addr));
            break;
        }
        else
        {
            print_errors(7,ERROR_TYPE,CHILD_SERVER_PREFIX,0);
            break;
        }
    }
    close_all_data_sockets(pasv_sock,data_sock);
    close(new_sock);
    exit(1);
}

int main (int argc, char ** argv)
{
    struct sockaddr_in serv_addr, clnt_addr;
    struct stat fstat;
    int new_sock, flag = 1;
    unsigned int addrlen;
    pid_t pid;
    signal(SIGINT, &my_exit);
    signal(SIGCHLD, &child_quit_handler);
    if(stat(ROOT_PATH, &fstat)<0)
    {
        print_errors(8,ERROR_TYPE,MAIN_SERVER_PREFIX,1);
    }
    if(chdir(ROOT_PATH)<0)
    {
        print_errors(9,ERROR_TYPE,MAIN_SERVER_PREFIX,1);
    }
    if((main_server_socket = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        print_errors(0,ERROR_TYPE,MAIN_SERVER_PREFIX,1);
    }
    
    if(setsockopt( main_server_socket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0 )
    {
        print_errors(6,ERROR_TYPE,MAIN_SERVER_PREFIX,1);
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(DEFAULT_PORT_NUM);

    if(bind(main_server_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        print_errors(1,ERROR_TYPE,MAIN_SERVER_PREFIX,1);
    }
    print_errors(2,NOTICE_TYPE,MAIN_SERVER_PREFIX,0);
    
    if(listen(main_server_socket, 20)<0)
    { 
        print_errors(3,ERROR_TYPE,MAIN_SERVER_PREFIX,1);
    }
  
    while (1) {
        memset(&clnt_addr, 0, sizeof(clnt_addr));
        addrlen = sizeof(clnt_addr);
      
        if((new_sock = accept(main_server_socket, (struct sockaddr *)&clnt_addr, &addrlen))<0)
        {
            print_errors(4,ERROR_TYPE,MAIN_SERVER_PREFIX,1);
        }
        fprintf(stderr, "[%s]:[%s] -> Установлено соединение с клиентом %s:%d\n", NOTICE_TYPE, MAIN_SERVER_PREFIX, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
        pid = fork();
        switch(pid)
        {
            case -1:
                print_errors(5,ERROR_TYPE,MAIN_SERVER_PREFIX,1);
                break;
            case 0:
                close(main_server_socket);
                main_funct(new_sock);
                break;
            default:
                close(new_sock);
        }
    }
    my_exit(0);
    return 0;
}
