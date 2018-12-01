#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashMap.h"

int Hash(mapKey_t key);
pMapElement mapElementCreate(mapKey_t key, mapVal_t value);
pMapElement GetMapElement(pList lst, mapKey_t key);

pMap mapCreate()
{
    Map* newMap = (Map*) malloc(sizeof(Map));
    int i = 0;
    for (i = 0; i < HASH_SIZE; i++)
        newMap->data[i] = NULL;

    return newMap;
}

void mapDelete(pMap* map)
{
    int i = 0;

    for (i = 0; i < HASH_SIZE; i++)
    {
        List* lst = (*map)->data[i];
        if (!lst)
            continue;

        ListIterator* itr = listCreateBeginIterator(lst);

        while (itr)
        {
            pMapElement cur = listGetIteratorValue(itr);
            free(cur);

            listIteratorNext(&itr);
        }

        listDelete(&lst);
    }
    free(*map);
    *map = NULL;
}

void AddToMap(pMap map, mapKey_t key, mapVal_t value)
{
    int hash = Hash(key);
    List* lst = map->data[hash];

    if (lst == NULL)
    {
        lst = listCreate();
        map->data[hash] = lst;
    }

    if (listIsEmpty(lst))
        listPushBack(lst, mapElementCreate(key, value));
    else
    {
        pMapElement elem = GetMapElement(lst, key);
        if (!elem)
        {
            listPushBack(lst, mapElementCreate(key, value));
        }
        else
        {
            elem->value = value;
        }
    }
}

int IsInMap(pMap map, mapKey_t key)
{
    List* lst = map->data[Hash(key)];

    if (!lst)
        return 0;

    pMapElement el = GetMapElement(lst, key);
    return el ? 1 : 0;
}

mapVal_t GetFromMap(pMap map, mapKey_t key)
{
    List* lst = map->data[Hash(key)];

    if (!lst)
        return NULL; //NULL

    pMapElement el = GetMapElement(lst, key);
    return el ? el->value : NULL; //NULL
}

int Hash(mapKey_t key)
{
    int hash = 7;
    int i = 0;
    int len = strlen(key);
    for (i = 0; i < len; i++)
        hash = hash * 31 + key[i];
    hash %= HASH_SIZE;

    return hash;
}


pMapElement mapElementCreate(mapKey_t key, mapVal_t value)
{
    pMapElement elem = (pMapElement) malloc(sizeof(MapElement));
    elem->key = key;
    elem->value = value;

    return elem;
}

pMapElement GetMapElement(pList lst, mapKey_t key)
{
    ListIterator* itr = listCreateBeginIterator(lst);

    while (itr)
    {
        pMapElement cur = (pMapElement) listGetIteratorValue(itr);
        if (strcmp(cur->key, key) == 0) //strcmp(cur->key, key) == 0
        {
            listDeleteIterator(&itr);
            return cur;
        }
        listIteratorNext(&itr);
    }
    return NULL;
}

pList GetKeyList(pMap map)
{
    int i = 0;
    pList keyLst = listCreate();
    for (i = 0; i < HASH_SIZE; i++)
    {
        pList curLst = map->data[i];

        if (!curLst)
            continue;

        pListIterator itr = listCreateBeginIterator(curLst);
        while (itr)
        {
            pMapElement el = (pMapElement) listGetIteratorValue(itr);
            listPushBack(keyLst, el->key);
            listIteratorNext(&itr);
        }
    }
    return keyLst;
}
