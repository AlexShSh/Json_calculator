#ifndef JSON_JSON_H
#define JSON_JSON_H

#include "hashMap.h"

typedef enum JsonElValue_t
{
    JSON_MAP = 1,
    JSON_VALUE,
    JSON_ARRAY
} JsonElValue_t;

typedef struct JsonElement
{
    JsonElValue_t type;
    void* value;
} JsonElement, *pJsonElement;


pJsonElement parseJson(const char* filename);
void DeleteJson(pJsonElement* pelem);

#endif //JSON_JSON_H
