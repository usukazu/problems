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

void die (char *s){
  perror(s);
  exit(1);
}

int main(int argc, char ** argv)
{
  int fd = open(argv[1], O_RDONLY);
  if (fd==-1)die("open");
  //printf("%d\n",fd);
  //printf("%d\n",errno);
  int N=256;
  short *data=(short *)malloc(2*N);
  while(1){
      int n=read(fd,data+N-256,2*256);
      if(n==-1)die("read");
      if(n>=0&&n<512){
          N-=256-n/2;
          break;
      }
      N+=256;
      short *newdata=(short *)malloc(2*N);
      bcopy(data, newdata, 2*(N-256));
      free(data);
      data=newdata;
  }
  close(fd);
  for(int i=0;i<N;i++){
    printf("%d %d\n",i,data[i]);
  }
  
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
