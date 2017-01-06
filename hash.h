#ifndef HASH_H
#define HASH_H

#include <pthread.h>
#include <stdbool.h>

#define MIN_N 100
#define MAX_N 1000
#define MIN_M 10
#define MAX_M 1000

typedef struct Node{
    int key;
    int value;
    struct Node* next;
}Node;

typedef struct hash_table
{
    int size;
    int region;
    int m_val;
    struct Node **table;
}hash_table;

typedef struct hash_table HashTable;

HashTable* hash_init (int N, int M);
int hash_insert (HashTable *hp, int k, int v);
int hash_delete (HashTable *hp, int k);
int hash_get (HashTable *hp, int k, int *vptr);
int hash_destroy (HashTable *hp);


#endif /* HASH_H */
