#ifndef FFTFUNC_H
#define FFTFUNC_H

typedef short sample_t;
void die(char * s);
ssize_t read_n(int fd, ssize_t n, void * buf);
ssize_t write_n(int fd, ssize_t n, void * buf);
void sample_to_complex(sample_t * s, complex float * X, long n);
void complex_to_sample(complex float * X, sample_t * s, long n);
void fft_r(complex float * x,complex float * y,long n,complex double w);
void fft(complex float * x, 
	 complex float * y, 
	 long n);
void ifft(complex float * y, 
	 complex float * x, 
	 long n);
int pow2check(long N);
int cut_data(complex float * Y,complex float * newY,unsigned char* memo, long n);
void remake_data(complex float * Y,complex float * newY,unsigned char* memo, long n);
#endif