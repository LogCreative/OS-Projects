#ifndef TLB_GUARD
#define TLB_GUARD 1

#include "pagetab.h"
#include "lru.h"

#define TLBSIZE 16

// TLB[i][2] - isOccupied:
//		0 - empty
//		1 - occupied
int TLB[TLBSIZE][3];

int tlb_search(int page_number);

#endif // !TLB_GUARD