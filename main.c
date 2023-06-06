#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "skiplist.h"
#include "leitor_csv.h"


//funções
void opcao();
void mostar(Dado *dado);

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
            }
            else{
                printf("A pessoa nao existe\n");
            }
            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("tempo de execucao: %.2f \n", tempo);
        }
        else if(v==2){
            Dado novo;
            printf("Digite a idade: ");
            scanf("%s", novo.idade);
            printf("%s",novo.idade);
            printf("\nDigite o sexo: ");
            scanf("%s",novo.sexo);
            printf("%s",novo.sexo);
            printf("\nDigite o municipio: ");
            scanf("%s", novo.municipio);
            printf("%s",novo.municipio);
            printf("\nDigite a UF: ");
            scanf("%s",novo.uf);
            printf("%s",novo.uf);
            printf("\nDigite o grupo de atendimento: ");
            scanf("%s",novo.grupoAtendimento);
            printf("%s",novo.grupoAtendimento);
            printf("\nDigite a categoria: ");
            scanf("%s",novo.categoria);
            printf("%s",novo.categoria);
            printf("\nDigite a fabricante: ");
            scanf("%s",novo.fabricante);
            printf("%s",novo.fabricante);         
            printf("\nDigite a dose: ");
            scanf("%s",novo.dose);
            printf("%s",novo.dose);
            printf("\nDigite o CPF: ");
            scanf("%lld",key);
            inicio = clock();
            insert(key,&novo,skiplist);
            fim = clock();
            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("tempo de execucao: %.2f \n", tempo);
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
    printf("município: %s\n",dado->municipio);
    printf("uf: %s\n",dado->uf);
    printf("grupo de atendimento: %s\n",dado->grupoAtendimento);
    printf("categoria: %s\n",dado->categoria);
    printf("fabricante: %s\n",dado->fabricante);
    printf("dose: %s\n",dado->dose);
} 
