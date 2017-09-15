
#include <stdio.h>
#include <stdlib.h>
#include "lrsll.h"

void printNode(lrsll_node *n, char *nodePosition) {
    if (n == NULL || n->data == NULL)
        fprintf(stdout, "\nList is empty");
    else
        fprintf(stdout, "\n\t%s Node value is %s", nodePosition, n->data);
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

    void printList() {
        lrsll_node *temp = list->head;
        fprintf(stdout, "\nCurrent list - \n");
        while (temp && temp->data) {
            fprintf(stdout, "\t%s", temp->data);
            temp = temp->next;
        }
        fprintf(stdout, "%s", (list->head == temp) ? "\tEmpty" : "\n");
    }

    void printPointers() {
        printHead(list);
        printTail(list);
        printList();
    }

    lrsll_node *add(bool append, char *item) {
        fprintf(stdout, "\n%s %s to the list...", append ? "Appending" : "Pushing", item);
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
        fprintf(stdout, "\n%s element from list...", front ? "Popping" : "Slicing");
        char *returned = front ? lrsll_popFront(list) : lrsll_popBack(list);
        fprintf(stdout, "\n\tRetrieved %s from list", returned ? returned : "nothing");
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

    void delete(char *item) {
        fprintf(stdout, "\nDeleting %s from list...", item);
        lrsll_node *deletedNode = lrsll_delete(list, item);
        if (deletedNode) {
            if (deletedNode->data) {
                fprintf(stdout, "\n\tDeleted %s", deletedNode->data);
                free(deletedNode->data);
            }
            free(deletedNode);
        } else {
            fprintf(stdout, "\n\t%s not found in list", item);
        }
        printPointers();
    }

    void addNextTo(bool after, char *data, char *searchItem) {
        fprintf(stdout, "\nAttempting to add %s %s %s", data, after ? "after" : "before", searchItem);
        lrsll_node *result = after ? lrsll_addAfter(list, data, searchItem) : lrsll_addBefore(list, data, searchItem);
        if (result) {
            if (result->data) {
                fprintf(stdout, "\n\tSuccessfully added %s", data);
            }
        } else {
            fprintf(stdout, "\n\tCouldn't find %s in list", searchItem);
        }
        printPointers();
    }

    void addAfter(char *data, char *searchItem) {
        addNextTo(true, data, searchItem);
    }

    void addBefore(char *data, char *searchItem) {
        addNextTo(false, data, searchItem);
    }

    void info(char *string) {
        fprintf(stdout, "\n%s:\n", string);
    }



    /*End test helper functions*/

    info("Push and append");
    printPointers();
    push("C");
    push("B");
    push("A");
    append("D");
    append("E");

    info("Pop");
    pop();
    info("Slice");
    slice();

    //Deletions
    info("Delete non-existent node");
    delete("Z");
    info("Delete existing nodes from front of list");
    delete("B");
    info("Delete existing nodes from back of list");
    append("E");
    delete("E");
    info("Delete existing nodes from middle of list");
    push("B");
    delete("C");
    info("Delete first node from list with two elements");
    delete("B");
    info("Add node back to front of list");
    push("C");
    info("Delete last node in list with two elements");
    delete("D");
    delete("C");
    info("Delete non-existent node from empty list");
    delete("E");

    //adds
    info("Add before non-existent node in an empty list");
    addBefore("C", "A");
    info("Add after non-existent node in an empty list");
    addAfter("C", "A");
    push("B");
    info("Add before non-existent node in a 1 element list");
    addBefore("C", "F");
    info("Add after non-existent node in a 1 element list");
    addAfter("C", "F");
    push("A");
    info("Add before non-existent node in a > 1 element list");
    addBefore("C", "F");
    info("Add after non-existent node in a > 1 element list");
    addAfter("C", "F");
    pop();
    info("Add before node in a 1 element list");
    addBefore("B", "A");
    pop();
    info("Add after node in a 1 element list");
    addAfter("B", "C");
    push("A");
    info("Add after node in a > 1 element list");
    addBefore("B", "A1");
    info("Add before node in a > 1 element list");
    addAfter("B", "B1");
    info("Add before head node in a list");
    addBefore("A", "A-");
    info("Add after tail node in a list");
    addAfter("C", "D");


}
