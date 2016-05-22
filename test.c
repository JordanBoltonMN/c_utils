#include <stdio.h>

#define test_value(VALUE, EXPECTED, PRINT_FMT) \
do { \
    if (VALUE != EXPECTED) {\
        fprintf(stderr, "File %s on line %d: found " PRINT_FMT " but expected " PRINT_FMT "\n", __FILE__, __LINE__, VALUE, EXPECTED); \
    } \
} while (0);

#define test_int(VALUE, EXPECTED) test_value(VALUE, EXPECTED, "%d");
#define test_pointer(VALUE, EXPECTED) test_value(VALUE, EXPECTED, "%p");
