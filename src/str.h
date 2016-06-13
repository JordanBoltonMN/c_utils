#include <stdbool.h>

#ifndef DBL_LL_H
#define DBL_LL_H
    #include "dbl_ll.h"
#endif

typedef struct str_find_result {
    struct dbl_ll * root;
    unsigned int look_for_len;
    unsigned int count;
} str_find_result;

str_find_result str_find(char * str, char * look_for);
void free_str_find_result(struct str_find_result result);

bool str_contains(char * str, char * look_for);
bool str_equal(char * s1, char * s2);
char * str_copy(char * str);
bool str_starts_with(char * str, char * look_for);
bool str_ends_with(char * str, char * look_for);
void str_upper(char * str);
void str_lower(char * str);
