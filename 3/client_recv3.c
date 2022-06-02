#include <assert.h>
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

int bitcount(char* memo,int n){
    int count=0;
    for(int i=0;i<n;i++){
        char b8 =memo[i];
	    b8 = (unsigned char)( ((b8 & 0xAA) >> 1) + (b8 & 0x55) );
	    b8 = (unsigned char)( ((b8 & 0xCC) >> 2) + (b8 & 0x33) );
	    b8 = (unsigned char)( ((b8 & 0xF0) >> 4) + (b8 & 0x0F) );
        count+=b8;
    }
	return count;
}

int main(int argc, char ** argv)
{
  int s = socket(PF_INET, SOCK_DGRAM,0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  int a=inet_aton(argv[1],&addr.sin_addr);
  if(a==0)die("addr");
  addr.sin_port = htons(atoi(argv[2]));
  int ret = connect(s,(struct sockaddr*)&addr, sizeof(addr));
  int N=16384;
  short *data=(short *)malloc(sizeof(short)*N);
  complex float * X = calloc(sizeof(complex float), N);
  complex float * Y = calloc(sizeof(complex float), N);
  complex float * newY = calloc(sizeof(complex float), N);
  char *memo=(char *)malloc(N/16);
  int i=0;
  int j=0;
  int num=0;
  while(1){
      memset(Y, 0, 8*N);
      memset(newY, 0, 8*N);
      int n=recv(s,memo,N/16,0);
      //printf("n=%d\n",n);
      if(n==-1)die("recv");
      if(n==0)break;
      num = bitcount(memo,N/16);
      //printf("num=%d\n",num);
      n=recv(s,newY,num*8,0);
      //printf("n=%d\n",n);
      if(n==-1)die("recv");
      if(j!=1){
      remake_data(Y,newY,memo,N);
      ifft(Y, X, N);
      complex_to_sample(X, data, N);
        n=write(1, data, 2*N);
        if(n==-1)die("write");
      }
      j++;
  }
  close(s);
  return 0;
}
