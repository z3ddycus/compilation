#include <stdlib.h>
#include <stdio.h>
#include "include/sorted_map.h"
#include "include/hashmap.h"

#define SIZE_HASHMAP 1024

struct _hashmap {
	SortedMap* lists;
	size_t (*hash) (void*);
	int (*compar) (void*, void*);
	size_t size;
};

HashMap newHashMap(size_t (*hash) (void*), int (*compar) (void*, void*)) {
	HashMap map = malloc(sizeof(*map));
	if (map == NULL) {
		fprintf(stderr, "Fail to allocate memory.");
		exit(EXIT_FAILURE);
	}
	
	map->size = 0;
	map->compar = compar;
	map->hash = hash;
	
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


