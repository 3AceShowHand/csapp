#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

queue_t *q_new()
{
	queue_t *q = malloc(sizeof(queue_t));
	if (q == NULL)
	{
		return NULL;
	}
	q->head = NULL;
	q->last = NULL;
    q->size = 0;
	return q;
}

bool q_insert_head(queue_t *q, int v)
{
	if (q == NULL)
	{
		return false;
	} else {
	    list_ele_t* item = malloc(sizeof(list_ele_t));
	    if (item == NULL) {
	        return false;
	    }
	    item->value = v;
	    item->next = q->head;
	    if (q->head == NULL) {
	    	q->last = item;
	    }
	    q->head = item;
	    q->size += 1;

        return true;
	}
}

bool q_insert_tail(queue_t *q, int v)
{
	if (q == NULL)
	{
		return false;
	} else {
		list_ele_t* item = malloc(sizeof(list_ele_t));
		if (item == NULL) {
			return false;
		}
		item->value = v;
		item->next = NULL;
		if (q->head == NULL) {
			q->head = item;
		} else {
			q->last->next = item;
		}
		q->last = item;
		q->size += 1;
		return true;
	}
}

bool q_remove_head(queue_t *q, int *vp)
{
	if (q == NULL || q->head == NULL)
	{
		return false;
	} else {
		list_ele_t* target = q->head;
		*vp = target->value;

		q->head = target->next;
		q->size -= 1;

		free(target);

		return true;
	}
}

void q_free(queue_t *q)
{
	if (q == NULL || q->head == NULL) {
		return ;
	} else {
		q->last = q->head;
		list_ele_t* current = q->head;
		while (current != NULL) {
			q->head = current->next;
			free(current);
			q->size -= 1;
			current = q->head;
		}
	}
	free(q);
}

int q_size(queue_t *q)
{
	if (q == NULL || q->head == NULL)
	{
		return 0;
	}
	else
	{
		return q->size;
	}
}

void q_reverse(queue_t *q)
{
	if (q == NULL || q->head == NULL) {
		return;
	} else {
		list_ele_t* items = q->head->next;
		q->last = q->head;

		list_ele_t* current = NULL;
		while (items != NULL) {
			current = items;
			items = items->next;
			current->next = q->head;
			q->head = current;
		}
		q->last->next = NULL;
	}
}

int main()
{
	queue_t *q = q_new();
	q_insert_head(q, 2);
	q_insert_head(q, 1);
	q_insert_head(q, 3);
	q_insert_tail(q, 5);
	q_insert_tail(q, 1);

	q_reverse(q);

	for (list_ele_t* cursor = q->head; cursor != NULL; cursor = cursor->next) {
		printf("%d ", cursor->value);
	}

	return 0;
}
