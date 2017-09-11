
#include <stdio.h>
#include <stdlib.h>
#include "lrsll.h"

void printNode(lrsll_node *n, char *nodePosition) {
    if (n == NULL || n->data == NULL)
        fprintf(stdout, "\nList is empty");
    else
        fprintf(stdout, "\n%s Node value is %s", nodePosition, n->data);
}

void printHead(lrsll_list **list) {
    printNode(lrsll_top(list), "Top");

}

void printTail(lrsll_list **list) {
    printNode(lrsll_tail(list), "Tail");
}

int main() {

    lrsll_list *list = createList();
    printHead(&list);
    printTail(&list);

    lrsll_push(&list, "test");
    printHead(&list);
    printTail(&list);

    lrsll_push(&list, "othertest");
    printHead(&list);
    printTail(&list);

    lrsll_append(&list, "appendTest");
    printHead(&list);
    printTail(&list);

    lrsll_append(&list, "appendTest2");
    printHead(&list);
    printTail(&list);

    char *popped = lrsll_popFront(&list);
    fprintf(stdout, "\nPopped %s", popped);
    free(popped);
    printHead(&list);
    printTail(&list);

    popped = lrsll_popBack(&list);
    fprintf(stdout, "\nPopped %s", popped);
    free(popped);
    printHead(&list);
    printTail(&list);

    lrsll_node *deletedNode = lrsll_delete(&list, "test");
    fprintf(stdout, "\nDeleted %s", deletedNode->data);
    free(deletedNode->data);
    free(deletedNode);

    deletedNode = lrsll_delete(&list, "appendTest");
    if (deletedNode != NULL) {
        fprintf(stdout, "\nDeleted %s", deletedNode->data);
        free(deletedNode->data);
        free(deletedNode);
    }

    deletedNode = lrsll_delete(&list, "appendTest");
    if (deletedNode != NULL) {
        fprintf(stdout, "\nDeleted %s", deletedNode->data);
        free(deletedNode->data);
        free(deletedNode);
    }
    printHead(&list);
    printTail(&list);

    lrsll_addBefore(&list, "addbefore", "beforethis");
    printHead(&list);
    printTail(&list);

    lrsll_addAfter(&list, "addAfter", "beforethis");
    printHead(&list);
    printTail(&list);

    lrsll_push(&list, "beforethis");
    printHead(&list);
    printTail(&list);

    lrsll_addBefore(&list, "addbefore", "beforethis");
    printHead(&list);
    printTail(&list);

    lrsll_addBefore(&list, "beforeaddbefore", "addbefore");
    printHead(&list);
    printTail(&list);

    lrsll_addAfter(&list, "addAfter", "beforethis");
    printHead(&list);
    printTail(&list);


}
