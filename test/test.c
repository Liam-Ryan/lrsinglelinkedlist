
#include <stdio.h>
#include <stdlib.h>
#include "lrsll.h"

void printNode(lrsll_node *n, char *nodePosition) {
    if (n == NULL || n->data == NULL)
        fprintf(stdout, "\nList is empty");
    else
        fprintf(stdout, "\n%s Node value is %s", nodePosition, n->data);
}

void printHead(lrsll_list *list) {
    printNode(lrsll_top(list), "Top");

}

void printTail(lrsll_list *list) {
    printNode(lrsll_tail(list), "Tail");
}


int main() {
    lrsll_list *list = createList();

    /* Start test helper functions */

    void printPointers() {
        printHead(list);
        printTail(list);
    }

    lrsll_node *add(bool append, char *item) {
        fprintf(stdout, "\n\t%s %s to the list...", append ? "Appending" : "Pushing", item);
        lrsll_node *result = append ? lrsll_append(list, item) : lrsll_push(list, item);
        printPointers();
        return result;
    }

    lrsll_node *push(char *item) {
        return add(false, item);
    }

    lrsll_node *append(char *item) {
        return add(true, item);
    }

    void *retrieve(bool front) {
        fprintf(stdout, "\n\t%s element from list...", front ? "Popping" : "Slicing");
        char *returned = front ? lrsll_popFront(list) : lrsll_popBack(list);
        fprintf(stdout, "\nRetrieved %s from list", returned ? returned : "nothing");
        if (returned)
            free(returned);
        printPointers();
    }

    char *pop() {
        retrieve(true);
    }

    char *slice() {
        retrieve(false);
    }

    void delete(char* item) {
        fprintf(stdout, "\n\tDeleting %s from list...", item);
        lrsll_node *deletedNode = lrsll_delete(list, item);
        if(deletedNode) {
            if (deletedNode->data) {
                fprintf(stdout, "\nDeleted %s", deletedNode->data);
                free(deletedNode->data);
            }
            free(deletedNode);
        } else {
            fprintf(stdout, "\n%s not found in list", item);
        }
    }

    void addNextTo(bool after, char *data, char* searchItem) {
        fprintf(stdout, "\n\tAttempting to add %s %s %s", data, after ? "after" : "before", searchItem);
        lrsll_node *result = after ? lrsll_addAfter(list, data, searchItem) : lrsll_addBefore(list, data, searchItem);
        if( result ) {
            if( result->data) {
                fprintf(stdout, "\nSuccessfully added %s", data);
            }
        } else {
            fprintf(stdout, "\nCouldn't find %s in list", searchItem);
        }
        printPointers();
    }

    void addAfter( char *data, char* searchItem) {
        addNextTo(true, data, searchItem);
    }

    void addBefore(char *data, char* searchItem) {
        addNextTo(false, data, searchItem);
    }

    /*End test helper functions*/

    printPointers();
    push("C");
    push("B");
    push("A");
    append("D");
    append("E");

    pop();
    slice();
    delete("Z");
    delete("B");
    delete("C");
    delete("D");
    delete("E");


    addBefore("C", "A");
    addAfter("B", "A");

    push("C");
    addBefore("B", "C");
    addBefore("A", "B");
    addAfter("D", "C");


}
