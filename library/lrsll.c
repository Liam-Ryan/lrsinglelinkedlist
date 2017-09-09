#include <malloc.h>
#include <mem.h>
#include "lrsll.h"

lrsll_node *lrsll_push(lrsll_list **list, char *data) {
    lrsll_list *listRef = *list;
    if (listRef == NULL) {
        listRef = malloc(sizeof(lrsll_list));
    }

    lrsll_node *node = malloc(sizeof(lrsll_node));
    node->data = strdup(data);
    node->next = listRef->head;
    listRef->head = node;
    if (listRef->tail == NULL)
        listRef->tail = node;
    return node;
};

lrsll_list *createList() {
    lrsll_list *list = malloc(sizeof(lrsll_list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

lrsll_node *lrsll_top(lrsll_list **list) {
    if (list != NULL && *list != NULL)
        return (*list)->head;
};

char *lrsll_popFront(lrsll_list **list) {
    if (list == NULL || *list == NULL || (*list)->head == NULL)
        return NULL;

    lrsll_node *oldHead = (*list)->head;
    (*list)->head = oldHead->next;
    if ((*list)->head == NULL)
        (*list)->tail = NULL;

    char *string = strdup(oldHead->data);
    free(oldHead->data);
    free(oldHead);

    return string;
};

lrsll_node *lrsll_append(lrsll_list **list, char *data){
    lrsll_list *listRef = *list;
    if (listRef == NULL) {
        listRef = malloc(sizeof(lrsll_list));
    }

    lrsll_node *node = malloc(sizeof(lrsll_node));
    node->data = strdup(data);
    node->next = NULL;
    if(listRef->tail) {
        listRef->tail->next = node;
        listRef->tail = node;
    } else {
        listRef->tail = node;
        listRef->head = node;
    }

    return node;
};

lrsll_node *lrsll_tail(lrsll_list **list) {
    if (list != NULL && *list != NULL)
        return (*list)->tail;
};

char *lrsll_popBack(lrsll_list **list) {
    if (list == NULL || *list == NULL || (*list)->tail == NULL)
        return NULL;

    lrsll_node *oldTail = (*list)->tail;
    char *string = strdup(oldTail->data);

    lrsll_node **newTail = &(*list)->head;
    while (oldTail != *newTail && oldTail != (*newTail)->next ) {
        newTail = &(*newTail)->next;
    }
    if (oldTail == *newTail) {
        (*list)->tail = NULL;
        (*list)->head = NULL;
    } else {
        (*list)->tail = *newTail;
    }
    free(oldTail->data);
    free(oldTail);

    return string;
};

lrsll_node *lrsll_find(lrsll_list **list, char *data) {
    if (lrsll_isEmpty( list ))
        return NULL;
    lrsll_node *n = (*list)->head;
    while( n && strcmp(n->data, data) != 0 ) {
        n = n->next;
    }
    return n;
};

lrsll_node *lrsll_delete(lrsll_list **list, char *data){

};

bool lrsll_isEmpty(lrsll_list **list) {
    return list == NULL || *list == NULL || (*list)->head == NULL;
};

lrsll_node *lrsll_addBefore(lrsll_list **list, char *data, char *item);

lrsll_node *lrsll_addAfter(lrsll_list **list, char *data, char *item);