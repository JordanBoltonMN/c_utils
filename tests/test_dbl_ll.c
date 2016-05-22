#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test.c"
#include "../src/dbl_ll.h"

void free_int_dbl_ll(dbl_ll * node) {
    if (node->key != node->data) {
        free(node->key);
        free(node->data);
    } else {
        free(node->key);
    }
}

int int_dbl_cmp_key(void * key1, void * key2) {
    int * ptr1 = (int *) key1;
    int * ptr2 = (int *) key2;
    return *ptr1 - *ptr2;
}

void test_create() {
    int * key = (int *) malloc(sizeof(int));
    int * data = (int *) malloc(sizeof(int));

    *key = 2;
    *data = 42;

    dbl_ll * node = dbl_ll_create(key, data, NULL, NULL);

    test_pointer(node->key, key);
    test_pointer(node->data, data);
    test_pointer(node->next, NULL);
    test_pointer(node->prev, NULL);

    free_int_dbl_ll(node);
}



void test_insert() {
    int * key1 = (int *) malloc(sizeof(int));
    int * data1 = (int *) malloc(sizeof(int));
    int * key2 = (int *) malloc(sizeof(int));
    int * data2 = (int *) malloc(sizeof(int));

    *key1 = 2;
    *data1 = 42;

    *key2 = 32;
    *data2 = 64;

    dbl_ll * root = NULL;
    dbl_ll * node1 = dbl_ll_create(key1, data1, NULL, NULL);
    dbl_ll * node2 = dbl_ll_create(key1, data1, NULL, NULL);

    root = dbl_ll_insert(root, node1);

    test_pointer(root, node1);
    test_pointer(node1->prev, NULL);
    test_pointer(node1->next, NULL);

    dbl_ll_insert(root, node2);

    test_pointer(root, node1);
    test_pointer(node1->next, node2);
    test_pointer(node2->prev, node1);
    test_pointer(node2->next, NULL);

    free_int_dbl_ll(node1);
    free_int_dbl_ll(node2);
}


int main() {
    test_create();
    test_insert();
    // test_delete();

    return 0;
}
