#ifndef MEMORY
#define MEMORY 1

#include <stdio.h>

#define MEMSIZE 256
#define FRAMESIZE 256

char mem[MEMSIZE][FRAMESIZE];

int read_frame(int page_number);

#endif