#include <stdio.h>
#include <string.h>

#include "test.c"
#include "../src/str.h"


void test_find() {
    char str1[] = "abc";
    char str2[] = "aaa";

    test_int(str_find_n(str1, 'a', 1), 0);
    test_int(str_find_n(str1, 'b', 1), 1);
    test_int(str_find_n(str1, 'c', 1), 2);
    test_int(str_find_n(str1, '!', 1), -1);
    test_int(str_find_n(str1, 'a', 0), -1);
    test_int(str_find_n(str1, 'a', 2), -1);

    test_int(str_find_n(str2, 'a', 1), 0);
    test_int(str_find_n(str2, 'a', 2), 1);
    test_int(str_find_n(str2, 'a', 3), 2);
    test_int(str_find_n(str2, 'a', 4), -1);
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
    test_find();
    test_starts_with();
    test_ends_with();
    test_upper();
    test_lower();

    return 0;
}
