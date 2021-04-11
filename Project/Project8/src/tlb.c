#include "tlb.h"

int all_number = 0;
int page_fault_number = 0;
int tlb_hit_number = 0;

int tlb_search(int page_number) {
	static struct used_node* tlb_head = NULL;
	static struct used_node* tlb_tail = NULL;

	++all_number;

	int result = -1;
	for (int i = 0; i < TLBSIZE; ++i) {
		if (TLB[i][2]			// is occupied 
			&& TLB[i][0] == page_number) {
			result = i;
			break;
		}
	}
	if (result >= 0) {			// TLB hit 
		search_pop(&tlb_head, &tlb_tail, page_number);
		push(&tlb_head, &tlb_tail, page_number);
		++tlb_hit_number;
		return TLB[result][1];	
	}
	else {						// TLB miss

		if (!page_table[page_number][1]) { // page fault
			if (handle_pagefault(page_number)) {	// page replacement
				int frame_number_r = page_table[page_number][0];
				for (int i = 0; i < TLBSIZE; ++i)
					if (TLB[i][2]
						&& TLB[i][1] == frame_number_r)
						TLB[i][2] = 0;
			}
			++page_fault_number;
		}

		int frame_number = page_table[page_number][0];

		int hole = -1;

		for (int i = 0; i < TLBSIZE; ++i)
			if (!TLB[i][2])	{	// is empty
				hole = i;
				break;
			}

		if (hole >= 0) {
			TLB[hole][0] = page_number;
			TLB[hole][1] = frame_number;
			TLB[hole][2] = 1;
			push(&tlb_head, &tlb_tail, page_number);
		} else {				// full TLB
			// LRU Algorithm
			int least_used = bottom_pop(&tlb_head, &tlb_tail);
			int least_used_index = 0;
			for (; TLB[least_used_index][0] != least_used; ++least_used_index);
			TLB[least_used_index][0] = page_number;
			TLB[least_used_index][1] = frame_number;
			push(&tlb_head, &tlb_tail, page_number);
		}

		return frame_number;
	}
}

double get_pagefault_rate() { return (double)page_fault_number / all_number; }
double get_tlbhit_rate() { return (double)tlb_hit_number / all_number; }