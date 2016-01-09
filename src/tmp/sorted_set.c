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
SortedSet newSet(int (* compar)(void*,void*)) {
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
void deleteSet(SortedSet* l) {
	clearSet(*l);
	free(*l);
	*l = NULL;
}

// GETTERS

/**
 * Test if the SortedSet contains the key
 */
int containsSet(SortedSet l, void* element) {
	return getSet(l, element) != NULL;
}
 
/**
 * Get SortedSet's length
 */
size_t lengthSet(SortedSet l) {
	return l->size;
}

/**
 * Get element in SortedSet
 */
void* getSet(SortedSet l, void* element) {
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
void insertSet(SortedSet l, void* element) {
	if (containsSet(l, element)) 
	{
		l->cur->value = element;
	} 
	else 
	{
		++l->size;
		Cell newCell = malloc(sizeof(*newCell));
		newCell->value = element;
		if (l->compar(element, l->head->value) > 0) 
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
				if(cur == NULL || l->compar(element, cur->value) < 0)
				{
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
void* removeSet(SortedSet l, void* element) {
	if (containsSet(l, element)) 
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
void clearSet(SortedSet l) {
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
void initIteratorSet(SortedSet l) {
	l->iterator = l->head;
}

/**
 * Test if there is a next element
 */
int hasNextSet(SortedSet l) {
	return l->iterator != NULL;
}

/**
 * Return the next element
 */
void* nextSet(SortedSet l) {
	if (l->iterator == NULL) {
		fprintf(stderr, "the iterator don't have a next element");
	}
	void* result = l->iterator->value;
	l->iterator = l->iterator->next;
	return result;
}
