#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max_level 6

typedef struct Dado{
    char idade[4];
    char sexo[2];
    char cor[21];
    char municipio[31];
    char grupoAtendimento[61];
    char categoria[31];
    char fabricante[31];
    char dose[16];
}Dado;

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
Node* create_node(int level,Dado dado);
void insert_inicio(int key,Dado dado, Skiplist* lista);
void insert(int key, Dado dado, Skiplist *lista);
void print_skiplist(Skiplist* skiplist);
int search(int key, Skiplist *lista);
int remover(int key, Skiplist *lista);

#endif
