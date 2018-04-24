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

#include <stdbool.h>

/************** Data structure declarations ****************/

/* Linked list element (You shouldn't need to change this) */
typedef struct ELE
{
  int value;
  struct ELE *next;
} list_ele_t;

/* Queue structure */
typedef struct
{
  list_ele_t *head; /* Linked list of elements */
  /*
      You will need to add more fields to this structure
      to efficiently implement q_size and q_insert_tail
    */
<<<<<<< HEAD
  int size;         /* count for queue size*/
  list_ele_t *last; /* trace the last position */
=======
  int size; /* count for queue size*/
  list_ele_t* current;
>>>>>>> bb93f7229ec317bc9bf1e842d33f61d11e3c51b2
} queue_t;

/************** Operations on queue ************************/

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new();

/*
  Free all storage used by queue.
  No effect if q is NULL
*/
void q_free(queue_t *q);

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v);

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v);

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp);

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q);

/*
  Reverse elements in queue
  No effect if q is NULL or empty
 */
void q_reverse(queue_t *q);
