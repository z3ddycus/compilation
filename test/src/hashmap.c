#include <stdlib.h>
#include <stdio.h>
#include "include/sorted_map.h"
#include "include/hashmap.h"

#define SIZE_HASHMAP 3

struct _hashmap {
	SortedMap* lists;
	size_t (*hash) (void*);
	int (*compar) (void*, void*);
	size_t size;
	int iterator;
};


/**
 * Return a new hashmap allocated and initialized empty.
 */

HashMap newHashMap(size_t (*hash) (void*), int (*compar) (void*, void*)) {
	HashMap map = malloc(sizeof(*map));
	if (map == NULL) {
		fprintf(stderr, "Fail to allocate memory.");
		exit(EXIT_FAILURE);
	}
	
	map->size = 0;
	map->compar = compar;
	map->hash = hash;
	map->iterator = SIZE_HASHMAP;
	map->lists = malloc(sizeof(*map->lists) * SIZE_HASHMAP);
	if (map->lists == NULL) {
		free(map);
		fprintf(stderr, "Fail to allocate memory.");
		exit(EXIT_FAILURE);
	}
	for (int k = 0; k < SIZE_HASHMAP; ++k) {
		map->lists[k] = newMap(compar);
	}
	
	return map;
}

/**
 * Free the memory allocated to the hashmap.
 */
void deleteHashMap(HashMap* map) {
		for (int k = 0; k < SIZE_HASHMAP; ++k) {
			deleteMap(&((*map)->lists[k]));
		}
		free((*map)->lists);
		free(*map);
		*map = NULL;
}

// GETTER

/**
 * Test if the map contains the key
 */
int containsHashMap(HashMap map, void* key) {
	return getHashMap(map, key) != NULL;
}

/**
 * Return the value of the key
 */
void* getHashMap(HashMap map, void* key) {
	int indice = map->hash(key) % SIZE_HASHMAP;
	return getMap(map->lists[indice], key);
}

/**
 * Return the size of the map
 */
size_t sizeHashMap(HashMap map) {
	return map->size;
}

// SETTERS

/**
 * Set or replace the value for the key
 */
void setHashMap(HashMap map, void* key, void* value) {
	if (!containsHashMap(map, key)) {
		++map->size;
	}
	int indice = map->hash(key) % SIZE_HASHMAP;
	insertMap(map->lists[indice], key, value);
}

/**
 * Remove the key.
 */
void* removeHashMap(HashMap map, void* key) {
	if (containsHashMap(map, key)) {
		map->iterator = SIZE_HASHMAP;
		--map->size;
		int indice = map->hash(key) % SIZE_HASHMAP;
		return removeMap(map->lists[indice], key);
	}
	return NULL;
}

/**
 * Clear the map
 */
void clearHashMap(HashMap* map) {
	(*map)->iterator = SIZE_HASHMAP;
	for(int k = 0; k < SIZE_HASHMAP; ++k) {
		clearMap((*map)->lists[k]);
	}
}

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorHashMap(HashMap map) {
	map->iterator = 0;
	while(map->iterator < SIZE_HASHMAP && lengthMap(map->lists[map->iterator]) == 0) {
		++map->iterator;
	}
	if (map->iterator != SIZE_HASHMAP) {
		initIteratorMap(map->lists[map->iterator]);
	}
}

/**
 * Test if there is a next element
 */
int hasNextHashMap(HashMap map) {
	return map->iterator != SIZE_HASHMAP;
}

/**
 * Return the next element
 */
void* nextHashMap(HashMap map) {
	if (map->iterator == SIZE_HASHMAP) {
		fprintf(stderr, "The iterator has no longer next values");
		exit(EXIT_FAILURE);
	}
	void* value = nextMap(map->lists[map->iterator]);
	if (!hasNextMap(map->lists[map->iterator])) {
		while(map->iterator < SIZE_HASHMAP && lengthMap(map->lists[map->iterator]) == 0) {
			++map->iterator;
		}
		if (map->iterator != SIZE_HASHMAP) {
			initIteratorMap(map->lists[map->iterator]);
		}
	}
	return value;
}


