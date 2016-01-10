#include "include/ref_manager.h"
#include "include/hashmap.h"
#include <string.h>
struct _ref_manager {
	HashMap map;
};

size_t hash(void* s);
int compar(void* a, void* b);

/**
 * Return a new hashmap allocated and initialized empty.
 */
RefManager newRefManager() {
	RefManager result = malloc(sizeof(*result)); 
	result->map = newHashMap(hash, compar);
	return result;
}

/**
 * Free the memory allocated to the hashmap.
 */
void deleteRefManager(RefManager* manager) {
	deleteHashMap(&((*manager)->map));
	free(*manager);
	*manager = NULL;
}

// GETTER

/**
 * Test if the map contains the key
 */
int containsRefManager(RefManager manager, char* id) {
	return containsHashMap(manager->map, id);
}

/**
 * Return the value of the key
 */
Reference getRefManager(RefManager manager, char* id) {
	return getHashMap(manager->map, id);
}

/**
 * Return the size of the map
 */
size_t sizeRefManager(RefManager manager) {
	return sizeHashMap(manager->map);
}

// SETTERS

/**
 * Set or replace the value for the key
 */
void setRefManager(RefManager manager, Reference ref) {
	setHashMap(manager->map, ref->id, ref);
}

/**
 * Remove the key.
 */
Reference removeRefManager(RefManager manager, char* id) {
	return removeHashMap(manager->map, id);
}

/**
 * Clear the map
 */
void clearRefManager(RefManager manager) {
	clearHashMap(manager->map);
}

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorRefManager(RefManager manager) {
	initIteratorHashMap(manager->map);
}

/**
 * Test if there is a next element
 */
int hasNextRefManager(RefManager manager) {
	return hasNextHashMap(manager->map);
}

/**
 * Return the next element
 */
Reference nextRefManager(RefManager manager) {
	return nextHashMap(manager->map);
}

// OUTILS


size_t hash(void* s) {
	char* str = s;
	size_t result = *str;
	while(*str != 0) {
		result = result * 37 + *str; 
	}
	return result;
}

int compar(void* a, void* b) {
	return strcmp((char*) a, (char*) b);
}
