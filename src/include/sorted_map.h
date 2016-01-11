#ifndef SORTED_MAP_H
#define SORTED_MAP_H

#include <stdlib.h>

#define GET_ERR 0

/**
 * Generic SortedMap type, can support NULL element.
 */
typedef struct _Map *SortedMap;

// CONSTRUCTOR

/**
 * Create and allocate a new empty SortieMap.
 */
SortedMap newMap(int (* compar)(void*,void*));


// FREE
/**
 * Free the memory allocated from the SortedMap.
 */
void deleteMap(SortedMap* l);

// GETTERS

/**
 * Test if the SortedMap contains the key
 */
int containsMap(SortedMap l, void* key); 
 
/**
 * Get SortedMap's length
 */
size_t lengthMap(SortedMap l);

/**
 * Get element in SortedMap
 */
void* getMap(SortedMap l, void* key);

// SETTERS

/**
 * Insert element in SortedMap
 */
void insertMap(SortedMap l, void* key, void* value);

/**
 * Remove element in SortedMap
 */
void* removeMap(SortedMap l, void* key);

/**
 * Clear SortedMap
 */
void clearMap(SortedMap l);

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorMap(SortedMap l);

/**
 * Test if there is a next element
 */
int hasNextMap(SortedMap l);

/**
 * Return the next element
 */
void* nextMap(SortedMap l);
#endif // SORTED_MAP_H
