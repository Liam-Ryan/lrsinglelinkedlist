#ifndef LRSLL_H
#define LRSLL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct lrsll_node {
    struct lrsll_node *next;
    char *data;
} lrsll_node;

typedef struct lrsll_list {
    lrsll_node *head;
    lrsll_node *tail;
} lrsll_list;

lrsll_list *createList();

lrsll_node *lrsll_push(lrsll_list *list, char *data);

lrsll_node *lrsll_top(lrsll_list *list);

char *lrsll_popFront(lrsll_list *list);

lrsll_node *lrsll_append(lrsll_list *list, char *data);

lrsll_node *lrsll_tail(lrsll_list *list);

char *lrsll_popBack(lrsll_list *list);

lrsll_node *lrsll_find(lrsll_list *list, char *data);

lrsll_node *lrsll_delete(lrsll_list *list, char *data);

bool lrsll_isEmpty(lrsll_list *list);

lrsll_node *lrsll_addBefore(lrsll_list *list, char *item, char *data);

lrsll_node *lrsll_addAfter(lrsll_list *list, char *item, char *data);

void lrsll_printList(lrsll_list *list);

#endif