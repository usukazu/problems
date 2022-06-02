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
#include <time.h>

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
  //int begin=0;
  //int end =16384;
  
  int N=32768;
  char *data=(char *)malloc(N);
  FILE	*fp;
  char	*cmdline = "rec -t raw -b 16 -c 1 -e s -r 44100 -";
  if ( (fp=popen(cmdline,"r")) ==NULL) {
	    perror ("can not exec commad");
		exit(EXIT_FAILURE);
  }
  while(1){
      /*int n=fread(data+begin,1,256,fp);
      if(n==-1)die("read");
      if(n<end-begin){
          end=begin+n;
          //printf("end=%d\n",end);
          break;
      }
      if(end>=N){
        n=send(s,data,N,0);
        begin=0;
        end=256;
      }else{
        begin=end;
        end+=256;
      }
      //printf("%d\n",end);
      char *newdata=(char *)malloc(end);
      bcopy(data, newdata, end-256);
      free(data);
      data=newdata;*/
      int n=fread(data,1,N,fp);
      if(n==0)break;
      n=send(s,data,N,0);
      //sendto(ss, data, N, 0,(struct sockaddr *)&addr, sizeof(addr));
  }
  //printf("data=%d\n",sizeof(data));
  //int n=send(s,data,end,0);
  //if(n==-1)die("send");
  //int a=write(1,data,2*end);
  //printf("n=%d\n",n);
  pclose(fp);
  close(ss);
  
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
