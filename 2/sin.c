#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define _USE_MATH_DEFINES
#include <math.h>

void die (char *s){
  perror(s);
  exit(1);
}

int main(int argc, char ** argv)
{
  long A=atoi(argv[1]);
  double f=atof(argv[2]);
  int N=atoi(argv[3]);
  short data[N];
  for(long i=0;i<N;i++){
      data[i]=(short)(A*sin(2*M_PI*f*i/44100));
  }
  int a=write(1,data,2*N);
  //printf("%d %d\n",sizeof(data),2*N);
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
