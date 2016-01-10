#ifndef REFERENCE_H
#define REFERENCE_H

enum _typeRef {
	ref_article = 0,
	ref_book,
	ref_booklet,
	ref_conference,
	ref_inbook,
	ref_incollection,
	ref_inproceedings,
	ref_manual,
	ref_mastersthesis,
	ref_misc,
	ref_phdthesis,
	ref_proceedings,
	ref_techreport,
	ref_unpublished,
	NB_TYPE_REF
};

enum _typeChamp {
		ref_address = 0,
		ref_abstract,
		ref_annote,
		ref_author,
		ref_booktitle,
		ref_chapter,
		ref_crossref,
		ref_edition,
		ref_editor,
		ref_eprint,
		ref_howpublished,
		ref_institution,
		ref_isbn,
		ref_journal,
		ref_key,
		ref_month,
		ref_note,
		ref_number,
		ref_organization,
		ref_pages,
		ref_publisher,
		ref_school,
		ref_series,
		ref_title,
		ref_type,
		ref_url,
		ref_volume,
		ref_year,
		NB_CHAMP_REF
};

typedef enum _typeChamp ChampReference;
typedef enum _typeRef TypeReference;

struct _ref{
		TypeReference type;
		char* id;
		char* champs[NB_CHAMP_REF];
};

typedef struct _ref* Reference;

/**
 * Create a new Reference with the type giving in argument
 */
Reference newReference(TypeReference type, char* id);

/**
 * Delete a reference
 */
void deleteReference(Reference* ref);

/**
 * Set the champ with the value s
 */
void setReference(Reference ref, ChampReference champ, char* s);

/**
 * Return a string representing the reference
 */
char* referenceToString(Reference ref);

/**
 * Concatene the information non empty contained in source in target
 * if target is NULL a new reference is allocated and initilize with 
 * information from the source
 * Return target
 */
Reference updateReference(Reference target, Reference source);

/**
 * Return a copy of source
 */
Reference copyReference(Reference source);
#endif

