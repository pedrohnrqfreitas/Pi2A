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


int leitor_csv(){
        FILE *file;
        char line[MAX_LINE_LENGTH];
        int contador = 1;
        srand(time(NULL));


        //Arruma o texto
        setlocale(LC_ALL,"Portuguese");

        // Abre o arquivo CSV para leitura
        //abrir os outros aquivos de csv
        file = fopen("C:\\Users\\Usuario\\CLionProjects\\untitled\\teste.csv", "r");
        //abrir o arquivo que contenha os cpfs
        

        //fazer um loop para ler todos os csvs
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
            //declaração da variavel que vai conter o dado
            //Dado *dado;
            while (field != NULL) {

                if(findColum(colunas, size,atual)==1){
                    //sequencia de ifs atribuindo os dados 
                    if(colunas[atual] == 2){
                        //dado->idade = field;
                    }
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