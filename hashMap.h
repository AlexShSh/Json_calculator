#ifndef JSON_HASHMAP_H
#define JSON_HASHMAP_H

#include "list.h"

#define HASH_SIZE 64

typedef char* mapKey_t;   //char*
typedef void* mapVal_t;   //void*

typedef struct MapElement
{
    mapKey_t key;
    mapVal_t value;
} MapElement, *pMapElement;

typedef struct _map
{
    List* data[HASH_SIZE];
} Map, *pMap;


pMap mapCreate();
void mapDelete(pMap*);

void AddToMap(pMap, mapKey_t, mapVal_t);
int IsInMap(pMap, mapKey_t);
mapVal_t GetFromMap(pMap, mapKey_t);
pList GetKeyList(pMap);

#endif //JSON_HASHMAP_H
