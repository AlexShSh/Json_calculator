#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List* listCreate()
{
    List* lst = (List*) malloc(sizeof(List));
    lst->first = lst->last = NULL;
    return lst;
}


void listPushBack(pList lst, void* value)
{
    pListElement new = (pListElement) malloc(sizeof(ListElement));

    new->value = value;
    new->next = NULL;
    new->prev = NULL;

    if (lst->last)
    {
        new->prev = lst->last;
        lst->last->next = new;
        lst->last = new;
    }
    else
    {
        lst->first = lst->last = new;
    }
}


void listDelete(pList* lst)
{
    pListElement current = (*lst)->first;
    while (current)
    {
        pListElement tmp = current->next;
        free(current);
        current = tmp;
    }
    free(*lst);
    *lst = NULL;
}


int listIsEmpty (pList lst)
{
    return lst->first ? 0 : 1;
}


ListIterator* listCreateBeginIterator(List* lst)
{
    ListIterator* itr = (ListIterator*) malloc(sizeof(ListIterator));
    itr->value = lst->first;
    if (itr->value)
        itr->next = itr->value->next;
    else
        itr->next = NULL;

    return itr;
}


void listDeleteIterator(ListIterator** itr)
{
    if (*itr)
        free(*itr);
    *itr = NULL;
}


void listIteratorNext(ListIterator** itr)
{
    (*itr)->value = (*itr)->next;

    if ((*itr)->next)
    {
        (*itr)->next = (*itr)->next->next;
        return;
    }

    listDeleteIterator(itr);
}


void* listGetIteratorValue(ListIterator* itr)
{
    return itr->value->value;
}
