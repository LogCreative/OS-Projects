#include "memory.h"

static struct used_node* mem_head = NULL;
static struct used_node* mem_tail = NULL;

int read_frame(int page_number) {
	static int frame_number = 0;

	FILE* backstore;
	if ((backstore = fopen("BACKING_STORE.bin", "rb")) == NULL) {
		fprintf(stderr, "Empty file storage!\n");
		return -1;
	}

	int fault = frame_number >= MEMSIZE;

	int frame_number_ = fault ? MEMSIZE : frame_number++;
	
	if (fault)	// Page Replacement
		frame_number_ = bottom_pop(&mem_head, &mem_tail);

	long pos = page_number * FRAMESIZE;
	fseek(backstore, pos, SEEK_SET);
	fread(mem[frame_number_], sizeof(char), FRAMESIZE, backstore);
	fclose(backstore);

	return fault ? -frame_number_-1 : frame_number_;
}

int get_value(add _phyadd) {
	int frame_number = _phyadd.number;
	search_pop(&mem_head, &mem_tail, frame_number);
	push(&mem_head, &mem_tail, frame_number);
	return mem[frame_number][_phyadd.offset];
}