#include <stdlib.h>
#include <stdio.h>
#include "include/sorted_set.h"


int compar(void* key1, void* key2) {
	if (key1 == NULL || key2 == NULL) {
		return key1 == NULL ? (key2 == NULL ? 0 : 1) : 1;
	}
	char* k1 = (char*) key1;
	char* k2 = (char*) key2;
	while(*k1 && *k1 == *k2) {
		++k1;
		++k2;
	}
	if (!*k1 || !*k2){
		if (!*k1) {
			return (*k2 == 0) ? 0 : 1;
		}
		return -1;
	}
	if (*k1 > *k2) {
		return -1;
	}
	return 1;
}

int main(void) {
	SortedSet map = newSet(compar);
	insertSet(map, "a");
	insertSet(map, "b");
	insertSet(map, "c");
	insertSet(map, "d");
	insertSet(map, "e");
	insertSet(map, "f");
	initIteratorSet(map);
	while(hasNextSet(map)) {
		printf("%s\n", (char*)nextSet(map));
	}
	return EXIT_SUCCESS;
}
