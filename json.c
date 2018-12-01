#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "json.h"
#include "hashMap.h"


char*        skipSpaces(char* cur);
char*        parseValue(char** pcur);
pMap         parseMap(char** pcur);
pJsonElement parseData(char** pcur);
pList 		 parseArray(char** pcur);
char*        ReadText(const char* filename);


pJsonElement parseJson(const char* filename)
{
    char* Text = ReadText(filename);
    char* tmp = Text;
    pJsonElement res = parseData(&Text);
    free(tmp);

    return res;
}


char* ReadText(const char* filename)
{
    FILE* fin = fopen(filename, "rt");

    fseek(fin, 0, SEEK_END);
    unsigned size = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    char* buf = (char*) malloc( (size + 1) * sizeof(char));
    fread(buf, sizeof(char), size, fin);
    buf[size] = '\0';
    fclose(fin);

    return buf;
}

pMap parseMap(char** pcur)
{
    char* cur = *pcur;
    cur = skipSpaces(cur);

    if (*cur != '{')
    {
        printf("ERROR {\n");
        return NULL;
    }

    cur++;

    pMap map = mapCreate();

    while (*cur != '}')
    {
        if (*cur == ',')
            cur++;
        cur = skipSpaces(cur);
        //printf("%c\n", *cur);
        char* key = NULL;
        void* value = NULL;

        if (*cur == '"')
            key = parseValue(&cur);

        cur = skipSpaces(cur);
        if (*cur != ':')
        {
            printf("ERROR :\n");
            return NULL;
        }
        cur++;
        cur = skipSpaces(cur);

        value = parseData(&cur);

        //cur++;
        cur = skipSpaces(cur);
        //printf("%c\n", *cur);
        if (*cur != ',' && *cur != '}')
        {
            printf("ERROR ,} \n %s\n", cur);
            return NULL;
        }

        AddToMap(map, key, value);
    }
    *pcur = cur + 1;

    return map;
}

char* skipSpaces(char* cur)
{
    while (*cur == ' ' || *cur == '\n' || *cur == '\t' || *cur == '\r')
        cur++;

    return cur;
}

char* parseValue(char** pcur)
{
    char* cur = *pcur;
    cur++;
    unsigned size = 0;
    unsigned quote = 0;

    while (*cur != '"' || (*cur == '"' && cur[-1] == '\\'))
    {
        size++;
        if (*cur == '"' && cur[-1] == '\\')
            quote++;
        cur++;
    }

    size = size - quote;
    char* buf = (char*) malloc((size + 1) * sizeof(char));
    cur = *pcur;
    cur++;
    int i = 0;
    quote = 0;
    for (i = 0; i < size; i++)
    {
        if (cur[i + quote] == '\\' && cur[i + quote + 1] == '"')
        {
            quote++;
        }
        buf[i] = cur[i + quote];
    }
    buf[size] = '\0';
    while (*cur != '"' || (*cur == '"' && cur[-1] == '\\'))
        cur++;

    *pcur = ++cur;

    //printf("%s\n", buf);

    return buf;
}


pJsonElement parseData(char** pcur)
{
    //printf("!!!\n");
    *pcur = skipSpaces(*pcur);
    pJsonElement elem = (pJsonElement) malloc(sizeof(JsonElement));
    if (**pcur == '"')
    {
        elem->type = JSON_VALUE;
        elem->value = parseValue(pcur);
    }
    else if (**pcur == '{')
    {
        elem->type = JSON_MAP;
        elem->value = parseMap(pcur);
    }
    else if (**pcur == '[')
    {
        elem->type = JSON_ARRAY;
        elem->value = parseArray(pcur);
    }
    else
    {
        printf("Error parseData \n");
        free(elem);
        elem = NULL;
    }
    return elem;
}


pList parseArray(char** pcur)
{
    char* cur = *pcur;
    if (*cur != '[')
    {
        printf("parse array error, expected [\n");
        return NULL;
    }
    cur++;
    cur = skipSpaces(cur);
    pList lst = listCreate();
    while (*cur != ']')
    {
        pJsonElement elem = parseData(&cur);
        //cur = skipSpaces(cur);
        if (*cur != ',')
        {
            cur = skipSpaces(cur);
            if (*cur != ']')
            {
                printf("Error array , :: %d\n", *cur);
            }
            cur--;
        }
        cur++;
        listPushBack(lst, elem);
        cur = skipSpaces(cur);
    }
    cur++;
    *pcur = cur;
    return lst;
}


void DeleteJson(pJsonElement* p_elem)
{
    pJsonElement elem = *p_elem;

    if (elem->type == JSON_VALUE)
    {
        free(elem->value);
        free(elem);
        *p_elem = NULL;

        return;
    }
    else if (elem->type == JSON_ARRAY)
    {
        pList lst = (pList) elem->value;
        pListIterator itr = listCreateBeginIterator(lst);

        while (itr)
        {
            pJsonElement el = listGetIteratorValue(itr);
            DeleteJson(&el);
            listIteratorNext(&itr);
        }

        listDelete(&lst);
        free(elem);
        *p_elem = NULL;

        return;
    }
    else if (elem->type == JSON_MAP)
    {
        pMap map = (pMap) elem->value;
        pList keyLst = GetKeyList(map);
        pListIterator itr = listCreateBeginIterator(keyLst);
        while (itr)
        {
            mapKey_t key = (mapKey_t) listGetIteratorValue(itr);
            pJsonElement elem = GetFromMap(map, key);
            free(key);
            DeleteJson(&elem);
            listIteratorNext(&itr);
        }
        listDelete(&keyLst);
        mapDelete(&map);
        free(elem);
        *p_elem = NULL;
    }
}
