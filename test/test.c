
#include <stdlib.h>
#include <check.h>
#include "lrsll.h"

lrsll_list *list;

void setup(void) {
    list = lrsll_createList();
}

void teardown(void) {
    lrsll_freeList(list);
}

void doNothing(void) {
    list = NULL;
}

START_TEST(create_list)
    {
        ck_assert_ptr_ne(list, NULL);
    }
END_TEST

START_TEST(free_empty_list_does_not_segfault)
    {
        lrsll_freeList(list);
        ck_assert(true);
    }
END_TEST

START_TEST(free_list_does_not_segfault)
    {
        lrsll_push(list, "A");
        lrsll_freeList(list);
        ck_assert(true);
    }
END_TEST

START_TEST(free_node_does_not_segfault)
    {
        lrsll_node *test = malloc(sizeof(lrsll_node));
        test->data = strdup("a");
        test->next = NULL;
        lrsll_freeNode(test);
        ck_assert(true);
        lrsll_freeList(list);
    }
END_TEST

START_TEST(free_empty_node_does_not_segfault)
    {
        lrsll_freeNode(NULL);
        ck_assert(true);
        lrsll_freeList(list);
    }
END_TEST

START_TEST(push)
    {
        lrsll_push(list, "B");
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "B");
        lrsll_push(list, "A");
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "B");
    }
END_TEST

START_TEST(append)
    {
        lrsll_append(list, "B");
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "B");
        lrsll_append(list, "A");
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "A");
    }
END_TEST

START_TEST(popFront)
    {
        char *returned;
        lrsll_append(list, "A");
        lrsll_append(list, "B");
        lrsll_append(list, "C");

        returned = lrsll_popFront(list);
        ck_assert_str_eq(returned, "A");
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "C");
        free(returned);
        returned = lrsll_popFront(list);
        ck_assert_str_eq(returned, "B");
        ck_assert_str_eq(list->head->data, "C");
        ck_assert_str_eq(list->tail->data, "C");
        free(returned);
        returned = lrsll_popFront(list);
        ck_assert_str_eq(returned, "C");
        ck_assert_ptr_eq(list->head, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
        free(returned);
    }
END_TEST

START_TEST(popBack)
    {
        char *returned;
        lrsll_push(list, "A");
        lrsll_push(list, "B");
        lrsll_push(list, "C");

        returned = lrsll_popBack(list);
        ck_assert_str_eq(returned, "A");
        ck_assert_str_eq(list->head->data, "C");
        ck_assert_str_eq(list->tail->data, "B");
        free(returned);
        returned = lrsll_popBack(list);
        ck_assert_str_eq(returned, "B");
        ck_assert_str_eq(list->head->data, "C");
        ck_assert_str_eq(list->tail->data, "C");
        free(returned);
        returned = lrsll_popBack(list);
        ck_assert_str_eq(returned, "C");
        ck_assert_ptr_eq(list->head, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
        free(returned);
    }
END_TEST

START_TEST(popFront_empty)
    {
        ck_assert_ptr_eq(lrsll_popFront(list), NULL);
        ck_assert_ptr_eq(list->head, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
    }
END_TEST

START_TEST(popBack_empty)
    {
        ck_assert_ptr_eq(lrsll_popFront(list), NULL);
        ck_assert_ptr_eq(list->head, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
    }
END_TEST

START_TEST(delete_from_empty)
    {
        ck_assert_ptr_eq(lrsll_delete(list, "A"), NULL);
        ck_assert_ptr_eq(list->head, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
    }
END_TEST

START_TEST(delete_missing)
    {
        lrsll_push(list, "A");
        ck_assert_ptr_eq(lrsll_delete(list, "B"), NULL);
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "A");
    }
END_TEST

START_TEST(delete_only)
    {
        lrsll_push(list, "A");
        lrsll_node *deleted = lrsll_delete(list, "A");
        ck_assert_ptr_ne(deleted, NULL);
        ck_assert_ptr_eq(list->head, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
        ck_assert_str_eq(deleted->data, "A");
        lrsll_freeNode(deleted);
    }
END_TEST

START_TEST(delete_head_of_two)
    {
        lrsll_push(list, "B");
        lrsll_push(list, "A");
        lrsll_node *deleted = lrsll_delete(list, "A");
        ck_assert_ptr_ne(deleted, NULL);
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "B");
        ck_assert_str_eq(deleted->data, "A");
        lrsll_freeNode(deleted);
    }
END_TEST

START_TEST(delete_tail_of_two)
    {
        lrsll_push(list, "A");
        lrsll_push(list, "B");
        lrsll_node *deleted = lrsll_delete(list, "A");
        ck_assert_ptr_ne(deleted, NULL);
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "B");
        ck_assert_str_eq(deleted->data, "A");
        lrsll_freeNode(deleted);
    }
END_TEST

START_TEST(delete_head_of_three)
    {
        lrsll_push(list, "C");
        lrsll_push(list, "B");
        lrsll_push(list, "A");
        lrsll_node *deleted = lrsll_delete(list, "A");
        ck_assert_ptr_ne(deleted, NULL);
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "C");
        ck_assert_str_eq(deleted->data, "A");
        lrsll_freeNode(deleted);
    }
END_TEST

START_TEST(delete_middle_of_three)
    {
        lrsll_push(list, "C");
        lrsll_push(list, "B");
        lrsll_push(list, "A");
        lrsll_node *deleted = lrsll_delete(list, "B");
        ck_assert_ptr_ne(deleted, NULL);
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "C");
        ck_assert_str_eq(deleted->data, "B");
        lrsll_freeNode(deleted);
    }
