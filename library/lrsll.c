#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include "lrsll.h"

void printNodeDebug(lrsll_node *node) {
    if (node != NULL)
        fprintf(stdout, "\nNode with data %s has pointer address %p and next pointer is %p", node->data, node,
                node->next);
}

lrsll_node *lrsll_push(lrsll_list *list, char *data) {
    lrsll_node *node = malloc(sizeof(lrsll_node));
    node->data = strdup(data);
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL)
        list->tail = node;
    return node;
};

lrsll_list *createList() {
    lrsll_list *list = malloc(sizeof(lrsll_list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

lrsll_node *lrsll_top(lrsll_list *list) {
    if (list != NULL)
        return list->head;
};

char *lrsll_popFront(lrsll_list *list) {
    if (lrsll_isEmpty(list))
        return NULL;

    lrsll_node *oldHead = list->head;
    list->head = oldHead->next;
    if (list->head == NULL)
        list->tail = NULL;

    char *string = strdup(oldHead->data);
    free(oldHead->data);
    free(oldHead);

    return string;
};

lrsll_node *lrsll_append(lrsll_list *list, char *data) {

    lrsll_node *node = malloc(sizeof(lrsll_node));
    node->data = strdup(data);
    node->next = NULL;
    if (list->tail) {
        list->tail->next = node;
        list->tail = node;
    } else {
        list->tail = node;
        list->head = node;
    }

    return node;
};

lrsll_node *lrsll_tail(lrsll_list *list) {
    if (list != NULL)
        return list->tail;
    return NULL;
};

char *lrsll_popBack(lrsll_list *list) {
    if (lrsll_isEmpty(list))
        return NULL;

    lrsll_node *oldTail = list->tail;
    char *string = strdup(oldTail->data);

    lrsll_node **newTail = &list->head;
    while (oldTail != *newTail && oldTail != (*newTail)->next) {
        newTail = &(*newTail)->next;
    }
    if (oldTail == *newTail) {
        list->tail = NULL;
        list->head = NULL;
    } else {
        list->tail = *newTail;
        list->tail->next = NULL;
    }
    free(oldTail->data);
    free(oldTail);

    return string;
};

lrsll_node *lrsll_find(lrsll_list *list, char *data) {
    if (lrsll_isEmpty(list))
        return NULL;
    lrsll_node *n = list->head;
    while (n && strcmp(n->data, data) != 0) {
        n = n->next;
    }
    return n;
};

lrsll_node *lrsll_delete(lrsll_list *list, char *data) {
    lrsll_node **node = &list->head;
    printNodeDebug(*node);
    while (*node && strcmp((*node)->data, data) != 0) {
        node = &(*node)->next;
        printNodeDebug(*node);
    }
    if (*node == NULL)
        return NULL;

    fprintf(stdout, "\nDeleting node:");
    printNodeDebug(*node);
    lrsll_node *deleted = *node;
    *node = deleted->next;
    fprintf(stdout, "\nSetting new node:");
    printNodeDebug(*node);


    if (deleted == list->tail) {
        /* if node is pointing to head we haven't moved meaning 1 element list so set tail to null
         * Otherwise set tail to the address of the struct that node is currently on. This works because next is the first
         * element declared in the struct so the address of node is the same as the address of node->next, we just need
         * to cast it to an lrsll_node pointer. TODO - reimplement with offsetof macro 
         *
         * Credit to Austin Hastings on SE - https://codereview.stackexchange.com/questions/175398/delete-node-from-singly-linked-list-with-tail-pointer-in-c
         * */
        list->tail = (node == &list->head) ? NULL : (lrsll_node*)node;
    }

    return deleted;
};

bool lrsll_isEmpty(lrsll_list *list) {
    return list == NULL || list->head == NULL;
};

lrsll_node *lrsll_addBefore(lrsll_list *list, char *data, char *item) {
    lrsll_node **node = &list->head;
    while (*node && strcmp((*node)->data, item) != 0) {
        node = &(*node)->next;
    }

    if (*node == NULL)
        return *node;

    lrsll_node *newNode = malloc(sizeof(lrsll_node));
    newNode->data = strdup(data);
    newNode->next = (*node);
    *node = newNode;
    return newNode;

};

lrsll_node *lrsll_addAfter(lrsll_list *list, char *data, char *item) {
    lrsll_node **node = &list->head;
    while (*node && strcmp((*node)->data, item) != 0) {
        node = &(*node)->next;
    }

    if (*node == NULL)
        return *node;

    lrsll_node *newNode = malloc(sizeof(lrsll_node));
    newNode->data = strdup(data);
    newNode->next = (*node)->next;
    (*node)->next = newNode;
    if (newNode->next == NULL)
        list->tail = newNode;
    return newNode;
};