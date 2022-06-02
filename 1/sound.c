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
#include <string.h>
#define roop(n) for(int i=0;i<n;i++)

double iso;
double dn;

void die (char *s){
  perror(s);
  exit(1);
}

int encode(char* s){
    int ans;
    if(strncmp(s,"do",2)==0)ans=-9;
    else if(strncmp(s,"re",2)==0)ans=-7;
    else if(strncmp(s,"mi",2)==0)ans=-5;
    else if(strncmp(s,"fa",2)==0)ans=-4;
    else if(strncmp(s,"so",2)==0)ans=-2;
    else if(strncmp(s,"ra",2)==0)ans=0;
    else if(strncmp(s,"si",2)==0)ans=2;

    if(s[2]=='b')ans-=1;
    else if(s[2]=='#')ans+=1;
    return ans;
}

void sound(char* oto,int oct,int n,double bpm,int A){
    double leng=44100*240/bpm/n+dn;
    int num=floor(leng);
    short data[num];
    double hz=440*pow(2.0,(double)oct+(double)encode(oto)/12);
    int j;
    if(iso==0.0&&dn==0.0)j=5;
    else j=1;
    iso+=hz/44100*dn*-1;
    for(int i=0;i<num;i++){
        data[i]=A/j*sin(2*M_PI*iso);
        iso+=hz/44100*fmin(1,leng);
        if(iso>=1.0){
          iso-=1.0;
          if(j>1)j--;
        }
        leng-=1.0;
    }
    dn=leng;
    write(1,data,num*2);
}

void soundc(char* oto,int oct,int n,double bpm,int A,int B){
    double leng=44100*240/bpm/n+dn;
    int num=floor(leng);
    short data[num];
    double hz=440*pow(2.0,(double)oct+(double)encode(oto)/12);
    int big=A;
    iso+=hz/44100*dn*-1;
    for(int i=0;i<num;i++){
        data[i]=big*sin(2*M_PI*iso);
        iso+=hz/44100*fmin(1,leng);
        if(iso>=1.0){
          iso-=1.0;
          big=B;
        }
        leng-=1.0;
    }
    dn=leng;
    write(1,data,num*2);
}

void zero(char* oto,int oct,int n,double bpm,int A){
    double leng=44100*240/bpm/n+dn;
    int num=floor(leng);
    short data[num];
    double hz=440*pow(2.0,(double)oct+(double)encode(oto)/12);
    iso+=hz/44100*dn*-1;
    for(int i=0;i<num;i++){
        data[i]=A*sin(2*M_PI*iso);
        iso+=hz/44100*fmin(1,leng);
        if(iso>=1.0){
          iso-=0.0;
          A/=1.005;
        }
        leng-=1.0;
    }
    iso=0.0;
    dn=0.0;
    write(1,data,num*2);
}

