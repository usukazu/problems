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
  double bpm=atoi(argv[2]);
  int n=atoi(argv[3]);
  int bu = 44100*15/bpm;
  short data[n*bu*16];
  for(int i=0;i<4*n;i++){
      for(int j=0;j<4*bu;j++){
        if(j<bu){
            if(i%4==0){
                data[i*4*bu+j]=A*sin(2*M_PI*524*j/44100);
            }
            else data[i*4*bu+j]=A*sin(2*M_PI*262*j/44100);
        }
        else data[i*4*bu+j]=0;
      }
  }
  int a=write(1,data,n*bu*32);
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
