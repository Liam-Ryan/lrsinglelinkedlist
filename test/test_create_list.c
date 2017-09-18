
#include <check.h>
#include <lrsll.h>
#include <malloc.h>

START_TEST(test_create_list)
{
    lrsll_list *list;
    list = lrsll_createList();
    ck_assert_int_eq(0, 2);
    free(list);
}
END_TEST

int main() {
    return 0;
}
