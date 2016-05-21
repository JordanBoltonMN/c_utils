#include <stdio.h>

#define testInt(VALUE, EXPECTED) \
do { \
    if (VALUE != EXPECTED) { \
        fprintf(stderr, "File %s on line %d: found %d but expected %d\n", __FILE__, __LINE__, VALUE, EXPECTED); \
    } \
} while (0);