END_TEST

START_TEST(delete_tail_of_three)
    {
        lrsll_push(list, "C");
        lrsll_push(list, "B");
        lrsll_push(list, "A");
        lrsll_node *deleted = lrsll_delete(list, "C");
        ck_assert_ptr_ne(deleted, NULL);
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "B");
        ck_assert_str_eq(deleted->data, "C");
        lrsll_freeNode(deleted);
    }
END_TEST

START_TEST(add_before_empty)
    {
        ck_assert_ptr_eq(lrsll_addBefore(list, "A", "B"), NULL);
        ck_assert_ptr_eq(list->head, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
    }
END_TEST

START_TEST(add_after_empty)
    {
        ck_assert_ptr_eq(lrsll_addAfter(list, "A", "B"), NULL);
        ck_assert_ptr_eq(list->head, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
    }
END_TEST

START_TEST(add_before_missing_length_1)
    {
        lrsll_push(list, "C");
        ck_assert_ptr_eq(lrsll_addBefore(list, "A", "B"), NULL);
        ck_assert_str_eq(list->head->data, "C");
        ck_assert_str_eq(list->tail->data, "C");
    }
END_TEST

START_TEST(add_after_missing_length_1)
    {
        lrsll_push(list, "C");

        ck_assert_ptr_eq(lrsll_addAfter(list, "A", "B"), NULL);
        ck_assert_str_eq(list->head->data, "C");
        ck_assert_str_eq(list->tail->data, "C");
    }
END_TEST

START_TEST(add_after_missing)
    {
        lrsll_push(list, "C");
        lrsll_push(list, "B");
        ck_assert_ptr_eq(lrsll_addAfter(list, "D", "F"), NULL);
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "C");
    }
END_TEST

START_TEST(add_before_missing)
    {
        lrsll_push(list, "C");
        lrsll_push(list, "B");
        ck_assert_ptr_eq(lrsll_addBefore(list, "D", "F"), NULL);
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "C");
    }
END_TEST

START_TEST(add_before_length_1)
    {
        lrsll_push(list, "A");
        ck_assert_ptr_ne(lrsll_addBefore(list, "A", "B"), NULL);
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "A");
    }
END_TEST

START_TEST(add_after_length_1)
    {
        lrsll_push(list, "A");
        ck_assert_ptr_ne(lrsll_addAfter(list, "A", "B"), NULL);
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "B");
    }
END_TEST

START_TEST(add_before)
    {
        lrsll_push(list, "A");
        lrsll_append(list, "B");
        lrsll_append(list, "C");
        ck_assert_ptr_ne(lrsll_addBefore(list, "B", "Z"), NULL);
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "C");
        free(lrsll_popBack(list));
        ck_assert_str_eq(list->tail->data, "B");
        free(lrsll_popFront(list));
        ck_assert_str_eq(list->head->data, "Z");
    }
END_TEST

START_TEST(add_after)
    {
        lrsll_push(list, "A");
        lrsll_append(list, "B");
        lrsll_append(list, "C");
        ck_assert_ptr_ne(lrsll_addAfter(list, "B", "Z"), NULL);
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "C");
        free(lrsll_popBack(list));
        ck_assert_str_eq(list->tail->data, "Z");
        free(lrsll_popFront(list));
        ck_assert_str_eq(list->head->data, "B");
    }
END_TEST

START_TEST(search_first)
    {
        lrsll_push(list, "A");
        lrsll_node *found = lrsll_find(list, "A");
        ck_assert_ptr_ne(found, NULL);
        ck_assert_str_eq(found->data, "A");
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "A");
    }
END_TEST

START_TEST(search_last)
    {
        lrsll_push(list, "B");
        lrsll_push(list, "A");
        lrsll_node *found = lrsll_find(list, "A");
        ck_assert_ptr_ne(found, NULL);
        ck_assert_str_eq(found->data, "A");
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "B");
    }
END_TEST

START_TEST(search_middle)
    {
        lrsll_push(list, "C");
        lrsll_push(list, "A");
        lrsll_push(list, "B");
        lrsll_node *found = lrsll_find(list, "A");
        ck_assert_ptr_ne(found, NULL);
        ck_assert_str_eq(found->data, "A");
        ck_assert_str_eq(list->head->data, "B");
        ck_assert_str_eq(list->tail->data, "C");
    }
END_TEST

