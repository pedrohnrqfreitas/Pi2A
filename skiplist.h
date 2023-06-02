#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max_level 16

typedef struct Node{
    int key;
    struct Node* next[max_level];
} Node;

typedef struct skiplist{
    int level;
    Node* inicio[max_level];
} Skiplist;

int rand_level();
Skiplist* create_skiplist();
Node* create_node(int level);
void insert_inicio(int key, Skiplist* lista);
void insert(int key, Skiplist *lista);
void print_skiplist(Skiplist* skiplist);
int search(int key, Skiplist *lista);
int remover(int key, Skiplist *lista);

#endif
