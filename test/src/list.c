#include "include/list.h"
#include <stdio.h>

typedef struct _cellList* CellList;

struct _set {
	int (*compar)(void*,void*);
	CellList head;
	CellList cur;
	CellList iterator;
	size_t size;
};

struct _cellList {
	void* value;
	CellList next;
};

// CONSTRUCTOR

/**
 * Create and allocate a new empty List.
 */
List newList(int (* compar)(void*,void*)) {
	List result = malloc(sizeof(*result));
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
 * Free the memory allocated from the List.
 */
void deleteList(List* l) {
	clearList(*l);
	free(*l);
	*l = NULL;
}

// GETTERS

/**
 * Test if the List contains the element.
 */
int containsList(List l, void* element) {
	return getList(l, element) != NULL;
}

/**
 * Get List's length
 */
size_t lengthList(List l) {
	return l->size;
}

/**
 * Get element in List
 */
void* getList(List l, void* element) {
	if (l->compar(element, l->cur->value) == 0) {
		return l->cur->value;
	}
	CellList c = l -> head;
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
 * Insert element in List
 */
void insertList(List l, void* element) {
	CellList newCell = malloc(sizeof(*newCell));
	newCell->value = element;
	newCell->next = l->head;
	l->head = newCell;
	++l->size;
}

/**
 * Remove the first element in List
 */
void* removeList(List l, void* element) {
	if (l->size != 0) {
		CellList cur = l->head->next;
		CellList prec = l->head;
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
 * Clear List
 */
void clearList(List l) {
	l->iterator = NULL;
	l->size = 0;
	while (l->head != NULL) {
		CellList c = l->head;
		l->head = l->head->next;
		free(c);
	}
}

// ITERATOR

/**
 * Initialize the iterator
 */
void initIteratorList(List l) {
	l->iterator = l->head;
}

/**
 * Test if there is a next element
 */
int hasNextList(List l) {
	return l->iterator != NULL;
}

/**
 * Return the next element
 */
void* nextList(List l) {
	void* value = l->iterator->value;
	l->iterator = l->iterator->next;
	return value;
}

