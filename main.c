#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "skiplist.h"
#include "leitor_csv.h"


//funções
void opcao();
void mostar(Dado *dado);
void imprime_tudo(Skiplist *skiplist);

int main(){
    clock_t inicio,fim;
    double tempo;
    int v;
    long long int key;
    char temp[50];
    inicio = clock();
    Skiplist *skiplist;
    skiplist = create_skiplist();
    leitor_csv(skiplist);
    fim = clock();
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("tempo de execucao: %.2f \n", tempo);
    print_skiplist(skiplist, 10);
    //imprime_tudo(skiplist);
    printf("\n");
    opcao();
    scanf("%d", &v);
    while(v< 4 && v > 0){
        //system("cls");
        
        if(v == 1){ 
            printf("Digite uma key:\n");
            scanf("%lld", &key);
            inicio = clock();
            Node *mostrar = search(key, skiplist);
            fim =  clock();
            if(mostrar!=NULL){
                mostar(mostrar->dado);
                //printf("%s\n", mostrar->dado->idade);
                //printf("A pessoa existe\n");
            }
            else{
                printf("A pessoa nao existe\n");
            }
            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("tempo de execucao: %.2f \n", tempo);
        }
        else if(v==2){
            Dado *novo = (Dado*) malloc(sizeof(Dado));
            novo->idade = malloc(4);
            novo->sexo = malloc(2);
            novo->cor = malloc(21);
            novo->municipio = malloc(31);
            novo->uf = malloc(4);
            novo->grupoAtendimento = malloc(81);
            novo->categoria = malloc(61);
            novo->fabricante = malloc(31);
            novo->dose = malloc(16);
            printf("Digite a idade: ");
            //scanf("%s", novo->idade);
            fflush(stdin);
            fgets(novo->idade,4,stdin);
            // printf("%s",novo.idade);
            printf("\nDigite o sexo: ");
            //scanf("%s",novo->sexo);
            fflush(stdin);
            fgets(novo->sexo,2,stdin);
            // printf("%s",novo.sexo);
            printf("\nDigite a Cor: ");
            fflush(stdin);
            fgets(novo->cor,21,stdin);             
            printf("\nDigite o municipio: ");
            //scanf("%s", novo->municipio);
            fflush(stdin);
            fgets(novo->municipio,31,stdin);
            // printf("%s",novo.municipio);
            printf("\nDigite a UF: ");
            //scanf("%s",novo->uf);
            fflush(stdin);
            fgets(novo->uf,4,stdin);
            // printf("%s",novo.uf);
            printf("\nDigite o grupo de atendimento: ");
            //scanf("%s",novo->grupoAtendimento);
            fflush(stdin);
            fgets(novo->grupoAtendimento,81,stdin);
            // printf("%s",novo.grupoAtendimento);
            printf("\nDigite a categoria: ");
            //scanf("%s",novo->categoria);
            fflush(stdin);
            fgets(novo->categoria,61,stdin);
            // printf("%s",novo.categoria);
            printf("\nDigite a fabricante: ");
            //scanf("%s",novo->fabricante);
            fflush(stdin);
            fgets(novo->fabricante,31,stdin);
            // printf("%s",novo.fabricante);         
            printf("\nDigite a dose: ");
            //scanf("%s",novo->dose);
            fflush(stdin);
            fgets(novo->dose,16,stdin);
            // printf("%s",novo.dose);
            printf("\nDigite o CPF: ");
            scanf("%lld",key);
            Node *vr = search(key, skiplist);
            if(vr == NULL){
                inicio = clock();
                insert(key,novo,skiplist);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("tempo de execucao: %.2f \n", tempo);
            }
            else{
                printf("Pessoa ja cadastrada\n");
            }
        }
        else if(v == 3){
            printf("Digite uma key:\n");
            scanf("%lld", &key);
            inicio = clock();
            if(!remover(key, skiplist)){
                printf("Removido!\n");
            }
            fim = clock();
            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("tempo de execucao: %.2f \n", tempo);
        }
        
        opcao();
        scanf("%d", &v);
    }
    
    return 0;
}

void opcao(){
    printf("------------  -----------  -----------  --------\n");
    printf("|1.Consulta|  |2.Inserir|  |3.Deletar|  |4.Sair|\n");
    printf("------------  -----------  -----------  --------\n");
}

void mostar(Dado *dado){
    printf("idade: %s\n",dado->idade);
    printf("sexo: %s\n",dado->sexo);
    printf("cor: %s\n",dado->cor);
    printf("municipio: %s\n",dado->municipio);
    printf("uf: %s\n",dado->uf);
    printf("grupo de atendimento: %s\n",dado->grupoAtendimento);
    printf("categoria: %s\n",dado->categoria);
    printf("fabricante: %s\n",dado->fabricante);
    printf("dose: %s\n",dado->dose);
} 

 void imprime_tudo(Skiplist *skiplist){
     Node *aux = skiplist->inicio[0];
     while(aux != NULL){
         printf("\n");
         printf("%lld / %s / %s / %s / %s / %s / %s / %s / %s",aux->key,aux->dado->idade,aux->dado->sexo,aux->dado->cor,aux->dado->municipio,aux->dado->uf,aux->dado->grupoAtendimento,aux->dado->categoria,aux->dado->fabricante,aux->dado->dose);
         aux = aux->next[0];
     }
 }
