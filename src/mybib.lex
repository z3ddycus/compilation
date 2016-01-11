%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/global.h"
#include "mybib.tab.h"
#include "include/hashmap.h"

char* filePrefix;
%}
CITE \\cite\{[^\}]+\}
NOCITE \\nocite\{[^\}]+\}
BIBNAME \\bibliography\{[^\}]+\}
INCLUDE \\include\{[^\}]+\}
INPUT \\input\{[^\}]+\}

TYPEREF @Article|@Book|@Booklet|@Conference|@Inbook|@Incollection|@Inproceedings|@Manual|@Mastersthesis|@Misc|@Phdthesis|@Proceedings|@Techreport|@Unpublished
TYPECHAMP address|abstract|annote|author|booktitle|chapter|crossref|edition|editor|eprint|howpublished|institution|isbn|journal|key|month|note|number|organization|pages|publisher|school|series|title|type|url|volume|year
KEY \{[a-zA-Z0-9]+(:[a-zA-Z0-9]+)*,
VAL \{.*\},|\{.*\}\n

%s latex
%s bibtex
%%
<latex>{CITE} {
    const size_t size = yyleng - 7;
    char* key = malloc(size + 1);
    memcpy(key, &yytext[6], size);
    key[size] = '\0';
    insertSortedSet(keys, key);
}

<latex>{NOCITE} {
    const size_t size = yyleng - 9;
    char* key = malloc(size + 1);
    memcpy(key, &yytext[8], size);
    key[size] = '\0';
    insertSortedSet(keys, key);
}

<latex>{BIBNAME} {
    const size_t size = yyleng - 11;
    char* file = malloc(size + 1);
    file = malloc(size + 1);
    memcpy(file, &yytext[14], size - 4);
    file[size - 4] = '.';
    file[size - 3] = 'b';
    file[size - 2] = 'i';
    file[size - 1] = 'b';
    file[size] = '\0';
    insertList(bibFiles, file);
}

<latex>{INCLUDE} {
    const size_t size = yyleng - 6;
    char* file = malloc(size + 1);
    memcpy(file, &yytext[9], size - 4);
    file[size - 4] = '.';
    file[size - 3] = 't';
    file[size - 2] = 'e';
    file[size - 1] = 'x';
    file[size] = '\0';
    insertList(texFiles, file);
}

<latex>{INPUT} {
    const size_t size = yyleng - 4;
    char* file = malloc(size + 1);
    memcpy(file, &yytext[9], size - 4);
    file[size - 4] = '.';
    file[size - 3] = 't';
    file[size - 2] = 'e';
    file[size - 1] = 'x';
    file[size] = '\0';
    insertList(texFiles, file);
}

<bibtex>{TYPEREF} {
    size_t size = strlen(yytext) - 1;
    yylval.string = malloc(size + 1);
    memcpy(yylval.string, &yytext[1], size);
    yylval.string[size] = '\0';
    //printf("Ref : %s\n", yylval.string);
    return TYPEREF;
}

<bibtex>{TYPECHAMP} {
    //printf("Champ : %s\n", yytext);
    size_t size = strlen(yytext);
    yylval.string = malloc(size + 1);
    memcpy(yylval.string, &yytext[0], size);
    yylval.string[size] = '\0';
    return TYPECHAMP;
}

<bibtex>{KEY} {
    size_t size = strlen(yytext) - 2;
    yylval.string = malloc(size + 1);
    memcpy(yylval.string, &yytext[1], size);
    yylval.string[size] = '\0';
    //printf("Key : %s\n", yylval.string);
    return KEY;
}

<bibtex>{VAL} {
    size_t size = strlen(yytext) - 3;
    yylval.string = malloc(size + 1);
    memcpy(yylval.string, &yytext[1], size);
    yylval.string[size] = '\0';
    //printf("Val : %s\n", yylval.string);
    return VAL;
}

<bibtex>\} return '}';

.|\n {}
%%
int yywrap(void) {
    if (lengthList(texFiles) > 0) {
        char* file = popList(texFiles);
        char* s = malloc(strlen(filePrefix) + strlen(file) + 1);
        sprintf(s, "%s%s", filePrefix, file);
        fclose(yyin);
        yyin = fopen(s, "r");
        if (yyin == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier de nom %s.\n", file);
            exit(0);
        }

        BEGIN(latex);
        return 0;
    }

    if (lengthList(bibFiles) > 0) {
        char* file = popList(bibFiles);
        char* s = malloc(strlen(filePrefix) + strlen(file) + 1);
        sprintf(s, "%s%s", filePrefix, file);
        fclose(yyin);
        yyin = fopen(s, "r");
        if (yyin == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier de nom %s.\n", file);
            exit(0);
        }

        BEGIN(bibtex);
        return 0;
    }
    return 1;
}

