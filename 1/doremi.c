#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

void die (char *s){
  perror(s);
  exit(1);
}

int main(int argc, char ** argv)
{
  long A=atoi(argv[1]);
  int n=atoi(argv[2]);
  short data[n*13230];
  double drm[7]={-9,-7,-5,-4,-2,0,2};
  double iso=0;
  for(int i=0;i<n;i++){
      for(long j=0;j<13230;j++){
        data[i*13230+j]=A*sin(2*M_PI*440*pow(2.0,((int)i/7)+drm[i%7]/12)*j/44100+iso);
      }
      iso+=2*M_PI*440*pow(2.0,((int)i/7)+drm[i%7]/12)*3/10;
  }
  int a=write(1,data,2*n*13230);
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
