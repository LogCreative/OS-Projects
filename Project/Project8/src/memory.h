#ifndef MEMORY
#define MEMORY 1

#include <stdio.h>
#include "lru.h"
#include "addext.h"

#define MEMSIZE 128
#define FRAMESIZE 256

char mem[MEMSIZE][FRAMESIZE];

// a negative number means there is a fault.
int read_frame(int page_number);
int get_value(add _phyadd);

#endif