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
SortedSet newSortedSet(int (* compar)(void*,void*));


// FREE
/**
 * Free the memory allocated from the SortedSet.
 */
void deleteSortedSet(SortedSet* l);

// GETTERS

/**
 * Test if the SortedSet contains the key
 */
int containsSortedSet(SortedSet l, void* element);
 
/**
 * Get SortedSet's length
 */
size_t lengthSortedSet(SortedSet l);

/**
 * Get element in SortedSet
 */
void* getSortedSet(SortedSet l, void* element);

// SETTERS

/**
 * Insert element in SortedSet
 */
void insertSortedSet(SortedSet l, void* element);

/**
 * Remove element in SortedSet
 */
void* removeSortedSet(SortedSet l, void* element);

/**
 * Clear SortedSet
 */
void clearSortedSet(SortedSet l);

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorSortedSet(SortedSet l);

/**
 * Test if there is a next element
 */
int hasNextSortedSet(SortedSet l);

/**
 * Return the next element
 */
void* nextSortedSet(SortedSet l);

#endif // SORTED_SET_H
