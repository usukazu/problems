#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  /*socklen_t sin_size;
  struct sockaddr_in from_addr;*/
  int s = socket(PF_INET, SOCK_STREAM,0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  int a=inet_aton(argv[1],&addr.sin_addr);
  if(a==0)die("addr");
  addr.sin_port = htons(atoi(argv[2]));
  int ret = connect(s,(struct sockaddr*)&addr, sizeof(addr));
  //bind(s, (struct sockaddr *)&addr, sizeof(addr));
  //printf("%d\n",fd);
  //printf("%d\n",errno);
  //int begin=0;
  //int end =4;
  int N=32768;
  char *data=(char *)malloc(N);
  int i=0;
  while(1){
      /*int n=recv(s,data+begin,256,0);
      if(n==-1)die("read");
      if(n<end-begin){
          end=begin+n;
          printf("end=%d\n",end);
          break;
      }
      begin=end;s
      end+=256;
      char *newdata=(char *)malloc(end);
      bcopy(data, newdata, end-256);
      free(data);
      data=newdata;*/
      memset(data, 0, N);
      //recvfrom(s, data, N, 0,(struct sockaddr *)&from_addr, &sin_size);
      int n=recv(s,data,N,0);
      if(n==0)break;
      a=write(1,data,N);//ここがprintfだとrawは出力できない
      /*char	*cmdline = "play -t raw -b 16 -c 1 -e s -r 44100 -";
      FILE	*fp;
      if ( (fp=popen(cmdline,"r")) ==NULL) {
	      perror ("can not exec commad");
		  exit(EXIT_FAILURE);*/
  }
  close(s);
  
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
