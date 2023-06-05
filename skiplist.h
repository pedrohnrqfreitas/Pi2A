#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max_level 22

typedef struct Dado{
    char *idade;
    char *sexo;
    char *cor;
    char *municipio;
    char *uf;
    char *grupoAtendimento;
    char *categoria;
    char *fabricante;
    char *dose;
}Dado;

typedef struct Node{
    long long int key;
    Dado *dado;
    struct Node* next[max_level];
} Node;

typedef struct skiplist{
    int level;
    Node* inicio[max_level];
} Skiplist;

int rand_level();
Skiplist* create_skiplist();
Node* create_node(int level,Dado *dado);
void insert_inicio(long long int key,Dado *dado, Skiplist* lista);
void insert(long long int key, Dado *dado, Skiplist *lista);
void print_skiplist(Skiplist* skiplist);
int search(long long int key, Skiplist *lista);
int remover(long long int key, Skiplist *lista);

#endif
