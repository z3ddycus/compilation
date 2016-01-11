#ifndef GLOBAL_h
#define GLOBAL_h

#include "ref_manager.h"
#include "sorted_set.h"
#include "list.h"

RefManager refManager;
SortedSet keys;
List texFiles;
List bibFiles;

// Fonctions pour rassembler un champ avec sa valeur.
struct _champVal{
    ChampReference champ;
    char* val;
};
typedef struct _champVal* ChampVal;

List champValList;

#endif
