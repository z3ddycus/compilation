#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/**
 * Generic List type, can support NULL element.
 */
typedef struct _set *List;

// CONSTRUCTOR

/**
 * Create and allocate a new empty List.
 */
List newList(int (* compar)(void*,void*));


// FREE
/**
 * Free the memory allocated from the List.
 */
void deleteList(List* l);

// GETTERS

/**
 * Test if the List contains the element.
 */
int containsList(List l, void* element);

/**
 * Get List's length
 */
size_t lengthList(List l);

/**
 * Get element in List
 */
void* getList(List l, void* element);

// SETTERS

/**
 * Insert element in List
 */
void insertList(List l, void* element);

/**
 * Remove element in List
 */
void* removeList(List l, void* element);

/**
 * Clear List
 */
void clearList(List l);

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorList(List l);

/**
 * Test if there is a next element
 */
int hasNextList(List l);

/**
 * Return the next element
 */
void* nextList(List l);

#endif // LIST_H
