#include "test.c"
#include "str.h"

void test_find() {
    char str1[] = "abc";
    char str2[] = "aaa";

    testInt(str_find_n(str1, 'a', 1), 0);
    testInt(str_find_n(str1, 'b', 1), 1);
    testInt(str_find_n(str1, 'c', 1), 2);
    testInt(str_find_n(str1, '!', 1), -1);
    testInt(str_find_n(str1, 'a', 0), -1);
    testInt(str_find_n(str1, 'a', 2), -1);

    testInt(str_find_n(str2, 'a', 1), 0);
    testInt(str_find_n(str2, 'a', 2), 1);
    testInt(str_find_n(str2, 'a', 3), 2);
    testInt(str_find_n(str2, 'a', 4), -1);
}

void test_starts_with() {
    char str1[] = "abc";
    char str2[] = "aaa";

    testInt(str_starts_with(str1, 'a'), true);
    testInt(str_starts_with(str1, 'ab'), true);
    testInt(str_starts_with(str1, 'abc'), true);
    testInt(str_starts_with(str1, 'abcd'), false);
}


int main() {
    test_find();
    test_starts_with();

    return 0;
}
