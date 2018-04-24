/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
	if (q == NULL) {
		return NULL;
	}
    q->head = NULL;
    q->last = q->head;
    q->size = 0;
    return q;

}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
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
        q->head = item;
        q->size += 1;
        return true;
    }
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
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

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL) {
        return false;
    } else if (vp == NULL) {
        return false;
    } else {
        list_ele_t* target = q->head;
        vp = target->value;

        q->head = target->next;
        q->size -= 1;
        free(target);
        return true;
    }
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    } else {
        list_ele_t* current = q->head;
        list_ele_t* target = NULL;
        while(current != NULL) {
            target = current;
            current = current->next;
            free(target);
        }
        free(q);
    }
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
	if (q == NULL || q->head == NULL) {
	    return 0;
	} else {
	    return q->size;
	}
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL) {
        return;
    } else {
        list_ele_t* items = q->head;
        q->head = NULL;

        list_ele_t* current = items;
        while (current != NULL) {
            items = items->next;
            current->next = q->head;
            q->head = current;
            current = items;
        }

    }
}
