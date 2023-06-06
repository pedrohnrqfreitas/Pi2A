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
        FILE *exel[10];
        FILE *cpf;
        char line[MAX_LINE_LENGTH];
        char cpfstr[12];
        int contador = 1;
        srand(time(NULL));


        //Arruma o texto
        setlocale(LC_ALL,"Portuguese");

        // Abre o arquivo CSV para leitura
        //abrir os outros aquivos de csv
        exel[0] = fopen("0.csv", "r");
        exel[1] = fopen("1.csv", "r");
        exel[2] = fopen("2.csv", "r");
        exel[3] = fopen("3.csv", "r");
        exel[4] = fopen("4.csv", "r");
        exel[5] = fopen("5.csv", "r");
       
        //abrir o arquivo que contenha os cpfs
        cpf = fopen("CPFs.txt","r");
        // Lê cada linha do arquivo
        for(int i = 0; i < 6; i++){
            
            if (exel[i] == NULL) {
                printf("Nao foi possivel abrir o arquivo.\n");
                return 1;
            }
            while (fgets(line, sizeof(line), exel[i]) && fgets(cpfstr,12,cpf)) {
                char *field;
                char fieldCopy[MAX_FIELD_LENGTH];

                // Copia a linha para uma variável temporária
                strncpy(fieldCopy, line, sizeof(fieldCopy));

                // Extrai cada campo separado por vírgula
                field = strtok(fieldCopy, delimiter);

                int atual = 0;
                int colunas[] = { 2,4, 6, 9, 11,21,23,25,28};
                int size = sizeof (colunas)/sizeof(int);


                //printf("%d, ",contador);
                //declaração da variavel que vai conter o dado
                Dado dado;
                while (field != NULL) {
                    if(findColum(colunas, size,atual)==1){
                        //sequencia de ifs atribuindo os dados 
                       switch (atual)
                       {
                       case 2:
                        dado.idade = field;
                        break;
                       case 4:
                        dado.sexo = field;
                        break;
                       case 6:
                        dado.cor = field;
                        break;
                       case 9:
                        dado.municipio = field;
                        break;
                       case 11:
                        dado.uf = field;
                        break;
                       case 21:
                        dado.grupoAtendimento = field;
                        break;
                       case 23:
                        dado.categoria = field;
                        break;
                       case 25:
                        dado.fabricante = field;
                        break;
                       case 28:
                        dado.dose = field;
                        break;
                       default:
                       printf("fudeu geral!!\n");
                        break;
                       }
                        // Imprime o valor do campo
                        //printf("%s, ", field);
                    }

                    // Obtém o próximo campo
                    field = strtok(NULL, delimiter);
                    atual += 1;

                }
                insert_inicio(atoll(cpfstr), &dado, skiplist);
                //printf("\n");
                contador ++;
            }
        }
        printf("%s\n",cpfstr);
        // Fecha o arquivo
        for(int i = 0; i < 6; i++){
            fclose(exel[i]);
        }
        return 0;
}
