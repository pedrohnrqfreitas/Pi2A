#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "skiplist.h"

#define MAX_LINE_LENGTH 1000
#define MAX_FIELD_LENGTH 1000
#define delimiter ";"


//funções
int findColum(int *array, int size, int colum){
    for(int i = 0; i < size ; i++){
        if(array[i] == colum){
            return 1;
        }
    }
    return 0;
}


int leitor_csv(Skiplist *skiplist){
        FILE *cpf;
        //FILE *exel;
        char line[MAX_LINE_LENGTH];
        char cpfstr[13];
        char *arquivos[] = {"0.csv","1.csv","2.csv","3.csv","4.csv","5.csv"};
        int contador = 1,i=0;

        srand(time(NULL));


        //Arruma o texto
        setlocale(LC_ALL,"Portuguese");

        // Abre o arquivo CSV para leitura
        //abrir os outros aquivos de csv
        // exel[i] = fopen(arquivos[i], "r");
        // exel[1] = fopen("1.csv", "r");
        // exel[2] = fopen("2.csv", "r");
        // exel[3] = fopen("3.csv", "r");
        // exel[4] = fopen("4.csv", "r");
        // exel[5] = fopen("5.csv", "r");
        //abrir o arquivo que contenha os cpfs
        cpf = fopen("CPFs.txt","r");
        //for(int i = 0; i < 6; i++){
        
        while( i < 6 ){
            FILE *exel = fopen(arquivos[i], "r");
            printf("lendo arquivo %d\n", i);
            i++;
            //fazer um loop para ler todos os csvs
            if (exel == NULL) {
                printf("Nao foi possivel abrir o arquivo.\n");
                continue;
            }
            if(cpf == NULL){
                printf("Nao foi possivel abrir o CPF.\n");
                break;
            }
            // Lê cada linha do arquivo
            //printf("aaaaaaa");
            while (fgets(line, sizeof(line), exel) && fgets(cpfstr, 13, cpf)) {

                //printf("aaaaaaa");
                // fgets(cpfstr, 13, cpf);
                //printf("%s ",cpfstr);
                //printf("%s\n" ,cpfstr);
                char *field;
                char fieldCopy[MAX_FIELD_LENGTH];
                //printf("bbbbbb");
                // Copia a linha para uma variável temporária
                strncpy(fieldCopy, line, sizeof(fieldCopy));

                // Extrai cada campo separado por vírgula
                field = strtok(fieldCopy, delimiter);

                int atual = 0;
                int colunas[] = { 2,4, 6, 9, 11,21,23,25,28};
                int size = sizeof (colunas)/sizeof(int);


                //printf("%d, ",contador);
                //declaração da variavel que vai conter o dado
                Dado *dado = (Dado*) malloc(sizeof(Dado));
                dado->idade = malloc(4);
                dado->sexo = malloc(2);
                dado->cor = malloc(21);
                dado->municipio = malloc(31);
                dado->uf = malloc(4);
                dado->grupoAtendimento = malloc(81);
                dado->categoria = malloc(61);
                dado->fabricante = malloc(31);
                dado->dose = malloc(16);                        
                /*    
                char idade[4];
                char sexo[2];
                char cor[21];
                char municipio[31];
                char grupoAtendimento[61];
                char categoria[31];
                char fabricante[31];
                char dose[16];
                */ 
                while (field != NULL) {

                    if(findColum(colunas, size,atual)==1){
                        //printf("bbbbbbbb");
                        //sequencia de ifs atribuindo os dados 
                        // 2 idade
                        // 4 sexo
                        // 6 cor
                        // 9 municipio 
                        // 11 uf 
                        // 21 grupoAtendimento 
                        // 23 categoria 
                        // 25 fabricante 
                        // 28 dose

                        switch (atual)
                        {
                        case 2:
                            strncpy(dado->idade, field, 4);
                            //dado.idade = field;
                            //printf("%s ", dado.idade);
                            break;
                        case 4:
                            strncpy(dado->sexo, field, 2);
                            //dado.sexo = field;
                            //printf("%s ", dado.sexo);
                            break;
                        case 6: 
                            strncpy(dado->cor, field, 21);
                            //dado.cor = field;
                            //printf("%s ", dado.cor);
                            break;
                        case 9: 
                            strncpy(dado->municipio, field, 31);
                            //dado.municipio = field;
                            //printf("%s ", dado.municipio);
                            break;
                        case 11: 
                            strncpy(dado->uf, field, 4);
                            //dado.uf = field;
                            //printf("%s ", dado.uf);
                            break;
                        case 21: 
                            strncpy(dado->grupoAtendimento, field, 81);
                            //dado.grupoAtendimento = field;
                            //printf("%s", dado.grupoAtendimento);
                            break;
                        case 23: 
                            strncpy(dado->categoria, field, 61);
                            //dado.categoria = field;
                            //printf("%s ", dado.categoria);
                            break;
                        case 25: 
                            strncpy(dado->fabricante, field, 31);
                            //dado.fabricante = field;
                            //printf("%s ", dado.fabricante);
                            break;
                        case 28: 
                            strncpy(dado->dose, field, 16);
                            //dado.dose = field;
                            //printf("%s\n", dado.dose);
                            break;
                        
                        default:
                            printf("oooooopa");
                            break;
                        }
                        // Imprime o valor do campo
                        //printf("%s, ", field);
                    }

                    // Obtém o próximo campo
                    field = strtok(NULL, delimiter);
                    atual += 1;

                }
                // inserir na skiplist
                long long int key = atoll(cpfstr);
                insert(key, dado, skiplist);
                //Node *teste = search(99999999727,skiplist);
                //printf("\nteste: %s \n", teste->dado->idade);
                // printf \n
                //printf("\n");
                contador ++;
            }
            fclose(exel);
        }
        // Fecha o arquivo
        //for(int i = 0; i < 6; i++){
            //fclose(exel);
        //}
        
        return 0;
}
