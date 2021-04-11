#include "lru.h"

void search_pop(struct used_node** head, struct used_node** tail, int page_number) {
	struct used_node* tmp = *head;
	while (tmp && tmp->page_number != page_number)
		tmp = tmp->next;
	if (!tmp) return;		// If nothing is found, then do nothing.
	if (*head == *tail) {
		*head = *tail = NULL;
		return;
	}
	if (tmp == *head) {
		tmp->next->prev = tmp->prev;
		*head = tmp->next;
	}
	else if (tmp == *tail) {
		tmp->prev->next = tmp->next;
		*tail = tmp->prev;
	}
	else {
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
	}
	free(tmp);
}

void push(struct used_node** head, struct used_node** tail, int page_number) {
	struct used_node* new_node = (struct used_node*)malloc(sizeof(struct used_node));
	new_node->page_number = page_number;
	new_node->prev = NULL;
	new_node->next = NULL;

	if (!*head) {
		*head = *tail = new_node;
		return;
	}

	new_node->next = *head;
	(*head)->prev = new_node;
	*head = new_node;
}

int bottom_pop(struct used_node** head, struct used_node** tail) {
	if (!*tail) return -1;
	
	int bottom = (*tail)->page_number;
	if (*head == *tail) {	
		*head = *tail = NULL;
		return bottom;
	}

	*tail = (*tail)->prev;
	free((*tail)->next);
	(*tail)->next = NULL;
	return bottom;
}
