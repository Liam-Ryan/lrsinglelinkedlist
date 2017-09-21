#include <malloc.h>
#include <string.h>
#include "lrsll.h"


void lrsll_freeList(lrsll_list *list) {
    if (!list)
        return;

    lrsll_node *currentNode = list->head;
    while (currentNode != NULL) {
        lrsll_node *delete = currentNode;
        currentNode = currentNode->next;
        lrsll_freeNode(delete);
    }
    free(list);
}

void lrsll_freeNode(lrsll_node *node) {
    if (!node)
        return;
    if (node->data)
        free(node->data);
    free(node);
}

//TODO implement testing of stdout
void lrsll_printList(lrsll_list *list) {
    lrsll_node *temp = list->head;
    fprintf(stdout, "\nCurrent list - \n");
    while (temp && temp->data) {
        fprintf(stdout, "\t%s", temp->data);
        temp = temp->next;
    }
    fprintf(stdout, "%s", (list->head == temp) ? "\tEmpty" : "\n");
}

lrsll_list *lrsll_createList() {
    lrsll_list *list = malloc(sizeof(lrsll_list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

//TODO investigate overloading in C
lrsll_node *lrsll_createNode(char *data, lrsll_node *next) {
    if (data == NULL || strlen(data) < 0)
        return NULL;
    lrsll_node *node = malloc(sizeof(lrsll_node));
    node->data = strdup(data);
    node->next = next;
    return node;
}

lrsll_node *lrsll_push(lrsll_list *list, char *data) {
    lrsll_node *node = lrsll_createNode(data, list->head);
    if (!node)
        return NULL;

    list->head = node;
    if (list->tail == NULL)
        list->tail = node;
    return node;
};

lrsll_node *lrsll_append(lrsll_list *list, char *data) {

    lrsll_node *node = lrsll_createNode(data, NULL);
    if (list->tail) {
        list->tail->next = node;
        list->tail = node;
    } else {
        list->tail = node;
        list->head = node;
    }

    return node;
};

lrsll_node *lrsll_top(lrsll_list *list) {
    if (!lrsll_isEmpty(list))
        return list->head;
    return NULL;
};

lrsll_node *lrsll_tail(lrsll_list *list) {
    if (list != NULL)
        return list->tail;
    return NULL;
};

char *lrsll_popFront(lrsll_list *list) {
    if (lrsll_isEmpty(list))
        return NULL;

    lrsll_node *oldHead = list->head;
    list->head = oldHead->next;
    if (list->head == NULL)
        list->tail = NULL;

    char *string = strdup(oldHead->data);
    lrsll_freeNode(oldHead);
    return string;
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

    lrsll_freeNode(oldTail);
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
    while (*node && strcmp((*node)->data, data) != 0) {
        node = &(*node)->next;
    }
    if (*node == NULL)
        return NULL;
    lrsll_node *deleted = *node;
    *node = deleted->next;


    if (deleted == list->tail) {
        /* if node is pointing to head we haven't moved meaning 1 element list so set tail to null Otherwise set tail to
         * the address of the struct (lrsll_node) that node is currently on. This works because next is the first
         * element declared in the struct so the address of the current node is the same as the address of node.next
         * since the pointer for node.next starts there, we just need to cast it to an lrsll_node pointer.
         * TODO - reimplement with offsetof macro
         *
         * Credit to Austin Hastings on SE -
         * https://codereview.stackexchange.com/questions/175398/delete-node-from-singly-linked-list-with-tail-pointer-in-c
         * */
        list->tail = (node == &list->head) ? NULL : (lrsll_node *) node;
    }

    return deleted;
};

bool lrsll_isEmpty(lrsll_list *list) {
    return list == NULL || list->head == NULL;
};

lrsll_node *lrsll_addBefore(lrsll_list *list, char *item, char *data) {
    lrsll_node **node = &list->head;
    while (*node && strcmp((*node)->data, item) != 0) {
        node = &(*node)->next;
    }

    if (*node == NULL)
        return *node;

    lrsll_node *newNode = lrsll_createNode(data, *node);
    *node = newNode;
    return newNode;

};

lrsll_node *lrsll_addAfter(lrsll_list *list, char *item, char *data) {
    lrsll_node **node = &list->head;
    while (*node && strcmp((*node)->data, item) != 0) {
        node = &(*node)->next;
    }

    if (*node == NULL)
        return *node;

    lrsll_node *newNode = lrsll_createNode(data, (*node)->next);
    (*node)->next = newNode;
    if (newNode->next == NULL)
        list->tail = newNode;
    return newNode;
};