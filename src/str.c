#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "str.h"

#ifndef DBL_LL_H
#define DBL_LL_H
    #include "dbl_ll.h"
#endif


struct str_find_result str_find(char * str, char * look_for) {
    struct str_find_result result;
    result.root = NULL;
    result.look_for_len = strlen(look_for);
    result.count = 0;

    if (result.look_for_len == 0) {
        return result;
    }

    char * iter = strstr(str, look_for);
    while (iter != NULL) {
        char ** start_of_match = (char **) malloc(sizeof(char **));
        *start_of_match = iter;
        struct dbl_ll * node = dbl_ll_create(
            (void *) start_of_match,
            (void *) start_of_match,
            NULL,
            NULL
        );

        result.root = dbl_ll_insert_right(result.root, node);
        result.count++;

        iter += result.look_for_len;
        iter = strstr(iter, look_for);
    }

    return result;
}


void free_str_find_result(struct str_find_result result) {
    struct dbl_ll * current = result.root;
    struct dbl_ll * next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}


bool str_contains(char * str, char * look_for) {
    struct str_find_result result = str_find(str, look_for);
    return result.count > 0;
}


bool str_equal(char * s1, char * s2) {
    return strcmp(s1, s2) == 0;
}


char * str_copy(char * str) {
    size_t len = strlen(str) + 1;
    void * result = malloc(sizeof(char) * len);
    memcpy(result, str, len);
    return (char *) result;
}


bool str_starts_with(char * str, char * look_for) {
    char * ptr1 = str;
    char * ptr2 = look_for;

    while (*ptr2 != '\0') {
        if (*ptr1 == '\0' || *ptr1 != *ptr2) {
            return false;
        }

        ptr1++;
        ptr2++;
    }

    // at least one character was matched
    return str != ptr1;
    return false;
}


bool str_ends_with(char * str, char * look_for) {
    unsigned str_len = 0;
    unsigned look_for_len = 0;

    char * ptr = str;
    while (*ptr != '\0') {
        str_len++;
        ptr++;
    }
    char * str_it = (ptr - 1);

    ptr = look_for;
    while (*ptr != '\0') {
        look_for_len++;
        ptr++;
    }
    char * look_for_it = (ptr - 1);

    if (look_for_len > str_len) {
        return false;
    }

    while (look_for_it >= look_for) {
        if (*str_it != *look_for_it) {
            return false;
        }
        str_it--;
        look_for_it--;
    }

    return true;
}


void str_upper(char * str) {
    while (*str != '\0') {
        if ('a' <= *str || *str <= 'z') {
            *str -= ('a' - 'A');
        }
        str++;
    }
}


void str_lower(char * str) {
    while (*str != '\0') {
        if ('A' <= *str || *str <= 'Z') {
            *str += ('a' - 'A');
        }
        str++;
    }
}
