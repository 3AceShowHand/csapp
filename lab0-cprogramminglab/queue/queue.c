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
	    } else
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
		item->next = q->last->next;
		q->last->next = item;
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

	}
}

void q_free(queue_t *q)
{
	if (q == NULL || q->head->next == q->last)
	{
		return;
	}
	list_elem_t *current = q->head->next;
	q->head->next = q->last;

	list_elem_t *target = NULL;
	while (current != q->last)
	{
		target = current;
		current = current->next;
		free(target);
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
	if (q == NULL || q->head == NULL)
	{
		return;
	}
	else
	{
		list_elem_t *items = q->head->next;
		q->head->next = q->last;

		list_elem_t *target = NULL;
		while (items != q->last)
		{
			target = items;
			items = items->next;

			target->next = q->head->next;

			q->head->next = target;
		}
	}
}

int main()
{
	queue_t *q = q_new();
	int *vp = malloc(sizeof(int));

	if (q_remove_head(q, vp))
	{
		printf("remove success, the value is: %d\n", *vp);
	}
	else
	{
		printf("remove failed\n");
	}

	q_insert_head(q, 5);
	q_insert_head(q, 4);

	q_insert_tail(q, 6);
	q_insert_tail(q, 1);
	list_elem_t *cursor = q->head->next;
	while (cursor != q->last)
	{
		printf("%d ", cursor->value);
		cursor = cursor->next;
	}
	printf("\n");

	printf("the size of list is: %d\n", q->size);

	q_remove_head(q, vp);
	printf("the removed head value is %d\n", *vp);
	printf("current size of list is: %d\n", q->size);

	q_reverse(q);
	cursor = q->head->next;
	while (cursor != q->last)
	{
		printf("%d ", cursor->value);
		cursor = cursor->next;
	}
	printf("\n");

	q_free(q);

	return 0;
}
