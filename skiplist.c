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
        Node *aux = lista->inicio[max_level];
        int i = 1;
        printf("estou procurando\n");
        while((aux == NULL||aux->key>key)){
            aux = lista->inicio[max_level-i];
            i++;
            if(i >max_level){
                return NULL;
            }
        }
        if(aux->key==key){
            return aux;
        }
        while(i<=max_level){
            if(aux->next[max_level-i]==NULL){
                i++;
                if(i > max_level){
                    return NULL;
                }
            }else{
                if(aux->next[max_level-i]->key == key){
                    return aux->next[max_level-i];
                }
                if(aux->next[max_level-i]->key>key){
                    i++;
                    if(i>max_level){
                        return NULL;
                    }
                }
                if(aux->next[max_level-i]->key<key){
                    aux = aux->next[max_level-i];
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
        Node *aux = lista->inicio[level];
        int i =level;
        while(aux==NULL||aux->key>key){
            if(aux == NULL){
                lista->inicio[i] = novo;
                novo->next[i] = NULL;                
            }
            else{
                novo->next[i] = lista->inicio[i];
                lista->inicio[i] = novo;
            }

            i--;
            aux = lista->inicio[i];
            if(i<0){
                return 1;
            }
        }
        while(i>=0){
            if(aux->next[i]==NULL){
                aux->next[i] = novo;
                novo->next[i] = NULL;
                i--;
            }
            else{
                if(aux->next[i]->key>key){
                    novo->next[i] = aux->next[i];
                    aux->next[i] = novo;
                    i--;
                }
                else{
                    aux = aux->next[i];
                }
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
    else{
        Node *aux = lista->inicio[max_level];
        int i = 1;
        while((aux == NULL||aux->key>key)){
            aux = lista->inicio[max_level-i];
            i++;
            if(i >max_level){
                return 0;
            }
        }
        while(aux->key==key){
            lista->inicio[max_level-i] = aux->next[max_level-i];
            i++;
            if(i>max_level){
                free(aux->dado);
                free(aux);
                return 1;
            }
            aux = lista->inicio[max_level-i];
        }
        Node *aux2 = aux;
        while(i<=max_level){
            if(aux->next[max_level-i]==NULL){
                i++;
                if(i > max_level){
                    return 0;
                }
            }else{
                if(aux->next[max_level-i]->key == key){
                    aux->next[max_level-i] =aux->next[max_level-i]->next[max_level-i];
                    i++;
                }
                if(aux->next[max_level-i]->key>key){
                    i++;
                    if(i>max_level){
                        free(aux2->dado);
                        free(aux2);
                        return 0;
                    }
                }
                if(aux->next[max_level-i]->key<key){
                    aux = aux->next[max_level-i];
                } 
            }
 
        }

    }

}
Dado* CriaDado(){
    Dado *dado = (Dado*) malloc(sizeof(Dado));
    return dado;
}
