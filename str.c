#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

unsigned int str_find(char * str, int c) {
    return str_find_n(str, c, 1);
}

unsigned int str_find_n(char * str, int c, int n) {
    if (n == 0) {
        return -1;
    }

    char * ptr = str;
    char * char_location = NULL;

    while (n > 0) {
        char_location = strchr(ptr, c);
        if (char_location == NULL) {
            return -1;
        }

        ptr = char_location + 1;

        // char_location was the last character in the string
        if (ptr == '\0') {
            return -1;
        }

        n--;
    }

    int index = char_location - str;
    return index;
}

// bool str_starts_with(char * str, char * look_for) {
//     char * ptr1 = str;
//     char * ptr2 = look_for;

//     while (*ptr2 != '\0') {
//         if (*ptr1 == '\0' || *ptr1 != *ptr2) {
//             return false;
//         }

//         ptr1++;
//         ptr2++;
//     }

//     // at least one character was matched
//     return str != ptr1;
// }

// bool str_ends_with(char * str, char * look_for) {
//     return false;
// }

// bool str_contains(char * str, char * look_for) {
//     return false;
// }

// bool str_equal(char * s1, char * s2) {
//     return strcmp(s1, s2) == 0;
// }

char * str_copy(char * str) {
    size_t len = strlen(str) + 1;
    char * result = malloc(sizeof(char) * len);
    memcpy(result, str, len);
    return result;
}

void str_upper(char * str) {
    while (*str != '\0') {
        if ('a' <= *str || *str <= 'z') {
            *str += ('a' - 'A');
        }
        str++;
    }
}
