#ifndef PAGETAB
#define PAGETAB 1

#include "memory.h"

#define PAGETABLESIZE 256

// [FN][0] Frame Number
// [FN][1] Valid Byte:
//		1 - valid
//		0 - invalid

int page_table[PAGETABLESIZE][2];

// return 1 if there is a page replacement
int handle_pagefault(int page_number);

#endif