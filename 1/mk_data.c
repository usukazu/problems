#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void die (char *s){
  perror(s);
  exit(1);
}

int main(int argc, char ** argv)
{
  int fd = open(argv[1], O_WRONLY|O_CREAT,0644);
  if (fd==-1)die("open");
  //printf("%d\n",fd);
  //printf("%d\n",errno);
  int N=256;
  unsigned char data[N];
  for(int i=0;i<N;i++){
      data[i]=i;
  }
  int a=write(fd,data,N);
  close(fd);
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
