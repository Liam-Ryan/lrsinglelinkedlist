#include <stdlib.h>
#include <check.h>
#include <lrsll.h>
#include <malloc.h>

START_TEST(test_create_list)
{
    lrsll_list *list;
    list = lrsll_createList();
    ck_assert_int_eq(0, 1);
    free(list);
}
END_TEST

Suite * money_suite(void)
{
	Suite *s;
	TCase *tc_core;
	s = suite_create("List");
	/* Core test case */
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_create_list);
	suite_add_tcase(s, tc_core);
	return s;
}

int main(void)
{
	    int number_failed;
	    Suite *s;
	    SRunner *sr;

	    s = money_suite();
	    sr = srunner_create(s);

	    srunner_run_all(sr, CK_NORMAL);
	    number_failed = srunner_ntests_failed(sr);
	    srunner_free(sr);
	    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
