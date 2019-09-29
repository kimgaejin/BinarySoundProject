#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define PCM 1

typedef unsigned char byte;

// wave 헤더
typedef struct riff
{
	unsigned char chunkID[4];
	unsigned int chunkSize;
	unsigned char format[4];
} Riff;

typedef struct fmt
{
	unsigned char chunkID[4];
	unsigned int chunkSize;
	unsigned short audioFormat;
	unsigned short numberChannel;
	unsigned int sampleRate;
	unsigned int avgByteRate;
	unsigned short blockAlign;
	unsigned short bitPerSample;
} fmt;

typedef struct data
{
	char chunkID[4];
	unsigned int chunkSize;
} Data;

typedef struct waveHeader
{
	Riff riff;
	fmt fmt;
	Data data;
} WaveHeader;

// main 함수 ============================

int main()
{
	FILE *f_out = NULL;

	WaveHeader header;

	f_out = fopen("out.wav", "w");
	if (!f_out)
	{
		printf("\nerror: couldn't find out.wav");
		return -1;
	}

	strncpy(header.riff.chunkID, "RIFF", 4);
	
	const int DURATION = 10;
	const int SAMPLE_RATE = 44100;
	const int CHANNEL = 1;
	const int BIT_RATE = 32;

	header.riff.chunkSize = DURATION * SAMPLE_RATE * CHANNEL * BIT_RATE / 8 + 36;
	// duration * sampleRate * channel * bitRate / bite 단위 + 남은 헤더 용량

	strncpy(header.riff.format, "WAVE", 4);

	strncpy(header.fmt.chunkID, "fmt ", 4);

	header.fmt.chunkSize = 0x10;
	header.fmt.audioFormat = PCM;
	header.fmt.numberChannel = CHANNEL;
	header.fmt.sampleRate = SAMPLE_RATE;
	header.fmt.avgByteRate = SAMPLE_RATE * CHANNEL * BIT_RATE / 8;
	header.fmt.blockAlign = CHANNEL * BIT_RATE / 8; 
	header.fmt.bitPerSample = BIT_RATE;

	strncpy(header.data.chunkID, "data", 4);

	header.data.chunkSize = DURATION * SAMPLE_RATE * CHANNEL * BIT_RATE / 8; 

	fwrite(&header, sizeof(header), 1, f_out); 
	short y[1]; 
	double freq = 1000; 

	printf("디");
	for (int i = 0; i < SAMPLE_RATE * DURATION * CHANNEL * BIT_RATE / 8; i++) {
		y[0] = (short)30000 * sin(2 * 3.141592 * i * freq / SAMPLE_RATE); 
		fwrite(&y[0], sizeof(short), 1, f_out); 
	}

	fclose(f_out);

	return 0;
}