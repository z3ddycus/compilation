#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>

#define GET_ERR 0

#define SET 1
#define LIST 0

/**
 * Generic SortedList type, can support NULL element.
 */
typedef struct _list *SortedList;

// CONSTRUCTOR

/**
 * Create and allocate a new empty SortieList.
 */
SortedList newList(int * (*compar)(void*,void*), int isSet);


// FREE
/**
 * Free the memory allocated from the SortedList.
 */
void deleteList(SortedList* l);

// GETTERS

/**
 * Test if the SortedList contains the key
 */
int containsList(SortedList l, void* key); 
 
/**
 * Get SortedList's length
 */
size_t lengthList(SortedList l);

/**
 * Get element in SortedList
 */
void* getList(SortedList l, void* key);

// SETTERS

/**
 * Insert element in SortedList
 */
void insertList(SortedList l, void* key, void* value);

/**
 * Remove element in SortedList
 */
void removeList(SortedList l, void* key);

/**
 * Clear SortedList
 */
void clearList(SortedList l);

#endif // SORTED_LIST_H
