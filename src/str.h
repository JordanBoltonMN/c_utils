#ifndef STR_H
#define STR_H

#include <stdbool.h>

#include "dbl_ll.h"

typedef struct str_find_result {
    struct dbl_ll * root;
    unsigned int look_for_len;
    unsigned int count;
} str_find_result;

str_find_result str_find(const char * str, const char * look_for);

bool str_contains(const char * str, const char * look_for);

bool str_equal(const char * s1, const char * s2);

char * str_copy(const char * str);

bool str_starts_with(const char * str, const char * look_for);
bool str_ends_with(const char * str, const char * look_for);

void str_upper(char * str);
void str_lower(char * str);

#endif
