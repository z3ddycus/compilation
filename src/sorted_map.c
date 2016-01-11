#include <stdio.h>
#include <stdlib.h>
#include "include/sorted_map.h"

typedef struct _cell * Cell;

struct _cell {
	void* key;
	void* value;
	Cell next;
};
 
struct _Map {
		int (*compar)(void*,void*);
		Cell head;
		size_t size;
		Cell cur;
		Cell iterator;
};



// CONSTRUCTOR

/**
 * Create and allocate a new empty SortieMap.
 */
SortedMap newMap(int (* compar)(void*,void*)) {
	SortedMap result = malloc(sizeof(*result));
	result->compar = compar;
	result->size = 0;
	result->cur = NULL;
	result->iterator = NULL;
	return result;
}


// FREE
/**
 * Free the memory allocated from the SortedMap.
 */
void deleteMap(SortedMap* l) {
	clearMap(*l);
	free(*l);
	*l = NULL;
}

// GETTERS

/**
 * Test if the SortedMap contains the key
 */
int containsMap(SortedMap l, void* key) {
	return getMap(l, key) != NULL;
}
 
/**
 * Get SortedMap's length
 */
size_t lengthMap(SortedMap l) {
	return l->size;
}

/**
 * Get element in SortedMap
 */
void* getMap(SortedMap l, void* key) {
	if (l->cur != NULL && l->compar(l->cur->key, key) == 0)
	{
		return l->cur->value;
	} 
	else 
	{	
		Cell tmp = l->head;
		int continu = 1;
		int result = 0;
		while(continu && tmp != NULL) 
		{
				int comparValue = l->compar(tmp->key, key);
				if (comparValue == 0) 
				{
					l->cur = tmp;
					continu = 0;
					result = 1;
				} 
				else 
				{
					if (comparValue < 0) 
					{
						continu = 0;
					} 
					else 
					{
						tmp = tmp->next;
					}
				}
		}
		return result ? tmp->value : NULL;
	}
}

// SETTERS

/**
 * Insert element in SortedMap
 */
void insertMap(SortedMap l, void* key, void* value) {
	if (containsMap(l, key)) 
	{
		l->cur->value = value;
	} 
	else 
	{
		++l->size;
		Cell newCell = malloc(sizeof(*newCell));
		newCell->value = value;
		newCell->key = key;
		if (l->head == NULL || l->compar(key, l->head->key) > 0) 
		{	
			newCell->next = l->head;
			l->head = newCell;
		} 
		else 
		{
			Cell cur = l->head->next;
			Cell prec = l->head;
			int continu = 1;
			while(continu)
			{
				if(cur == NULL || l->compar(key, cur->key) > 0)
				{
					continu = 0;
					prec->next = newCell;
					newCell->next = cur;
				}
				else
				{
					prec = cur;
					cur = cur->next;
				}
			}
		}
	}
}

/**
 * Remove element in SortedMap
 */
void* removeMap(SortedMap l, void* key) {
	if (containsMap(l, key)) 
	{
		l->iterator = NULL;
		--l->size;
		void* value = l->cur->value;
		free(l->cur);
		l->cur = NULL;
		return value;
	}
	return NULL;
}

/**
 * Clear SortedMap
 */
void clearMap(SortedMap l) {
	l->iterator = NULL;
	l->size = 0;
	while(l->head != NULL) {
		Cell tmp = l->head;
		l->head = l->head->next;
		free(tmp);
	}
}


// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorMap(SortedMap l) {
	l->iterator = l->head;
}

/**
 * Test if there is a next element
 */
int hasNextMap(SortedMap l) {
	return l->iterator != NULL;
}

/**
 * Return the next element
 */
void* nextMap(SortedMap l) {
	if (l->iterator == NULL) {
		fprintf(stderr, "the iterator don't have a next element");
		exit(EXIT_FAILURE);
	}
	void* result = l->iterator->key;
	l->iterator = l->iterator->next;
	return result;
}

void toString(SortedMap l) {
	printf("Entete\n");
	printf("\t Head : %s\n\tSize : %zu\n", (char*)l->head, l->size);
	Cell cur = l->head;
	while(cur != NULL) {
		printf("Element\n\t%s\n\t%s\n\t%s\n", (char*)cur->key, (char*)cur->value, (char*)cur->next);
		cur = cur->next;
	}
}
