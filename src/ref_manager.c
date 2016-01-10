#include "include/ref_manager.h"
#include "include/hashmap.h"
#include "include/sorted_set.h"
#include <string.h>
#include <stdio.h>

#define SIZE_BUFFER_REFERENCE_MANAGER 10000000
#define SIZE_BUFFER_ID 10000
char compteur [SIZE_BUFFER_ID];

struct _ref_manager {
	HashMap map;
	int onlyUpdateMode;
	//int stringHeadMode;
};

size_t hashString(void* s);
int comparString(void* a, void* b);
//char* concateneChamp(RefManager manager, ChampReference champ);  OPTION -s
void deleteSpaceSuffixe(char* s);
char* stringAfterSpace(char* s);
char* setNb(int i);
int getNb(char* c);

/**
 * Return a new hashmap allocated and initialized empty.
 */
RefManager newRefManager() {
	RefManager result = malloc(sizeof(*result)); 
	result->map = newHashMap(hashString, comparString);
	result->onlyUpdateMode = 0;
	//result->stringHeadMode = 0;
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

// MODE
void setOnlyUpdateMode(RefManager manager, int flag) {
	manager->onlyUpdateMode = flag;
} 
void setStringHeadMode(RefManager manager, int flag) {
	//manager->stringHeadMode = flag;
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
	if (!manager->onlyUpdateMode || containsRefManager(manager, ref->id)) {
		Reference oldRef = getRefManager(manager, ref->id);
		setHashMap(manager->map, oldRef->id, updateReference(oldRef, ref));
	}
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

/**
void normalizeKey(RefManager manager) {
	HashMap nbUse = newHashMap(hashString, comparString);
	initIteratorRefManager(manager);
	while(hasNextRefManager(manager)) 
	{
		Reference ref = nextRefManager(manager);
		char id [SIZE_BUFFER_ID];
		char* author = ref->champs[ref_author];
		if (author != NULL) {
			
		}
		if (containsHashMap(nbUse, id)) 
		{
			char* nbTmp = getHashMap(nbUse, id);
			int occurence = getNb(nbTmp);
			if (occurence == 1) 
			{
				Reference oldRef = getRefManager(manager, id);
				char buffer[SIZE_BUFFER_ID];
				strcpy(buffer, id);
				size_t tailleCle = strlen(buffer);
				snprintf(buffer + tailleCle, SIZE_BUFFER_ID - tailleCle, ":1"); 
				free(oldRef->id);
				oldRef->id = buffer;
				removeRefManager(manager, id);
				setRefManager(manager, oldRef);
			}
			setHashMap(nbUse, id, setNb(occurence + 1));
			
		} 
		else 
		{
			setHashMap(nbUse, id, setNb(1));
		}
	}
}
*/
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
	return getHashMap(manager->map, nextHashMap(manager->map));
}

/**
 * Serialize the manager
 */
void referenceToBibtex(RefManager manager, FILE* f) {
	initIteratorRefManager(manager);
	while(hasNextRefManager(manager)) {
		Reference ref = nextRefManager(manager);
		fprintf(f, "%s", referenceToString(ref));
	}
}


// OUTILS
/**
char* concateneChamp(RefManager manager, ChampReference champ) {
		if (champ >= 0 && champ < NB_CHAMP_REF) {
			static char buffer[SIZE_BUFFER_REFERENCE_MANAGER];
			size_t taille = 0;
			initIteratorRefManager(manager);
			while(hasNextRefManager(manager)) {
				Reference ref = nextRefManager(manager);
				char* c = ref->champs[champ];
				if (c != NULL) {
					c = stringAfterSpace(c);
					deleteSpaceSuffixe(c);
					size_t tailleTmp = strlen(c);
					if (tailleTmp > 0) {
						strncpy()
					}
				}
			}
			return buffer;
		}
		return "";
}*/ // OPTION -s


char* setNb(int i) {
	return compteur + i;
}

int getNb(char* c) {
	return c - compteur;
}


size_t hashString(void* s) {
	char* str = s;
	size_t result = *str;
	while(*str != 0) {
		result = result * 37 + *str; 
	}
	return result;
}

int comparString(void* a, void* b) {
	return strcmp((char*) a, (char*) b);
}


void deleteSpaceSuffixe(char* s) {
	if (s != NULL) {
		size_t taille = strlen(s);
		for (int k = taille -1; k >= 0 && s[k] == ' '; --k) {
			s[k] = 0;
		}
	}
}

char* stringAfterSpace(char* s) {
	if (s != NULL) {
		size_t taille = strlen(s);
		char* result = s;
		for (int k = 0; k < taille && s[k] == ' '; ++k) {
			++result;
		}
		return result;
	}
	return NULL;
}