int champValComp(ChampVal v1, ChampVal v2) {
    if (v1->champ == v2->champ) {
        return strcmp(v1->val, v2->val);
    }
    return v1->champ - v2->champ;
}

// Calcul du prefixe
void calcPrefix(char* s) {
    char* p = strchr(s, '/');
    if (p != NULL) {
        size_t size = p - s + 1;
        filePrefix = malloc(size + 1);
        memcpy(filePrefix, s, size);
        filePrefix[size] = '\0';
    } else {
        filePrefix = malloc(1);
        filePrefix[0] = '\0';
    }
}

// Fonction de hachage.
size_t hash(void* s) {
	char* str = s;
	size_t result = *str;
	while(*str != 0) {
		result = result * 37 + *str;
        ++str;
	}
	return result;
}

int main(int argc, char** argv) {
    if (argc == 0) {
        fprintf(stderr, "Usage %s [-bcekstuo]\n", argv[0]);
        exit(0);
    }

    // Initialisation des variables globales.
    refManager = newRefManager();

    keys = newSortedSet((int (*) (void*, void*)) strcmp);
    texFiles = newList((int (*) (void*, void*)) strcmp);
    bibFiles = newList((int (*) (void*, void*)) strcmp);
    bibKeys = newList((int (*) (void*, void*)) strcmp);
    champValList = newList((int (*) (void*, void*)) champValComp);

    /**
    -b 1 arg  : genere un bibtex a partir d'un .tex
    -c 1 arg  : verifie que chaque toutes les entrées ont une entrée propre
    -e 3 args : extraction d'un bibtex par filtre regexp
    -k 1 arg  : normalise les clés d'un .bib
    -s 1 arg  : extraction des champs pour tri
    -t 2 args : ne garde que les entrées de type t
    -u 1 arg  : supprime les doublons
    -o 1 arg  : redirection de la sortie standard dans un fichier
    */
    if (strcmp(argv[1], "-b") == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage %s -b texFile\n", argv[0]);
            exit(0);
        }

        calcPrefix(argv[2]);
        yyin = fopen(argv[2], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", argv[3]);
            exit(0);
        }
        BEGIN(latex);
        yyparse();

        initIteratorSortedSet(keys);
        while (hasNextSortedSet(keys)) {
            char* key = nextSortedSet(keys);
            printf("Key : %s\n", key);
            Reference ref = getRefManager(refManager, key);
            if (ref != NULL) {
                printf("%s\n", referenceToString(ref));
            }
        }
    } else if (strcmp(argv[1], "-c") == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage %s -c bibFile\n", argv[0]);
            exit(0);
        }

        calcPrefix(argv[2]);
        yyin = fopen(argv[2], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", argv[3]);
            exit(0);
        }
        BEGIN(bibtex);
        yyparse();

        SortedSet set = newSortedSet((int (*) (void*, void*)) strcmp);
        initIteratorList(bibKeys);
        while (hasNextList(bibKeys)) {
            char* key = nextList(bibKeys);
            if (containsSortedSet(set, key)) {
                printf("Doublon sur la clé : %s\n", key);
            } else {
                insertSortedSet(set, key);
            }
        }
    } else if (strcmp(argv[1], "-e") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage %s -e opt regexp bibFile\n", argv[0]);
            exit(0);
        }

        calcPrefix(argv[4]);
    } else if (strcmp(argv[1], "-k") == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage %s -k bibFile\n", argv[0]);
            exit(0);
        }

        calcPrefix(argv[2]);
    } else if (strcmp(argv[1], "-s") == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage %s -s bibFile\n", argv[0]);
            exit(0);
        }

        calcPrefix(argv[2]);
        yyin = fopen(argv[2], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", argv[3]);
            exit(0);
        }
        BEGIN(bibtex);
        yyparse();

        HashMap publishers = newHashMap((size_t (*) (void*)) hash, (int (*) (void*, void*)) strcmp);
        HashMap series = newHashMap((size_t (*) (void*)) hash, (int (*) (void*, void*)) strcmp);
        HashMap journals = newHashMap((size_t (*) (void*)) hash, (int (*) (void*, void*)) strcmp);
        HashMap organizations = newHashMap((size_t (*) (void*)) hash, (int (*) (void*, void*)) strcmp);

        initIteratorRefManager(refManager);
        while (hasNextRefManager(refManager)) {
            Reference ref = nextRefManager(refManager);
            if (strlen(ref->champs[ref_publisher]) != 0) {
                size_t size = strlen(ref->champs[ref_publisher]);
                char* key = malloc(size + 1);
                int count = 0;
                for (int i = 0; i < size; ++i) {
                    if (isalpha(ref->champs[ref_publisher][i])) {
                        key[count] = toupper(ref->champs[ref_publisher][i]);
                        ++count;
                    }
                }
                key[count] = '\0';
                setHashMap(publishers, key, ref->champs[ref_publisher]);
                ref->champs[ref_publisher] = key;
            } else if (strlen(ref->champs[ref_journal]) != 0) {
                size_t size = strlen(ref->champs[ref_journal]);
                char* key = malloc(size + 1);
                int count = 0;
                for (int i = 0; i < size; ++i) {
                    if (isalpha(ref->champs[ref_journal][i])) {
                        key[count] = toupper(ref->champs[ref_journal][i]);
                        ++count;
                    }
                }
                key[count] = '\0';
                setHashMap(journals, key, ref->champs[ref_journal]);
                ref->champs[ref_journal] = key;
            } else if (strlen(ref->champs[ref_series]) != 0) {
                size_t size = strlen(ref->champs[ref_series]);
                char* key = malloc(size + 1);
                int count = 0;
                for (int i = 0; i < size; ++i) {
                    if (isalpha(ref->champs[ref_series][i])) {
                        key[count] = toupper(ref->champs[ref_series][i]);
                        ++count;
                    }
                }
                key[count] = '\0';
                setHashMap(series, key, ref->champs[ref_series]);
                ref->champs[ref_series] = key;
            } else if (strlen(ref->champs[ref_organization]) != 0) {
                size_t size = strlen(ref->champs[ref_organization]);
                char* key = malloc(size + 1);
                int count = 0;
                for (int i = 0; i < size; ++i) {
                    if (isalpha(ref->champs[ref_organization][i])) {
                        key[count] = toupper(ref->champs[ref_organization][i]);
                        ++count;
                    }
                }
                key[count] = '\0';
                setHashMap(organizations, key, ref->champs[ref_organization]);
                ref->champs[ref_organization] = key;
            }
        }

        if (sizeHashMap(publishers) > 0) {
            printf("@Comment{\"Automatically generated strings for fields of type publisher\"}\n");
            printf("@String{");
            initIteratorHashMap(publishers);
            while (hasNextHashMap(publishers)) {
                char* key = nextHashMap(publishers);
                char* val = getHashMap(publishers, key);
                printf("%s=\"%s\"", key, val);
                if (hasNextHashMap(publishers)) {
                    printf(",");
                }
            }
            printf("}\n");
        }

        if (sizeHashMap(journals) > 0) {
            printf("@Comment{\"Automatically generated strings for fields of type journal\"}\n");
            printf("@String{");
            initIteratorHashMap(journals);
            while (hasNextHashMap(journals)) {
                char* key = nextHashMap(journals);
                char* val = getHashMap(journals, key);
                printf("%s=\"%s\"", key, val);
                if (hasNextHashMap(journals)) {
                    printf(",");
                }
            }
            printf("}\n");
        }

        if (sizeHashMap(series) > 0) {
            printf("@Comment{\"Automatically generated strings for fields of type series\"}\n");
            printf("@String{");
            initIteratorHashMap(series);
            while (hasNextHashMap(series)) {
                char* key = nextHashMap(series);
                char* val = getHashMap(series, key);
                printf("%s=\"%s\"", key, val);
                if (hasNextHashMap(series)) {
                    printf(",");
                }
            }
            printf("}\n");
        }

        if (sizeHashMap(organizations) > 0) {
            printf("@Comment{\"Automatically generated strings for fields of type organization\"}\n");
            printf("@String{");
            initIteratorHashMap(organizations);
            while (hasNextHashMap(organizations)) {
                char* key = nextHashMap(organizations);
                char* val = getHashMap(organizations, key);
                printf("%s=\"%s\"", key, val);
                if (hasNextHashMap(organizations)) {
                    printf(",");
                }
            }
            printf("}\n");
        }

        referenceToBibtex(refManager, stdout);
    } else if (strcmp(argv[1], "-t") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage %s -t type bibFile\n", argv[0]);
            exit(0);
        }
        calcPrefix(argv[3]);
        yyin = fopen(argv[3], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", argv[3]);
            exit(0);
        }
        BEGIN(bibtex);
        yyparse();


        TypeReference type = getType(argv[2]);
        initIteratorRefManager(refManager);
        while (hasNextRefManager(refManager)) {
            Reference ref = nextRefManager(refManager);
            if (ref->type == type) {
                printf("%s", referenceToString(ref));
            }
        }
    } else if (strcmp(argv[1], "-u") == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage %s -u bibFile\n", argv[0]);
            exit(0);
        }

        calcPrefix(argv[2]);
    } else if (strcmp(argv[1], "-o") == 0) {
        fprintf(stderr, "-o non gérée encore\n");
        exit(0);
    } else {
        fprintf(stderr, "Usage %s [-bcekstuo]\n", argv[0]);
        exit(0);
    }

    return EXIT_SUCCESS;
}
