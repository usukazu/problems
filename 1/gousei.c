#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
  int a=0;
  int N=16384;
  short *data=(short *)malloc(2*N);
  short *read=(short *)malloc(2);
  int begin,end;
  while(1){
    char filename[124];
    bool flag=true;
	scanf("%s" , filename);
    FILE *fp;
    if(strcmp(filename,"q")==0)break;
    fp = fopen(filename, "r");
	if (fp != NULL){
        printf("read %s\n",filename);
        if(a==0){
            begin=0;
            end =N;
            a=1;
        }else{
            begin=end;
            for(int i=0;i<end;i++){
                int n=fread(read,2,1,fp);
                if(n==1)data[i]+=*read;
                if(n<1){
                    flag=false;
                    break;
                }
            }
            if(flag){
                end+=N;
                short *newdata=(short *)malloc(2*end);
                bcopy(data, newdata, 2*end-2*N);
                free(data);
                data=newdata;
            }
        }
        while(flag){
            int n=fread(data+begin,2,end-begin,fp);
            if(n==-1)die("read");
            if(n<end-begin){
                end=begin+n;
                break;
            }
            begin=end;
            end+=N;
            short *newdata=(short *)malloc(2*end);
            bcopy(data, newdata, 2*end-2*N);
            free(data);
            data=newdata;
        }
    }else{
        printf("can't read %s\n",filename);
    }
    printf("end=%d\n",end);
    fclose(fp);
  }
  FILE *newfp;
  newfp = fopen(argv[1], "w");
  a=fwrite(data,2,end,newfp);
  //printf("%d\n",errno);
  //printf("%d\n",a);
  //printf("%c\n",data[49]);
  return 0;
}
