
#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "lrsll.h"


void printNode(lrsll_node *n, char *nodePosition) {
    if (n == NULL || n->data == NULL)
        fprintf(stdout, "\n\t%s is NULL", nodePosition);
    else
        fprintf(stdout, "\n\t%s Node value is %s", nodePosition, n->data);
}

void printHead(lrsll_list *list) {
    printNode(lrsll_top(list), "Top");

}

void printTail(lrsll_list *list) {
    printNode(lrsll_tail(list), "Tail");
}

void info(char *string) {
    fprintf(stdout, "\n---------------------------------\n\n%s:\n", string);
}


START_TEST(test_list_create)
    {
        lrsll_list *list;
        list = lrsll_createList();
        ck_assert_int_eq(1, 2);
        free(list);
    }
END_TEST

int main() {
    lrsll_list *list = lrsll_createList();

    /* Start test helper functions */

    void printList() {
        lrsll_printList(list);
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
        lrsll_node *result = after ? lrsll_addAfter(list, searchItem, data) : lrsll_addBefore(list, searchItem, data);
        if (result) {
            if (result->data) {
                fprintf(stdout, "\n\tSuccessfully added %s", data);
            }
        } else {
            fprintf(stdout, "\n\tCouldn't find %s in list", searchItem);
        }
        printPointers();
    }

    void addAfter(char *searchItem, char *data) {
        addNextTo(true, data, searchItem);
    }

    void addBefore(char *searchItem, char *data) {
        addNextTo(false, data, searchItem);
    }

    void find(char *searchItem) {
        lrsll_node *result= lrsll_find( list, searchItem);
        if(result && result->data) {
            fprintf(stdout, "\n\tFound node %s", result->data);
        } else {
            fprintf(stdout, "\n\tCouldn't find %s", searchItem);
        }
        printPointers();
    }



    /*End test helper functions*/

    info("Push and append");
    printPointers();
    info("Push C");
    push("C");
    info("Push B");
    push("B");
    info("Push A");
    push("A");
    info("Append D");
    append("D");
    info("Append E");
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
    info("Append E for next test");
    append("E");
    info("Delete existing nodes from back of list");
    delete("E");
    info("Push B for next test");
    push("B");
    info("Delete existing nodes from middle of list");
    delete("C");
    info("Delete first node from list with two elements");
    delete("B");
    info("Add node back to front of list");
    push("C");
    info("Delete D for next test");
    delete("D");
    info("Delete last node in list with two elements");
    delete("C");
    info("Delete non-existent node from empty list");
    delete("E");

    //adds
    info("Add before non-existent node in an empty list");
    addBefore("C", "A");
    info("Add after non-existent node in an empty list");
    addAfter("C", "A");
    info("Push B for next test");
    push("B");
    info("Add before non-existent node in a 1 element list");
    addBefore("C", "F");
    info("Add after non-existent node in a 1 element list");
    addAfter("C", "F");
    info("Push A for next test");
    push("A");
    info("Add before non-existent node in a > 1 element list");
    addBefore("C", "F");
    info("Add after non-existent node in a > 1 element list");
    addAfter("C", "F");
    info("Pop for next test");
    pop();
    info("Add before node in a 1 element list");
    addBefore("B", "A");
    info("Pop for next test");
    pop();
    info("Add after node in a 1 element list");
    addAfter("B", "C");
    info("Push A for next test");
    push("A");
    info("Add before node in a > 1 element list");
    addBefore("B", "A1");
    info("Add after node in a > 1 element list");
    addAfter("B", "B1");
    info("Add before head node in a list");
    addBefore("A", "A-");
    info("Add after tail node in a list");
    addAfter("C", "D");

    //search
    info("Find first node");
    find("A-");
    info("Find last node");
    find("D");
    info("Find middle node");
    find("B");
    info("Find non-existent node");
    find("Nope");
    info("Empty list in preparation for find in empty list");
    while(list->head) {
        pop();
    }
    info("Find in empty list");
    find("A");
    return 0;
}
