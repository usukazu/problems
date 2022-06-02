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
  int s = socket(PF_INET, SOCK_STREAM,0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  int a=inet_aton(argv[1],&addr.sin_addr);
  if(a==0)die("addr");
  addr.sin_port = htons(50000);
  int ret = connect(s,(struct sockaddr*)&addr, sizeof(addr));
  //printf("%d\n",fd);
  //printf("%d\n",errno);
  int begin=0;
  int end =2;
  char *data=(char *)malloc(end);
  while(1){
      int n=recv(s,data+begin,2,0);
      if(n==-1)die("read");
      if(n<end-begin){
          end=begin+n;
          printf("end=%d\n",end);
          break;
      }
      begin=end;
      end+=2;
      char *newdata=(char *)malloc(end);
      bcopy(data, newdata, end-2);
      free(data);
      data=newdata;
  }
  close(s);
  a=write(1,data,end);//ここがprintfだとrawは出力できない
  
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
