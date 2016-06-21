#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "macros.c"
#include "../src/dbl_ll.h"

void free_int_dbl_ll(dbl_ll * node) {
    if (node->key != node->data) {
        free(node->key);
        free(node->data);
    } else {
        free(node->key);
    }
    free(node);
}

void free_all_int_dbl_ll(dbl_ll * node) {
    dbl_ll * next = NULL;

    while (node != NULL) {
        next = node->next;
        free_int_dbl_ll(node);
        node = next;
    }
}


int int_dbl_cmp_key(const void * key1, const void * key2) {
    int * ptr1 = (int *) key1;
    int * ptr2 = (int *) key2;
    return *ptr1 - *ptr2;
}


struct dbl_ll * int_create_node(unsigned int n) {
    int * key_and_data = malloc(sizeof(int));
    *key_and_data = n;
    return dbl_ll_create(key_and_data, key_and_data, NULL, NULL);
}


struct dbl_ll * create_chain(unsigned int n) {
    struct dbl_ll * root = NULL;
    struct dbl_ll * node = NULL;
    for (unsigned int i=0; i<n; i++) {
        node = int_create_node(i);
        root = dbl_ll_insert(root, node);
    }

    return root;
}


void test_create() {
    int * key = (int *) malloc(sizeof(int));
    int * data = (int *) malloc(sizeof(int));

    *key = 2;
    *data = 42;

    struct dbl_ll * node = dbl_ll_create(key, data, NULL, NULL);

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
    dbl_ll * node2 = dbl_ll_create(key2, data2, NULL, NULL);

    root = dbl_ll_insert(root, node1);

    test_pointer(root, node1);
    test_pointer(node1->prev, NULL);
    test_pointer(node1->next, NULL);

    dbl_ll_insert(root, node2);

    test_pointer(root, node1);
    test_pointer(node1->next, node2);
    test_pointer(node2->prev, node1);
    test_pointer(node2->next, NULL);

    free_all_int_dbl_ll(root);
}


void test_delete1() {
    dbl_ll * root = NULL;
    dbl_ll * node1 = int_create_node(0);
    dbl_ll * node2 = int_create_node(1);
    dbl_ll * node3 = int_create_node(2);

    root = dbl_ll_insert(root, node1);
    root = dbl_ll_insert(root, node2);
    root = dbl_ll_insert(root, node3);

    test_pointer(root, node1);
    test_pointer(root->next, node2);
    test_pointer(root->next->next, node3);

    int * target_key = malloc(sizeof(int));
    *target_key = 1;
    const void * p = (void *) target_key;

    struct dbl_ll_del result = dbl_ll_delete(
        root,
        p,
        &int_dbl_cmp_key,
        &free_int_dbl_ll
    );
    dbl_ll * new_root = result.root;

    test_int(result.deleted, 1);
    test_pointer(new_root, node1);
    test_pointer(new_root->prev, NULL);
    test_pointer(new_root->next, node3);
    test_pointer(new_root->next->prev, new_root);

    free_all_int_dbl_ll(root);
    free(target_key);
}


void test_delete2() {
    dbl_ll * root = NULL;
    dbl_ll * node1 = int_create_node(0);
    int * target_key = malloc(sizeof(int));
    *target_key = 0;

    root = dbl_ll_insert(root, node1);
    test_pointer(root, node1);

    dbl_ll_del result = dbl_ll_delete(
        root,
        target_key,
        &int_dbl_cmp_key,
        &free_int_dbl_ll
    );

    test_int(result.deleted, 1);
    test_pointer(result.root, NULL);

    free(target_key);
}


void test_delete3() {
    dbl_ll * root = NULL;
    dbl_ll * node1 = int_create_node(0);
    int * target_key = malloc(sizeof(int));
    *target_key = -1;

    root = dbl_ll_insert(root, node1);
    test_pointer(root, node1);

    dbl_ll_del result = dbl_ll_delete(
        root,
        target_key,
        &int_dbl_cmp_key,
        &free_int_dbl_ll
    );

    test_int(result.deleted, 0);
    test_pointer(result.root, root);

    free_all_int_dbl_ll(root);
    free(target_key);
}


void test_has1() {
    int * bad_key = malloc(sizeof(int));
    *bad_key = 42;

    test_int(dbl_ll_has(NULL, NULL, &int_dbl_cmp_key), false);
    test_int(dbl_ll_has(NULL, bad_key, &int_dbl_cmp_key), false);

    free(bad_key);
}


void test_has2() {
    dbl_ll * root = create_chain(10);
    int * bad_key1 = malloc(sizeof(int));
    int * bad_key2 = malloc(sizeof(int));
    *bad_key1 = -1;
    *bad_key2 = 10;

    test_int(dbl_ll_has(root, (void *) bad_key1, &int_dbl_cmp_key), false);
    test_int(dbl_ll_has(root, (void *) bad_key2, &int_dbl_cmp_key), false);

    free(bad_key1);
    free(bad_key2);
    free_all_int_dbl_ll(root);
}


void test_has3() {
    dbl_ll * root = create_chain(10);
    int * good_key1 = malloc(sizeof(int));
    int * good_key2 = malloc(sizeof(int));
    *good_key1 = 0;
    *good_key2 = 9;

    test_int(dbl_ll_has(root, (void *) good_key1, &int_dbl_cmp_key), true);
    test_int(dbl_ll_has(root, (void *) good_key2, &int_dbl_cmp_key), true);

    free(good_key1);
    free(good_key2);
    free_all_int_dbl_ll(root);
}



int main() {
    printf("Starting test_dbl_ll.c\n");
    test_create();
    test_insert();
    test_delete1();
    test_delete2();
    test_delete3();
    test_has1();
    test_has2();
    test_has3();
    printf("Done with test_dbl_ll.c\n");
    return 0;
}
