#include "memory.h"

#define PAGETABLESIZE 256

// [FN][0] Frame Number
// [FN][1] Valid Byte:
//		1 - valid
//		0 - invalid

int page_table[PAGETABLESIZE][2];

void handle_pagefault(int page_number);