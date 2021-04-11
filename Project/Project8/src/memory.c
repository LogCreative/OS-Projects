#include "memory.h"

int read_frame(int page_number) {
	static int frame_number = 0;

	FILE* backstore;
	if ((backstore = fopen("BACKING_STORE.bin", "rb")) == NULL) {
		fprintf(stderr, "Empty file storage!\n");
		return -1;
	}

	int frame_number_ = frame_number++;
	long pos = page_number * FRAMESIZE;
	fseek(backstore, pos, SEEK_SET);
	fread(mem[frame_number_], sizeof(char), FRAMESIZE, backstore);
	fclose(backstore);

	return frame_number_;
}