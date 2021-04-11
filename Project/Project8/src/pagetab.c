#include "pagetab.h"

void handle_pagefault(int page_number) {
	int frame_number = read_frame(page_number);
	page_table[page_number][0] = frame_number;
	page_table[page_number][1] = 1;
}