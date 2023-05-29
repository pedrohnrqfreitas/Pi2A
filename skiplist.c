#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//define
#define max_level 6

//structs
typedef struct Node{
    int key;
    struct Node* next[max_level];
}Node;

typedef struct skiplist{
    int level;
    Node* inicio[max_level];
}Skiplist;

//funções
int rand_level();
Skiplist* create_skiplist();
Node* create_node(int level);
void insert_inicio(int key, Skiplist* lista);
void insert(int key,  Skiplist *lista);
void print_skiplist(Skiplist* skiplist);
int search(int key, Skiplist *lista);

int main(){
    Skiplist* skiplist = create_skiplist();

    insert(5, skiplist);
    insert(4, skiplist);
    insert(6, skiplist);
    insert(2, skiplist);
    insert(1, skiplist);

    print_skiplist(skiplist);

    if(search(5, skiplist)){
        printf("achei\n");
    }

    
}

int rand_level() {
    static int initialized = 0;
    int num = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    while(rand() % 2 == 1 && num < max_level - 1){
        num++;
    }
    return num;
}

Skiplist* create_skiplist(){
    Skiplist* skiplist = (Skiplist*) malloc(sizeof(Skiplist));
    for(int i = 0; i < max_level; i++){
        skiplist->inicio[i] = NULL;
    }
    return skiplist;
}

Node* create_node(int level){
    Node* newnode = (Node*) malloc(sizeof(Node));
    return newnode;
}

void insert_inicio(int key, Skiplist* lista){
    int level = rand_level();
    Node* aux = create_node(level);
    aux->key = key;
    lista->level = level;
    for(int i = level; i >= 0; i--){
        aux->next[i] = lista->inicio[i];
        lista->inicio[i] = aux;
    }
}

void insert(int key, Skiplist *lista) {
    if (lista->inicio[0] == NULL) {
        insert_inicio(key, lista);
    } 
    else {
        int level = rand_level();
        Node *novo = create_node(level);
        novo->key = key;
        for(int i = level; i >= 0; i--){
            Node *aux = lista->inicio[i];
            if(aux == NULL){
                novo->next[i] = NULL;
                lista->inicio[i] = novo;
                continue;
            }
            if(aux->key > key){
                novo->next[i] = lista->inicio[i];
                lista->inicio[i] = novo;
            }
            else{
                while (aux->next[i] != NULL && aux->next[i]->key <= key){
                    aux = aux->next[i];
                }
                novo->next[i] = aux->next[i];
                aux->next[i] = novo; 
            }
        }
    }
}


void print_skiplist(Skiplist* skiplist){
    for(int i = max_level - 1; i >= 0; i--){
        Node* aux = skiplist->inicio[i];
        printf("Level %d: ", i);
        while(aux != NULL){
            printf("%d ", aux->key);
            aux = aux->next[i];
            
        }
        if(aux == NULL){
            printf("NULL");
        }
        printf("\n");
    }
}

int search(int key, Skiplist *lista){
    for(int i = max_level - 1; i >= 0; i--){
        Node *aux = lista->inicio[i];
        if(aux == NULL){
            continue;
        }
        else{
            while(aux != NULL && aux->key <= key){
                if(aux->key == key){
                return 1;
                }
                aux = aux->next[i];
            }
        }
    }
    return 0;
}