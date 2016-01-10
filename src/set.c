#include "include/set.h"
#include <stdio.h>

typedef struct _cellSet* CellSet;

struct _set {
	int (*compar)(void*,void*);
	CellSet head;
	CellSet cur;
	CellSet iterator;
	size_t size;
};

struct _cellSet {
	void* value;
	CellSet next;
};

// CONSTRUCTOR

/**
 * Create and allocate a new empty Set.
 */
Set newSet(int (* compar)(void*,void*)) {
	Set result = malloc(sizeof(*result));
	if (result == NULL) {
		fprintf(stderr, "Failure to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	result -> compar = compar;
	result -> head = NULL;
	result -> size = 0;
	result -> cur = NULL;
	
	return result;
}


// FREE
/**
 * Free the memory allocated from the Set.
 */
void deleteSet(Set* l) {
	clearSet(*l);
	free(*l);
	*l = NULL;
}

// GETTERS

/**
 * Test if the Set contains the element.
 */
int containsSet(Set l, void* element) {
	return getSet(l, element) != NULL;
}

/**
 * Get Set's length
 */
size_t lengthSet(Set l) {
	return l->size;
}

/**
 * Get element in Set
 */
void* getSet(Set l, void* element) {
		if (l->compar(element, l->cur->value) == 0) {
			return l->cur->value;
		}
		CellSet c = l -> head;
		void* result = NULL;
		while (c != NULL && result == NULL) {
			if (l->compar(element, c->value) == 0) {
				result = c->value;
				l->cur = c;
			}
			c = c -> next;
		}
		return result;
}

// SETTERS

/**
 * Insert element in Set
 */
void insertSet(Set l, void* element) {
	if (containsSet(l, element)) {
		CellSet newCell = malloc(sizeof(*newCell));
		newCell->value = element;
		newCell->next = l->head;
		l->head = newCell;
		++l->size;
	}
}

/**
 * Remove the first element in Set
 */
void* removeSet(Set l, void* element) {
	if (l->size != 0) {
		CellSet cur = l->head->next;
		CellSet prec = l->head;
		while(cur != NULL && l->compar(cur->value, element) != 0) {
			prec = cur;
			cur = cur->next;
		}
		if (cur != NULL) {
			prec->next = cur->next;
			void* result = cur->value;
			free(cur);
			--l->size;
			return result;
		}
	}
	return NULL;
}

/**
 * Clear Set
 */
void clearSet(Set l) {
	l->iterator = NULL;
	l->size = 0;
	while (l->head != NULL) {
		CellSet c = l->head;
		l->head = l->head->next;
		free(c);
	}
}

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorSet(Set l) {
	l->iterator = l->head;
}

/**
 * Test if there is a next element
 */
int hasNextSet(Set l) {
	return l->iterator != NULL;
}

/**
 * Return the next element
 */
void* nextSet(Set l) {
	void* value = l->iterator->value;
	l->iterator = l->iterator->next;
	return value;
}

