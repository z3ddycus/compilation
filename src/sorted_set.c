#include <stdio.h>
#include <stdlib.h>
#include "include/sorted_set.h"

typedef struct _cell * Cell;

struct _cell {
	void* value;
	Cell next;
};
 
struct _set {
		int (*compar)(void*,void*);
		Cell head;
		size_t size;
		Cell cur;
		Cell iterator;
};



// CONSTRUCTOR

/**
 * Create and allocate a new empty SortieSet.
 */
SortedSet newSortedSet(int (* compar)(void*,void*)) {
	SortedSet result = malloc(sizeof(*result));
	result->compar = compar;
	result->size = 0;
	result->cur = NULL;
	result->iterator = NULL;
	return result;
}


// FREE
/**
 * Free the memory allocated from the SortedSet.
 */
void deleteSortedSet(SortedSet* l) {
	clearSortedSet(*l);
	free(*l);
	*l = NULL;
}

// GETTERS

/**
 * Test if the SortedSet contains the key
 */
int containsSortedSet(SortedSet l, void* element) {
	return getSortedSet(l, element) != NULL;
}
 
/**
 * Get SortedSet's length
 */
size_t lengthSortedSet(SortedSet l) {
	return l->size;
}

/**
 * Get element in SortedSet
 */
void* getSortedSet(SortedSet l, void* element) {
	if (l->cur != NULL && l->compar(l->cur->value, element)) 
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
				int comparValue = l->compar(tmp->value, element);
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
 * Insert element in SortedSet
 */
void insertSortedSet(SortedSet l, void* element) {
	if (containsSortedSet(l, element))
	{
		l->cur->value = element;
	} 
	else 
	{
		++l->size;
		Cell newCell = malloc(sizeof(*newCell));
		newCell->value = element;
		if (l->head == NULL || l->compar(element, l->head->value) > 0) 
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
				if(cur == NULL || l->compar(element, cur->value) > 0)
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
 * Remove element in SortedSet
 */
void* removeSortedSet(SortedSet l, void* element) {
	if (containsSortedSet(l, element))
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
 * Clear SortedSet
 */
void clearSortedSet(SortedSet l) {
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
void initIteratorSortedSet(SortedSet l) {
	l->iterator = l->head;
}

/**
 * Test if there is a next element
 */
int hasNextSortedSet(SortedSet l) {
	return l->iterator != NULL;
}

/**
 * Return the next element
 */
void* nextSortedSet(SortedSet l) {
	if (l->iterator == NULL) {
		fprintf(stderr, "the iterator don't have a next element");
	}
	void* result = l->iterator->value;
	l->iterator = l->iterator->next;
	return result;
}
