#include "include/sorted_set.h"

enum TypeReference {

};

struct _ref{
		TypeReference type;
		
		char* address;
		char* abstract;
		char* annote;
		char* author;
		char* booktitle;
		char* chapter;
		char* crossref;
		char* edition;
		char* editor;
		char* eprint;
		char* howpublished;
		char* institution;
		char* journal;
		char* key;
		char* month;
		char* note;
		char* number;
		char* organization;
		char* pages;
		char* publisher;
		char* school;
		char* series;
		char* title;
		char* url;
		char* volume;
		char* year;
};

typedef struct _ref* Reference;

Reference newReference(TypeReference type) {
		Reference result = malloc(sizeof(*result));
		
		result->type = type;
		
		result->address = NULL;
		result->abstract = NULL;
		result->annote = NULL;
		result->author = NULL;
		result->booktitle = NULL;
		result->chapter = NULL;
		result->crossref = NULL;
		result->edition = NULL;
		result->editor = NULL;
		result->eprint = NULL;
		result->howpublished = NULL;
		result->institution = NULL;
		result->journal = NULL;
		result->key = NULL;
		result->month = NULL;
		result->note = NULL;
		result->number = NULL;
		result->organization = NULL;
		result->pages = NULL;
		result->publisher = NULL;
		result->school = NULL;
		result->series = NULL;
		result->title = NULL;
		result->url = NULL;
		result->volume = NULL;
		result->year = NULL;
}
