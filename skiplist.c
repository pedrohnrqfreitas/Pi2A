#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define MAX_LINE_LENGTH 1000
#define MAX_FIELD_LENGTH 1000
#define delimiter ";"
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
int leitor_csv();

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

int findColum(int *array, int size, int colum){
    for(int i = 0; i < size ; i++){
        if(array[i] == colum){
            return 1;
        }
    }
    return 0;
}


int leitor_csv(){
        FILE *file;
        char line[MAX_LINE_LENGTH];
        int contador = 1;
        srand(time(NULL));


        //Arruma o texto
        setlocale(LC_ALL,"Portuguese");

        // Abre o arquivo CSV para leitura
        file = fopen("C:\\Users\\Usuario\\CLionProjects\\untitled\\teste.csv", "r");
        if (file == NULL) {
            printf("Nao foi possivel abrir o arquivo.\n");
            return 1;
        }

        // Lê cada linha do arquivo
        while (fgets(line, sizeof(line), file)) {
            char *field;
            char fieldCopy[MAX_FIELD_LENGTH];

            // Copia a linha para uma variável temporária
            strncpy(fieldCopy, line, sizeof(fieldCopy));

            // Extrai cada campo separado por vírgula
            field = strtok(fieldCopy, delimiter);

            int atual = 0;
            int colunas[] = { 2,4, 6, 9, 11,21,23,25,28};
            int size = sizeof (colunas)/sizeof(int);


            printf("%d, ",contador);

            //Gerador de cpf

//        int a[11],soma,soma1;
//        soma = 0;
//        soma1 = 0;
//        for(int i=0;i<9;i++){
//            a[i] = rand()%10;
//            soma += (a[i]*(10-i));
//            soma1+= (a[i]*(11-i));
//        }
//
//        if(soma%11<2){
//            a[9] = 0;
//        }
//        else{
//            a[9] = 11 - (soma - (11 *(soma/11)));
//        }
//        soma1 += a[9] * 2;
//
//        if(soma1%11<2){
//            a[10] = 0;
//        }
//        else{
//            a[10] = 11 - (soma1 - (11*(soma1/11)));
//        }
//        for (int i = 0; i < 11; i++) {
//            printf("%d",a[i]);
//        }
//        printf(", ");

            while (field != NULL) {

                if(findColum(colunas, size,atual)==1){
                    // Imprime o valor do campo
                    printf("%s, ", field);
                }

                // Obtém o próximo campo
                field = strtok(NULL, delimiter);
                atual += 1;

            }
            printf("\n");
            contador ++;
        }

        // Fecha o arquivo
        fclose(file);
        return 0;
}