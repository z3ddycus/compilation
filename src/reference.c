#include "include/reference.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define SIZE_BUFFER_REFERENCE 1000000



char* typeReferenceArray[NB_TYPE_REF] = {
	"Article",
	"Book",
	"Booklet",
	"Conference",
	"Inbook",
	"Incollection",
	"Inproceedings",
	"Manual",
	"Mastersthesis",
	"Misc",
	"Phdthesis",
	"Proceedings",
	"Techreport",
	"Unpublished"
};

char* champReferenceArray[NB_CHAMP_REF] = {
	"address",
	"abstract",
	"annote",
	"author",
	"booktitle",
	"chapter",
	"crossref",
	"edition",
	"editor",
	"eprint",
	"howpublished",
	"institution",
	"isbn",
	"journal",
	"key",
	"month",
	"note",
	"number",
	"organization",
	"pages",
	"publisher",
	"school",
	"series",
	"title",
	"type",
	"url",
	"volume",
	"year"
};
void deleteSpaceSuffixe(char* s);
char* stringAfterSpace(char* s);


Reference newReference(TypeReference type, char* id) {
		size_t taille = strlen(id);
		char* valeur = malloc((taille + 1) * sizeof(*valeur));
		strncpy(valeur, id, taille);
		
		Reference result = malloc(sizeof(*result));
		result->type = type;
		result->id = valeur;
		
		for (int k = 0; k < NB_CHAMP_REF; ++k) {
			result->champs[k] = "";
		}
		return result;
}

/**
 * Return a Type corresponding to the string.
 */
