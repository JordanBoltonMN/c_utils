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

    if (result.look_for_len == 0) {
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


bool str_contains(const char * str, const char * look_for) {
    struct str_find_result result = str_find(str, look_for);
    return result.count > 0;
}


bool str_equal(const char * s1, const char * s2) {
    return strcmp(s1, s2) == 0;
}


char * str_copy(const char * str) {
    size_t len = strlen(str) + 1;
    void * result = malloc(sizeof(char) * len);
    memcpy(result, str, len);
    return (char *) result;
}


bool str_starts_with(const char * str, const char * look_for) {
    const char * ptr1 = str;
    const char * ptr2 = look_for;

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


bool str_ends_with(const char * str, const char * look_for) {
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
