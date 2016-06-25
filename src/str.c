#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "str.h"
#include "dbl_ll.h"

struct str_find_result str_find(const char * str, const char * look_for) {
    struct str_find_result result;
    result.root = NULL;
    result.look_for_len = strlen(look_for);
    result.count = 0;

    if (str == NULL || look_for == NULL) {
        return result;
    }

    const char * iter = strstr(str, look_for);
    while (iter != NULL) {
        char ** start_of_match = (char **) malloc(sizeof(char **));
        *start_of_match = (char *) iter;
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
    struct str_find_result result = str_find(str, look_for);
    return result.count > 0;
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

    const char * str_iter = str;

    while (*look_for != '\0') {
        if (*str_iter == '\0' || *str_iter != *look_for) {
            return false;
        }

        str_iter++;
        look_for++;
    }

    // at least one character was matched
    return str != str_iter;
}


bool str_ends_with(const char * str, const char * look_for) {
    if (str == NULL || look_for == NULL) {
        return false;
    }

    unsigned str_len = 0;
    unsigned look_for_len = 0;

    const char * str_iter = str;
    while (*str_iter != '\0') {
        str_iter++;
        str_len++;
    }
    str_iter--;

    const char * look_for_iter = look_for;
    while (*look_for_iter != '\0') {
        look_for_iter++;
        look_for_len++;
    }
    look_for_iter--;

    if (look_for_len > str_len) {
        return false;
    }

    while (look_for_iter >= look_for) {
        if (*str_iter != *look_for_iter) {
            return false;
        }
        str_iter--;
        look_for_iter--;
    }

    return true;
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
