#ifndef JSON_LIST_H
#define JSON_LIST_H

typedef struct list_element
{
    void* value;
    struct list_element *next;
    struct list_element *prev;
} ListElement, *pListElement;

typedef struct list
{
    pListElement first;
    pListElement last;
} List, *pList;


List* listCreate   ();
void  listPushBack (pList lst, void* value);
void  listDelete   (pList* lst);
int   listIsEmpty  (pList lst);

typedef struct ListIterator
{
    ListElement* value;
    ListElement* next;
} ListIterator, *pListIterator;

ListIterator* listCreateBeginIterator(List* lst);
void listDeleteIterator(ListIterator** itr);
void listIteratorNext(ListIterator** itr);
void* listGetIteratorValue(ListIterator* itr);

#endif //JSON_LIST_H
