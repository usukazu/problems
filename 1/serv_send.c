#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void die (char *s){
  perror(s);
  exit(1);
}

int main(int argc, char ** argv)
{
  int ss = socket(PF_INET, SOCK_STREAM,0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[1]));
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(ss, (struct sockaddr*)&addr, sizeof(addr));
  listen(ss,10);
  struct sockaddr_in client_addr;
  socklen_t len = sizeof(struct sockaddr_in);
  int s = accept(ss, (struct sockaddr*)&client_addr,&len);
  close(ss);
  //printf("%d\n",fd);
  //printf("%d\n",errno);
  int begin=0;
  int end =256;
  char *data=(char *)malloc(end);
  while(1){
      int n=read(0,data+begin,256);
      if(n==-1)die("read");
      //printf("%d %d\n",n,end-begin);
      if(n<end-begin || n>40000){
          end=begin+n;
          break;
      }
      begin=end; //ここが+=になってた
      end+=256;
      char *newdata=(char *)malloc(end);
      bcopy(data, newdata, end-256);
      free(data);
      data=newdata;
      
  }
  printf("%d\n",end);
  int n=send(s,data,end,0);
  printf("n=%d\n",n);
  if(n==-1)die("send");
  close(s);
  
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
