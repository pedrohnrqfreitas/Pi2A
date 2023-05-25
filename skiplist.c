#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//define
#define max_nivel 6

//structs
typedef struct Node{
    int key;
    struct Node* next[max_nivel];
}Node;

typedef struct skiplist{
    int nivel;
    Node* inicio[max_nivel];
}Skiplist;

//funções
int rand_nivel();
Skiplist* create_skiplist();
Node* create_node(int key, int level);
void insert_inicio(int key, Skiplist* lista);
void insert(int key,  Skiplist *lista);
void print_skiplist(Skiplist* skiplist);
int search(int key, Skiplist *lista);

int main(){
    Skiplist* skiplist = create_skiplist();

    //printf("%d\n", rand_nivel());

    insert(5, skiplist);
    insert(4, skiplist);
    insert(3, skiplist);
    insert(2, skiplist);
    insert(1, skiplist);

    print_skiplist(skiplist);

    if(search(5, skiplist)){
        printf("achei\n");
    }

    
}

int rand_nivel() {
    static int initialized = 0;
    int num = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    while(rand() % 2 == 1 && num < max_nivel){
        num++;
    }
    return num;
}

Skiplist* create_skiplist(){
    Skiplist* skiplist = (Skiplist*) malloc(sizeof(Skiplist));
    for(int i = 0; i < max_nivel; i++){
        skiplist->inicio[i] = NULL;
    }
    return skiplist;
}

Node* create_node(int key, int level){
    Node* newnode = (Node*) malloc(sizeof(Node));
    newnode->key = key;
    return newnode;
}

void insert_inicio(int key, Skiplist* lista){
    int level = rand_nivel();
    Node* aux = create_node(key, level);
    lista->nivel = level;
    for(int i = level; i >= 0; i--){
        aux->next[i] = lista->inicio[i];
        lista->inicio[i] = aux;
    }
}

void insert(int key, Skiplist *lista) {
    if (lista->inicio[0] == NULL) {
        insert_inicio(key, lista);
    } else {
        int level = rand_nivel();
        Node *novo = create_node(key, level);
        Node *aux[max_nivel];
        for(int i = 0; i < max_nivel; i++){
            novo->next[i] = lista->inicio[i];
        }
        for(int i = max_nivel - 1; i >= 0; i--){
            if(novo->next[i] == NULL){
                aux[i] = novo;
                continue;
            }
            else{
                while (novo->next[i]->key < key){
                    novo = novo->next[i];
                }
                aux[i] = novo;
            }
        }
        novo = novo->next[0];
        if(novo->key == key){
            //atualização do valor
        }
        else{
            if(lista->nivel < level){
                for(int i = level + 1; i < max_nivel; i++){
                    aux[i] = lista->inicio[i];
                }
                lista->nivel = level;
            }
            for(int i = 0; i < level; i++){
                novo->next[i] = aux[i]->next[i];
                aux[i]->next[i] = novo;

            }
        }
    }
}


void print_skiplist(Skiplist* skiplist){
    for(int i = max_nivel - 1; i >= 0; i--){
        Node* aux = skiplist->inicio[i];
        printf("Level %d: ", i);
        while(aux != NULL){
            printf("%d ", aux->key);
            aux = aux->next[i];
        }
        printf("\n");
    }
}

int search(int key, Skiplist *lista){
    Node *aux;
    aux->key = 0;
    for(int i = 0; i < max_nivel; i++){
        aux->next[i] = lista->inicio[i];
    }
    for(int i = max_nivel - 1; i >= 0; i--){
        while(aux->key != key || aux->next[i] != NULL){
            printf("%d\n ", aux->key);
            aux = aux->next[i];
        }
        if(aux->key == key){
            return 1;
        }
    }
    return 0;
}