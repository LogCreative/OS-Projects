#ifndef LRU
#define LRU 1

#include <stdlib.h>

struct used_node {
	int page_number;
	struct used_node* prev;
	struct used_node* next;
};

void search_pop(struct used_node** head, struct used_node** tail, int page_number);

void push(struct used_node** head, struct used_node** tail, int page_number);

int bottom_pop(struct used_node** head, struct used_node** tail);

#endif