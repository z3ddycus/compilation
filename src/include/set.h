#ifndef SET_H
#define SET_H

#include <stdlib.h>

/**
 * Generic Set type, can support NULL element.
 */
typedef struct _set *Set;

// CONSTRUCTOR

/**
 * Create and allocate a new empty Set.
 */
Set newSet(int (* compar)(void*,void*));


// FREE
/**
 * Free the memory allocated from the Set.
 */
void deleteSet(Set* l);

// GETTERS

/**
 * Test if the Set contains the element.
 */
int containsSet(Set l, void* element);

/**
 * Get Set's length
 */
size_t lengthSet(Set l);

/**
 * Get element in Set
 */
void* getSet(Set l, void* element);

// SETTERS

/**
 * Insert element in Set
 */
void insertSet(Set l, void* element);

/**
 * Remove element in Set
 */
void* removeSet(Set l, void* element);

/**
 * Clear Set
 */
void clearSet(Set l);

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorSet(Set l);

/**
 * Test if there is a next element
 */
int hasNextSet(Set l);

/**
 * Return the next element
 */
void* nextSet(Set l);

#endif // SET_H
