#include <stdio.h>
#include <string.h>

#include "macros.c"
#include "../src/str.h"
// #include "../src/dbl_ll.h"

void test_find1() {
    char str1[] = "";
    char str2[] = "";

    struct str_find_result result = str_find(str1, str2);
    test_int(result.count, 0);

    free_str_find_result(result);
}

void test_find2() {
    char str1[] = "aa";
    char str2[] = "aa";

    struct str_find_result result = str_find(str1, str2);
    struct dbl_ll * root = result.root;

    test_int(result.count, 1);

    char ** match = (char **) root->data;

    test_pointer(str1, *match);

    free_str_find_result(result);
}

void test_find3() {
    char str1[] = "baa";
    char str2[] = "aa";

    struct str_find_result result = str_find(str1, str2);
    struct dbl_ll * root = result.root;

    test_int(result.count, 1);

    char ** match = (char **) root->data;

    test_pointer(str1 + 1, *match);

    free_str_find_result(result);
}

void test_find4() {
    char str1[] = "aaaaa";
    char str2[] = "aa";

    struct str_find_result result = str_find(str1, str2);
    test_int(result.count, 2);

    struct dbl_ll * root = result.root;
    char ** first_match = (char **) root->data;
    char ** second_match = (char **) root->next->data;

    test_pointer(str1, *first_match);
    test_pointer(str1 + strlen(str2), *second_match);

    free_str_find_result(result);
}

void test_starts_with() {
    char str1[] = "abc";

    test_int(str_starts_with(str1, "a"), true);
    test_int(str_starts_with(str1, "ab"), true);
    test_int(str_starts_with(str1, "abc"), true);

    test_int(str_starts_with(str1, "abcd"), false);
    test_int(str_starts_with(str1, "X"), false);
}


void test_ends_with() {
    char str1[] = "qaz";

    test_int(str_ends_with(str1, "z"), true);
    test_int(str_ends_with(str1, "az"), true);
    test_int(str_ends_with(str1, "qaz"), true);

    test_int(str_ends_with(str1, "qqaz"), false);
    test_int(str_ends_with(str1, "X"), false);
}


void test_upper() {
    char str1[] = "abc";
    char str2[] = "aaa";

    str_upper(str1);
    str_upper(str2);

    test_int(strcmp(str1, "ABC"), 0);
    test_int(strcmp(str2, "AAA"), 0);
}


void test_lower() {
    char str1[] = "ABC";
    char str2[] = "AAA";

    str_lower(str1);
    str_lower(str2);

    test_int(strcmp(str1, "abc"), 0);
    test_int(strcmp(str2, "aaa"), 0);
}


int main() {
    printf("Starting test_str.c\n");
    test_find1();
    test_find2();
    test_find3();
    test_find4();
    test_starts_with();
    test_ends_with();
    test_upper();
    test_lower();
    printf("Done with test_str.c\n");

    return 0;
}
