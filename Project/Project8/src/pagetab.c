#include "pagetab.h"

int handle_pagefault(int page_number) {
	int frame_number = read_frame(page_number);
	int fault = frame_number < 0;
	frame_number = fault ? -frame_number - 1 : frame_number;

	if (fault) {
		// in-valid the original page_number
		int original_page_number = 0;
		for (; original_page_number < PAGETABLESIZE &&
			!(page_table[original_page_number][1] && 
				page_table[original_page_number][0]==frame_number);
			++original_page_number);
		page_table[original_page_number][1] = 0;
	}

	page_table[page_number][0] = frame_number;
	page_table[page_number][1] = 1;
	return fault;
}