int main(int argc, char ** argv)
{
  /*
  //かえるのうた
  iso=0;
  dn=0;
  double bpm=120;
  int A=8000;

  roop(6){zero("do",0,1,bpm,0);}

  sound("do",0,4,bpm,A);
  sound("re",0,4,bpm,A);
  sound("mi",0,4,bpm,A);
  sound("fa",0,4,bpm,A);
  sound("mi",0,4,bpm,A);
  sound("re",0,4,bpm,A);
  sound("do",0,4,bpm,A);
  zero("do",0,4,bpm,A);

  soundc("mi",0,4,bpm,0,A);
  sound("fa",0,4,bpm,A);
  sound("so",0,4,bpm,A);
  sound("ra",0,4,bpm,A);
  sound("so",0,4,bpm,A);
  sound("fa",0,4,bpm,A);
  sound("mi",0,4,bpm,A);
  zero("mi",0,4,bpm,A);

  roop(4){
    sound("do",0,4,bpm,A);
    zero("do",0,4,bpm,A);
  }

  sound("do",0,16,bpm,A);
  zero("do",0,16,bpm,A);
  sound("do",0,16,bpm,A);
  zero("do",0,16,bpm,A);
  sound("re",0,16,bpm,A);
  zero("re",0,16,bpm,A);
  sound("re",0,16,bpm,A);
  zero("re",0,16,bpm,A);
  sound("mi",0,16,bpm,A);
  zero("mi",0,16,bpm,A);
  sound("mi",0,16,bpm,A);
  zero("mi",0,16,bpm,A);
  sound("fa",0,16,bpm,A);
  zero("fa",0,16,bpm,A);
  sound("fa",0,16,bpm,A);
  zero("fa",0,16,bpm,A);
  sound("mi",0,4,bpm,A);
  sound("re",0,4,bpm,A);
  sound("do",0,4,bpm,A);
  zero("do",0,4,bpm,A);
  */


  //カノン
  iso=0;
  dn=0;
  double bpm=60;
  int sm=6000;
  int bg=8000;
  int A=8000;
  int n=atoi(argv[1]);//パート0,1,2,3

  if(n==0){
  //伴奏
  roop(13){
  sound("re",0,4,bpm,A);
  sound("ra",-1,4,bpm,A);
  sound("si",-1,4,bpm,A);
  sound("fa#",-1,4,bpm,A);
  sound("so",-1,4,bpm,A);
  sound("re",-1,4,bpm,A);
  sound("so",-1,4,bpm,A);
  sound("ra",-1,4,bpm,A);
  }
  sound("re",0,1,bpm,A);
  zero("re",0,8,bpm,A);
  }

  else{
  A=sm;
  roop(n*2){zero("do",0,1,bpm,0);}
  sound("fa#",1,4,bpm,A);
  sound("mi",1,4,bpm,A);
  sound("re",1,4,bpm,A);
  sound("do#",1,4,bpm,A);
  sound("si",0,4,bpm,A);
  sound("ra",0,4,bpm,A);
  sound("si",0,4,bpm,A);
  sound("do#",1,4,bpm,A);

  sound("re",1,4,bpm,A);
  sound("do#",1,4,bpm,A);
  sound("si",0,4,bpm,A);
  sound("ra",0,4,bpm,A);
  sound("so",0,4,bpm,A);
  sound("fa#",0,4,bpm,A);
  sound("so",0,4,bpm,A);
  sound("mi",0,4,bpm,A);

  sound("re",0,8,bpm,A);
  sound("fa#",0,8,bpm,A);
  sound("ra",0,8,bpm,A);
  sound("so",0,8,bpm,A);
  sound("fa#",0,8,bpm,A);
  sound("re",0,8,bpm,A);
  sound("fa#",0,8,bpm,A);
  sound("mi",0,8,bpm,A);
  sound("re",0,8,bpm,A);
  sound("si",-1,8,bpm,A);
  sound("re",0,8,bpm,A);
  sound("ra",0,8,bpm,A);
  sound("so",0,8,bpm,A);
  sound("si",0,8,bpm,A);
  sound("ra",0,8,bpm,A);
  sound("so",0,8,bpm,A);

  sound("fa#",0,8,bpm,A);
  sound("re",0,8,bpm,A);
  sound("mi",0,8,bpm,A);
  sound("do#",1,8,bpm,A);
  sound("re",1,8,bpm,A);
  sound("fa#",1,8,bpm,A);
  sound("ra",1,8,bpm,A);
  sound("ra",0,8,bpm,A);
  sound("si",0,8,bpm,A);
  sound("so",0,8,bpm,A);
  sound("ra",0,8,bpm,A);
  sound("fa#",0,8,bpm,A);
  sound("re",0,8,bpm,A);
  roop(5){sound("re",1,16,bpm,A);}
  sound("do#",1,16,bpm,A);

  A=bg;
  soundc("re",1,16,bpm,sm,bg);
  sound("do#",1,16,bpm,A);
  sound("re",1,16,bpm,A);
  sound("re",0,16,bpm,A);
  sound("do#",0,16,bpm,A);
  sound("ra",0,16,bpm,A);
  sound("mi",0,16,bpm,A);
  sound("fa#",0,16,bpm,A);
  sound("re",0,16,bpm,A);
  sound("re",1,16,bpm,A);
  sound("do#",1,16,bpm,A);
  sound("si",0,16,bpm,A);
  sound("do#",1,16,bpm,A);
  sound("fa#",1,16,bpm,A);
  sound("ra",1,16,bpm,A);
  sound("si",1,16,bpm,A);
  sound("so",1,16,bpm,A);
  sound("fa#",1,16,bpm,A);
  sound("mi",1,16,bpm,A);
  sound("so",1,16,bpm,A);
  sound("fa#",1,16,bpm,A);
  sound("mi",1,16,bpm,A);
  sound("re",1,16,bpm,A);
  sound("do#",1,16,bpm,A);
  sound("si",0,16,bpm,A);
  sound("ra",0,16,bpm,A);
  sound("so",0,16,bpm,A);
  sound("fa#",0,16,bpm,A);
  sound("mi",0,16,bpm,A);
  sound("so",0,16,bpm,A);
  sound("fa#",0,16,bpm,A);
  sound("mi",0,16,bpm,A);

  A=sm;
  soundc("re",0,16,bpm,bg,sm);
  sound("mi",0,16,bpm,A);
  sound("fa#",0,16,bpm,A);
  sound("so",0,16,bpm,A);
  sound("ra",0,16,bpm,A);
  sound("mi",0,16,bpm,A);
  sound("ra",0,16,bpm,A);
  sound("so",0,16,bpm,A);
  sound("fa#",0,16,bpm,A);
  sound("si",0,16,bpm,A);
  sound("ra",0,16,bpm,A);
  sound("so",0,16,bpm,A);
  sound("ra",0,16,bpm,A);
  sound("so",0,16,bpm,A);
  sound("fa#",0,16,bpm,A);
  sound("mi",0,16,bpm,A);
  sound("re",0,16,bpm,A);
  sound("si",-1,16,bpm,A);
  sound("si",0,16,bpm,A);
  sound("do#",1,16,bpm,A);
  sound("re",1,16,bpm,A);
  sound("do#",1,16,bpm,A);
  sound("si",0,16,bpm,A);
  sound("ra",0,16,bpm,A);
  sound("so",0,16,bpm,A);
  sound("fa#",0,16,bpm,A);
  sound("mi",0,16,bpm,A);
  sound("si",0,16,bpm,A);
  sound("ra",0,16,bpm,A);
  sound("si",0,16,bpm,A);
  sound("ra",0,16,bpm,A);
  sound("so",0,16,bpm,A);

  sound("fa#",0,8,bpm,A);
  A=bg;
  soundc("fa#",1,8,bpm,sm,bg);
  sound("mi",1,4,bpm,A);
  zero("mi",1,8,bpm,A);
  sound("re",1,8,bpm,A);
  sound("fa#",1,4,bpm,A);
  sound("si",1,4,bpm,A);
  sound("ra",1,4,bpm,A);
  sound("si",1,4,bpm,A);
  sound("do#",2,4,bpm,A);

  sound("re",2,8,bpm,A);
  sound("re",1,8,bpm,A);
  sound("do#",1,4,bpm,A);
  zero("do#",1,8,bpm,A);
  A=sm;
  sound("si",0,8,bpm,A);
  roop(11){sound("re",1,48,bpm,A);}
  zero("re",1,48,bpm,A);
  roop(17){sound("re",1,48,bpm,A);}
  zero("re",1,48,bpm,A);
  roop(5){sound("re",1,48,bpm,A);}
  zero("re",1,48,bpm,A);
  sound("re",1,8,bpm,A);
  sound("so",1,8,bpm,A);
  sound("mi",1,8,bpm,A);
  sound("ra",1,8,bpm,A);

  A=bg;
  soundc("ra",1,16,bpm,sm,bg);
  sound("fa#",1,32,bpm,A);
  sound("so",1,32,bpm,A);
  sound("ra",1,16,bpm,A);
  sound("fa#",1,32,bpm,A);
  sound("so",1,32,bpm,A);
  sound("ra",1,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("si",0,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("mi",1,32,bpm,A);
  sound("fa#",1,32,bpm,A);
  sound("so",1,32,bpm,A);
  sound("fa#",1,16,bpm,A);
  sound("re",1,32,bpm,A);
  sound("mi",1,32,bpm,A);
  sound("fa#",1,16,bpm,A);
  sound("fa#",0,32,bpm,A);
  sound("so",0,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("si",0,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("so",0,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("fa#",0,32,bpm,A);
  sound("so",0,32,bpm,A);
  sound("ra",0,32,bpm,A);

  sound("so",0,16,bpm,A);
  sound("si",0,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("so",0,16,bpm,A);
  sound("fa#",0,32,bpm,A);
  sound("mi",0,32,bpm,A);
  sound("fa#",0,32,bpm,A);
  sound("mi",0,32,bpm,A);
  sound("re",0,32,bpm,A);
  sound("mi",0,32,bpm,A);
  sound("fa#",0,32,bpm,A);
  sound("so",0,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("si",0,32,bpm,A);
  sound("so",0,16,bpm,A);
  sound("si",0,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("si",0,16,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("si",0,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("mi",1,32,bpm,A);
  sound("fa#",1,32,bpm,A);
  sound("so",1,32,bpm,A);
  sound("ra",1,32,bpm,A);

  sound("fa#",1,16,bpm,A);
  sound("re",1,32,bpm,A);
  sound("mi",1,32,bpm,A);
  sound("fa#",1,16,bpm,A);
  sound("mi",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("mi",1,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("mi",1,32,bpm,A);
  sound("fa#",1,32,bpm,A);
  sound("mi",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,16,bpm,A);
  sound("si",0,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,16,bpm,A);
  sound("re",0,32,bpm,A);
  sound("mi",0,32,bpm,A);
  sound("fa#",0,32,bpm,A);
  sound("so",0,32,bpm,A);
  sound("fa#",0,32,bpm,A);
  sound("mi",0,32,bpm,A);
  sound("fa#",0,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,32,bpm,A);

  sound("si",0,16,bpm,A);
  sound("re",1,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("si",0,16,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("so",0,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("so",0,32,bpm,A);
  sound("fa#",0,32,bpm,A);
  sound("so",0,32,bpm,A);
  sound("ra",0,32,bpm,A);
  sound("si",0,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("si",0,16,bpm,A);
  sound("re",1,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,16,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("si",0,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("mi",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("do#",1,32,bpm,A);
  sound("re",1,32,bpm,A);
  sound("si",0,32,bpm,A);
  sound("do#",1,32,bpm,A);

  if(n==1||n==2){
  A=sm;
  soundc("re",1,8,bpm,bg,sm);
  zero("re",1,8,bpm,A);
  sound("do#",1,8,bpm,A);
  zero("do#",1,8,bpm,A);
  sound("si",0,8,bpm,A);
  zero("si",0,8,bpm,A);
  sound("re",1,8,bpm,A);
  zero("re",1,8,bpm,A);
  roop(4){sound("re",0,8,bpm,A);
            zero("re",0,8,bpm,A);}
  }
  if(n==1){
  A=4000;
  zero("ra",0,8,bpm,0);
  sound("ra",0,8,bpm,A);
  zero("ra",0,8,bpm,A);
  sound("ra",0,8,bpm,A);
  zero("ra",0,8,bpm,A);
  sound("fa#",0,8,bpm,A);
  zero("fa#",0,8,bpm,A);
  sound("ra",0,8,bpm,A);
  zero("ra",0,8,bpm,A);
  sound("so",0,8,bpm,A);
  zero("so",0,8,bpm,A);
  sound("fa#",0,8,bpm,A);
  zero("fa#",0,8,bpm,A);
  sound("so",0,8,bpm,A);
  zero("so",0,8,bpm,A);
  sound("mi",1,8,bpm,A);
  }
  if(n==1){
  soundc("fa#",0,1,bpm,A,sm);
  zero("fa#",0,8,bpm,sm);
  }
  else if(n==2){
  soundc("ra",0,1,bpm,A,sm);
  zero("ra",0,8,bpm,sm);
  }
  else if(n==3){
  soundc("re",1,1,bpm,A,sm);
  zero("re",1,8,bpm,sm);
  }
  }
  return 0;
}