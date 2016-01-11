#ifndef REF_MANAGER_H
#define REF_MANAGER_H

#include <stdlib.h>
#include "reference.h"

typedef struct _ref_manager* RefManager;

/**
 * Return a new hashmap allocated and initialized empty.
 */
RefManager newRefManager();

/**
 * Free the memory allocated to the hashmap.
 */
void deleteRefManager(RefManager* manager);

// GETTER

/**
 * Test if the map contains the key
 */
int containsRefManager(RefManager manager, char* id);

/**
 * Return the value of the key
 */
Reference getRefManager(RefManager manager, char* id);

/**
 * Return the size of the map
 */
size_t sizeRefManager(RefManager manager);

// SETTERS

/**
 * Set or replace the value for the key
 */
void setRefManager(RefManager manager, Reference ref);

/**
 * Remove the key.
 */
Reference removeRefManager(RefManager manager, char* id);

/**
 * Clear the map
 */
void clearRefManager(RefManager manager);

/**
 * Serialize the manager
 */
void referenceToBibtex(RefManager manager, FILE* f);

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorRefManager(RefManager manager);

/**
 * Test if there is a next element
 */
int hasNextRefManager(RefManager manager);

/**
 * Return the next element
 */
Reference nextRefManager(RefManager manager);

#endif
