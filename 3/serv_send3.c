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
#include <complex.h>
#include <math.h>
#include "fftfunc.h"

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
  
  int N=16384;
  short *data=(short *)malloc(sizeof(short)*N);
  complex float * X = calloc(sizeof(complex float), N);
  complex float * Y = calloc(sizeof(complex float), N);
  complex float * newY = calloc(sizeof(complex float), N);
  unsigned char *memo= calloc(sizeof(unsigned char), N/16);
  int num=0;
  FILE	*fp;
  char	*cmdline = "rec -t raw -b 16 -c 1 -e s -r 44100 -";
  if ( (fp=popen(cmdline,"r")) ==NULL) {
	    perror ("can not exec commad");
		exit(EXIT_FAILURE);
  }
  while(1){
      memset(newY, 0, 8*N);
      memset(memo, 0, N/16);
      int n=fread(data,2,N,fp);
      if (n==-1) die("read");
      if(n==0)break;
      if(n<N)memset(data + 2*n, 0, 2*(N-n));
      sample_to_complex(data, X, N);
      fft(X, Y, N);
      num=cut_data(Y,newY,memo,N);
      n=send(s,memo,N/16,0);
      if (n==-1) die("send");
      n=send(s,newY,8*num,0);
      if (n==-1) die("send");
  }
  pclose(fp);
  close(s);
  return 0;
}