TypeReference getType(char* s) {
    char str[strlen(s) + 1];
    sprintf(str, "%s", s);
    for (int i = 1; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    str[0] = toupper(str[0]);
        
    for (int i = 0; i < NB_TYPE_REF; ++i) {
        if (strcmp(str, typeReferenceArray[i]) == 0) {
            return i;
        }
    }
    
    fprintf(stderr, "Type %s inconnu.\n", s);
    exit(0);
}

/**
 * Return a Champ corresponding to the string.
 */
ChampReference getChamp(char* s) {
    char str[strlen(s) + 1];
    sprintf(str, "%s", s);
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    
    for (int i = 0; i < NB_CHAMP_REF; ++i) {
        if (strcmp(str, champReferenceArray[i]) == 0) {
            return i;
        }
    }
    
    fprintf(stderr, "Champ %s inconnu.\n", s);
    exit(0);
}

void deleteReference(Reference* ref) {
	for (int k = 0; k < NB_CHAMP_REF; ++k) {
		if ((*ref)->champs[k] != NULL) {
			free((*ref)->champs[k]);
		}
	}
	free(*ref);
	*ref = NULL;
}

void setReference(Reference ref, ChampReference champ, char* s) {
	if (champ <= NB_CHAMP_REF) {
		size_t length = strlen(s);
		char* valeur = malloc((length + 1) * sizeof(*valeur));
		strncpy(valeur, s, length);
		ref->champs[champ] = valeur;
	}
}

char* referenceToString(Reference ref) {
	static char result[SIZE_BUFFER_REFERENCE];
	switch(ref->type) {
		case ref_article :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_article],
						ref->id,
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_journal],
						ref->champs[ref_journal],
						champReferenceArray[ref_year],
						ref->champs[ref_year],
						champReferenceArray[ref_volume],
						ref->champs[ref_volume],
						champReferenceArray[ref_number],
						ref->champs[ref_number],
						champReferenceArray[ref_pages],
						ref->champs[ref_pages],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_key],
						ref->champs[ref_key]);
				break;
		case ref_book :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_book],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_edition],
						ref->champs[ref_edition],
						champReferenceArray[ref_editor],
						ref->champs[ref_editor],
						champReferenceArray[ref_isbn],
						ref->champs[ref_isbn],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_publisher],
						ref->champs[ref_publisher],
						champReferenceArray[ref_series],
						ref->champs[ref_series],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_volume],
						ref->champs[ref_volume],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_booklet :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_booklet],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_howpublished],
						ref->champs[ref_howpublished],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_conference :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_conference],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_booktitle],
						ref->champs[ref_booktitle],
						champReferenceArray[ref_editor],
						ref->champs[ref_editor],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_organization],
						ref->champs[ref_organization],
						champReferenceArray[ref_pages],
						ref->champs[ref_pages],
						champReferenceArray[ref_publisher],
						ref->champs[ref_publisher],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_inbook :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_inbook],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_chapter],
						ref->champs[ref_chapter],
						champReferenceArray[ref_edition],
						ref->champs[ref_edition],
						champReferenceArray[ref_editor],
						ref->champs[ref_editor],
						champReferenceArray[ref_eprint],
						ref->champs[ref_eprint],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_pages],
						ref->champs[ref_pages],
						champReferenceArray[ref_publisher],
						ref->champs[ref_publisher],
						champReferenceArray[ref_series],
						ref->champs[ref_series],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_volume],
						ref->champs[ref_volume],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_incollection :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_incollection],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_booktitle],
						ref->champs[ref_booktitle],
						champReferenceArray[ref_editor],
						ref->champs[ref_editor],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_organization],
						ref->champs[ref_organization],
						champReferenceArray[ref_pages],
						ref->champs[ref_pages],
						champReferenceArray[ref_publisher],
						ref->champs[ref_publisher],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_inproceedings :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_inproceedings],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_booktitle],
						ref->champs[ref_booktitle],
						champReferenceArray[ref_editor],
						ref->champs[ref_editor],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_organization],
						ref->champs[ref_organization],
						champReferenceArray[ref_pages],
						ref->champs[ref_pages],
						champReferenceArray[ref_publisher],
						ref->champs[ref_publisher],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_manual :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_manual],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_edition],
						ref->champs[ref_edition],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_organization],
						ref->champs[ref_organization],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_mastersthesis :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_mastersthesis],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_school],
						ref->champs[ref_school],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_misc :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_misc],
						ref->id,
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_howpublished],
						ref->champs[ref_howpublished],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_phdthesis :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_phdthesis],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_school],
						ref->champs[ref_school],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_proceedings :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_proceedings],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_editor],
						ref->champs[ref_editor],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_organization],
						ref->champs[ref_organization],
						champReferenceArray[ref_publisher],
						ref->champs[ref_publisher],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_techreport :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_techreport],
						ref->id,
						champReferenceArray[ref_address],
						ref->champs[ref_address],
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_institution],
						ref->champs[ref_institution],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_number],
						ref->champs[ref_number],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_type],
						ref->champs[ref_type],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		case ref_unpublished :
				snprintf(result, SIZE_BUFFER_REFERENCE,
						"@%s{%s,\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s},\n\t%s = {%s}\n}\n",
						typeReferenceArray[ref_unpublished],
						ref->id,
						champReferenceArray[ref_author],
						ref->champs[ref_author],
						champReferenceArray[ref_key],
						ref->champs[ref_key],
						champReferenceArray[ref_month],
						ref->champs[ref_month],
						champReferenceArray[ref_note],
						ref->champs[ref_note],
						champReferenceArray[ref_title],
						ref->champs[ref_title],
						champReferenceArray[ref_year],
						ref->champs[ref_year]);
				break;
		default:
				break;
	}
	return result;
}

Reference updateReference(Reference target, Reference source) {
	if (source != NULL) {
		if (target == NULL) {
			target = newReference(source->type, source->id);
		}
		for (int k = 0; k < NB_CHAMP_REF; ++k) {
			char* c = source->champs[k];
			if (c != NULL) {
				c = stringAfterSpace(c);
				deleteSpaceSuffixe(c);
				if (strlen(c) > 0) {
					setReference(target, k, c);
				}
			}
		}
	}
	return target;
}

Reference copyReference(Reference source) {
	return updateReference(NULL, source);
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
