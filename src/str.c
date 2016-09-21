#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "str.h"
#include "dbl_ll.h"

struct str_find_result str_find(const char * str, const char * look_for) {
    struct str_find_result result;
    result.root = NULL;
    result.look_for_len = -1;
    result.count = -1;

    if (str == NULL || look_for == NULL) {
        return result;
    } else {
        result.look_for_len = strlen(look_for);
        result.count = 0;
    }

    if (result.look_for_len == 0) {
        return result;
    }

    const char * iter = strstr(str, look_for);
    while (iter != NULL) {
        const char ** start_of_match = (const char **) malloc(sizeof(char *));
        *start_of_match = iter;
        struct dbl_ll * node = dbl_ll_create(
            (void *) start_of_match,
            (void *) start_of_match,
            NULL,
            NULL
        );

        result.root = dbl_ll_insert(result.root, node);
        result.count++;

        iter += result.look_for_len;
        iter = strstr(iter, look_for);
    }

    return result;
}


bool str_contains(const char * str, const char * look_for) {
    return strstr(str, look_for) != NULL;
}


bool str_equal(const char * s1, const char * s2) {
    return strcmp(s1, s2) == 0;
}


char * str_copy(const char * str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str) + 1;
    char * result = (char *) malloc(sizeof(char) * len);
    memcpy(result, str, len);
    return result;
}


bool str_starts_with(const char * str, const char * look_for) {
    if (str == NULL || look_for == NULL) {
        return false;
    }

    return strstr(str, look_for) == str;
}


bool str_ends_with(const char * str, const char * look_for) {
    if (str == NULL || look_for == NULL) {
        return false;
    }

    size_t len1 = strlen(str);
    size_t len2 = strlen(look_for);
    if (len2 > len1) {
        return false;
    }

    const char * start = str + (len1 - len2);
    return strstr(start, look_for) != NULL;
}


void str_upper(char * str) {
    if (str == NULL) {
        return;
    }

    while (*str != '\0') {
        if ('a' <= *str || *str <= 'z') {
            *str -= ('a' - 'A');
        }
        str++;
    }
}


void str_lower(char * str) {
    if (str == NULL) {
        return;
    }

    while (*str != '\0') {
        if ('A' <= *str || *str <= 'Z') {
            *str += ('a' - 'A');
        }
        str++;
    }
}
