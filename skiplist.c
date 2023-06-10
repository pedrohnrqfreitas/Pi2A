#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//define
#define max_level 22

//structs
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
    struct Dado *dado;
    struct Node* next[max_level];
}Node;

typedef struct skiplist{
    int level;
    Node* inicio[max_level];
}Skiplist;

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

Node* create_node(int level,Dado *dado){
    Node* newnode = (Node*) malloc(sizeof(Node));
    newnode->dado = dado;
    return newnode;
}

Node *search(long long int key, Skiplist *lista){
    for(int i = max_level - 1; i >= 0; i--){
        Node *aux = lista->inicio[i];
        if(aux == NULL){
            continue;
        }
        else{
            while(aux != NULL && aux->key <= key){
                if(aux->key == key){
                return aux;
                }
                aux = aux->next[i];
            }
        }
    }
    return NULL;
}


void insert_inicio(long long int key,Dado *dado, Skiplist* lista){
    int level = rand_level();
    Node* aux = create_node(level,dado);
    aux->key = key;
    lista->level = level;
    for(int i = level; i >= 0; i--){
        aux->next[i] = lista->inicio[i];
        lista->inicio[i] = aux;
    }
}

int insert(long long int key, Dado *dado, Skiplist *lista) {
    if (lista->inicio[0] == NULL) {
        insert_inicio(key, dado, lista);
    }
    else {
        int level = rand_level();
        Node *novo = create_node(level, dado);
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
    return 1;
}


void print_skiplist(Skiplist* skiplist, int qtd){
    int cont = 0;
    for(int i = max_level - 1; i >= 0; i--){
        Node* aux = skiplist->inicio[i];
        printf("Level %d: ", i);
        while(aux != NULL){
            if(cont == qtd){
                return;
            }
            printf("%lld ", aux->key);
            aux = aux->next[i];
            cont++;
        }
        if(aux == NULL){
            printf("NULL");
        }
        printf("\n");
    }
}

int remover(long long int key, Skiplist *lista){
    if (lista->inicio[0] == NULL) {
        return 0;
    } 
    else {
        Node *update[max_level];
        Node *aux2;
        for(int i = 0; i < max_level; i++){
            update[i] = NULL;
        }
        for(int i = max_level - 1; i >= 0; i--){
            Node *aux = lista->inicio[i];
            if(aux == NULL){
                continue;
            }
            if(aux->key == key){
                lista->inicio[i] = aux->next[i];
            }
            if(aux->next[i] == NULL){
                continue;
            }
            else{
                while (aux->next[i] != NULL && aux->next[i]->key < key){
                    aux = aux->next[i];
                    if(aux->next[i] == NULL){
                        break;
                    }
                }
                if(aux->next[i] == NULL){
                    continue;
                }
                if(aux->next[i]->key == key){
                    update[i] = aux;
                    aux2 = aux->next[i];
                }
            }
        }
        if(update[0] == NULL){
                return 0;
        }
        for(int i = 0; i < max_level; i++){
            if(update[i] != NULL){
                update[i]->next[i] = aux2->next[i];
            }
        }
        free(aux2);
        return 1;
    }

}
Dado* CriaDado(){
    Dado *dado = (Dado*) malloc(sizeof(Dado));
    return dado;
}