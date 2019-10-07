#include<stdio.h>

#define FRAMESIZE 1024

int main(int argc, char* argv[])
{
	 FILE *fin;
	 FILE *fout;

	 short data[FRAMESIZE];

	 fin = fopen("stereo.wav","rb");
	 fout= fopen("output.wav","wb");

	 while( ! feof(fin) )
	 {
		 fread(data,sizeof(short),FRAMESIZE,fin);
		 fwrite(data,sizeof(short),FRAMESIZE,fout);
	 }
	 fcloseall();
	 printf("complete");
	 
	 return 0;
} 
