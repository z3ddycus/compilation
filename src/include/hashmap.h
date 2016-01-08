#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>

typedef struct _hashmap* HashMap;

/**
 * Return a new hashmap allocated and initialized empty.
 */
HashMap newHashMap(size_t (*hash) (void*), int (*compar) (void*, void*));

/**
 * Free the memory allocated to the hashmap.
 */
void deleteHashMap(HashMap* map);

// GETTER

/**
 * Test if the map contains the key
 */
int containsHashMap(HashMap map, void* key);

/**
 * Return the value of the key
 */
void* getHashMap(HashMap map, void* key);

/**
 * Return the size of the map
 */
size_t sizeHashMap(HashMap map);

// SETTERS

/**
 * Set or replace the value for the key
 */
void setHashMap(HashMap map, void* key, void* value);

/**
 * Remove the key.
 */
void* removeHashMap(HashMap map, void* key);

/**
 * Clear the map
 */
void clearHashMap(HashMap* map);

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorHashMap(HashMap map);

/**
 * Test if there is a next element
 */
int hasNextHashMap(HashMap map);

/**
 * Return the next element
 */
void * nextHashMap(HashMap map);

#endif // HASHMAP_H
