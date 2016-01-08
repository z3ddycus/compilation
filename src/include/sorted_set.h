#ifndef SORTED_SET_H
#define SORTED_SET_H

#include <stdlib.h>

#define GET_ERR 0

/**
 * Generic SortedSet type, can support NULL element.
 */
typedef struct _set *SortedSet;

// CONSTRUCTOR

/**
 * Create and allocate a new empty SortieSet.
 */
SortedSet newSet(int (* compar)(void*,void*));


// FREE
/**
 * Free the memory allocated from the SortedSet.
 */
void deleteSet(SortedSet* l);

// GETTERS

/**
 * Test if the SortedSet contains the key
 */
int containsSet(SortedSet l, void* element); 
 
/**
 * Get SortedSet's length
 */
size_t lengthSet(SortedSet l);

/**
 * Get element in SortedSet
 */
void* getSet(SortedSet l, void* element);

// SETTERS

/**
 * Insert element in SortedSet
 */
void insertSet(SortedSet l, void* element);

/**
 * Remove element in SortedSet
 */
void* removeSet(SortedSet l, void* element);

/**
 * Clear SortedSet
 */
void clearSet(SortedSet l);

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorMap(SortedSet l);

/**
 * Test if there is a next element
 */
int hasNext(SortedSet l);

/**
 * Return the next element
 */
void* next(SortedSet l);

#endif // SORTED_SET_H
