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
    if (q == NULL)
    {
        return NULL;
    }
    q->head = malloc(sizeof(list_ele_t));
    q->last = malloc(sizeof(list_ele_t));
    q->head->next = q->last;
    q->size = 0;

    return q;
}

/* Free all storage used by queue */

void q_free(queue_t *q)
{
    if (q == NULL || q->head->next == q->last)
    {
        return;
    }
    list_ele_t *current = q->head->next;
    q->head->next = q->last;

    list_ele_t *target = NULL;
    while (current != q->last)
    {
        target = current;
        current = current->next;
        free(target);
    }
    free(q);

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
    }
    else
    {
        list_ele_t *item = malloc(sizeof(list_ele_t));
        if (item == NULL)
        {
            return false;
        }
        item->value = v;
        item->next = q->head->next;
        q->head->next = item;
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
    if (q == NULL)
    {
        return false;
    }
    else
    {
        list_ele_t *item = malloc(sizeof(list_ele_t));
        if (item == NULL)
        {
            return false;
        }
        q->last->value = v;
        q->last->next = item;
        item->next = NULL;
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
    if (q == NULL || q->head->next == q->last)
    {
        return false;
    }
    else
    {
        list_ele_t *target = q->head->next;
        *vp = target->value;
        q->head->next = target->next;
        q->size -= 1;
        free(target);

        return true;
    }
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */

int q_size(queue_t *q)
{
    if (q == NULL || q->head->next == q->last)
    {
        return 0;
    }
    else
    {
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
    if (q == NULL || q->head == NULL)
    {
        return;
    }
    else
    {
        list_ele_t *items = q->head->next;
        q->head->next = q->last;

        list_ele_t *target = NULL;
        while (items != q->last)
        {
            target = items;
            items = items->next;

            target->next = q->head->next;

            q->head->next = target;
        }
    }
}