START_TEST(search_missing)
    {
        lrsll_push(list, "A");
        lrsll_node *found = lrsll_find(list, "B");
        ck_assert_ptr_eq(found, NULL);
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "A");
    }
END_TEST

START_TEST(search_empty)
    {
        lrsll_node *found = lrsll_find(list, "A");
        ck_assert_ptr_eq(found, NULL);
        ck_assert_ptr_eq(list->head, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
    }
END_TEST

START_TEST(top)
    {
        lrsll_push(list, "A");
        lrsll_node *top = lrsll_top(list);
        ck_assert_ptr_ne(top, NULL);
        ck_assert_str_eq(top->data, "A");
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "A");
    }
END_TEST

START_TEST(tail)
    {
        lrsll_push(list, "A");
        lrsll_node *tail = lrsll_tail(list);
        ck_assert_ptr_ne(tail, NULL);
        ck_assert_str_eq(tail->data, "A");
        ck_assert_str_eq(list->head->data, "A");
        ck_assert_str_eq(list->tail->data, "A");
    }
END_TEST

START_TEST(top_empty)
    {
        lrsll_node *top = lrsll_top(list);
        ck_assert_ptr_eq(top, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
        ck_assert_ptr_eq(list->head, NULL);
    }
END_TEST

START_TEST(tail_empty)
    {
        lrsll_node *tail = lrsll_tail(list);
        ck_assert_ptr_eq(tail, NULL);
        ck_assert_ptr_eq(list->tail, NULL);
        ck_assert_ptr_eq(list->head, NULL);
    }
END_TEST


Suite *list_suite(void) {
    Suite *s = suite_create("Single Linked List");

    TCase *tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, create_list);
    suite_add_tcase(s, tc_core);

    TCase *tc_pushPop = tcase_create("Push/Pop");
    tcase_add_checked_fixture(tc_pushPop, setup, teardown);
    tcase_add_test(tc_pushPop, push);
    tcase_add_test(tc_pushPop, append);
    tcase_add_test(tc_pushPop, popFront);
    tcase_add_test(tc_pushPop, popBack);
    tcase_add_test(tc_pushPop, popFront_empty);
    tcase_add_test(tc_pushPop, popBack_empty);
    suite_add_tcase(s, tc_pushPop);

    TCase *tc_free = tcase_create("Free");
    tcase_add_checked_fixture(tc_free, setup, doNothing);
    tcase_add_test(tc_free, free_list_does_not_segfault);
    tcase_add_test(tc_free, free_empty_list_does_not_segfault);
    tcase_add_test(tc_free, free_node_does_not_segfault);
    tcase_add_test(tc_free, free_empty_node_does_not_segfault);
    suite_add_tcase(s, tc_free);

    TCase *tc_delete = tcase_create("Delete");
    tcase_add_checked_fixture(tc_delete, setup, teardown);
    tcase_add_test(tc_core, delete_from_empty);
    tcase_add_test(tc_core, delete_missing);
    tcase_add_test(tc_core, delete_only);
    tcase_add_test(tc_core, delete_head_of_two);
    tcase_add_test(tc_core, delete_tail_of_two);
    tcase_add_test(tc_core, delete_head_of_three);
    tcase_add_test(tc_core, delete_middle_of_three);
    tcase_add_test(tc_core, delete_tail_of_three);
    suite_add_tcase(s, tc_delete);

    TCase *tc_add = tcase_create("Add");
    tcase_add_checked_fixture(tc_add, setup, teardown);
    tcase_add_test(tc_core, add_before_empty);
    tcase_add_test(tc_core, add_after_empty);
    tcase_add_test(tc_core, add_after_missing);
    tcase_add_test(tc_core, add_before_missing);
    tcase_add_test(tc_core, add_before_missing_length_1);
    tcase_add_test(tc_core, add_after_missing_length_1);
    tcase_add_test(tc_core, add_before_length_1);
    tcase_add_test(tc_core, add_after_length_1);
    tcase_add_test(tc_core, add_before);
    tcase_add_test(tc_core, add_after);
    suite_add_tcase(s, tc_add);

    TCase *tc_search = tcase_create("Search");
    tcase_add_checked_fixture(tc_search, setup, teardown);
    tcase_add_test(tc_core, search_first);
    tcase_add_test(tc_core, search_last);
    tcase_add_test(tc_core, search_middle);
    tcase_add_test(tc_core, search_missing);
    tcase_add_test(tc_core, search_empty);
    suite_add_tcase(s, tc_search);

    TCase *tc_topTail = tcase_create("Top/Tail");
    tcase_add_checked_fixture(tc_topTail, setup, teardown);
    tcase_add_test(tc_core, top);
    tcase_add_test(tc_core, tail);
    tcase_add_test(tc_core, top_empty);
    tcase_add_test(tc_core, tail_empty);
    suite_add_tcase(s, tc_topTail);

    return s;
}

int main() {

    int number_failed;
    Suite *s;
    SRunner *sr;

    s = list_suite();
    sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return number_failed < 1 ? EXIT_SUCCESS : EXIT_FAILURE;
}
