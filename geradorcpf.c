#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void gerador(FILE *fptr);

int main(){
int k;
scanf("%d",&k);
srand(time(NULL));
FILE *fileptr = fopen("C:\\Users\\joaov\\Documents\\estudos\\C\\ds\\cpfs.txt","w");

for(int i=0;i<k;i++){
gerador(fileptr);
}

fclose(fileptr);
return 0;
}

void gerador(FILE *fptr){
    int a[11],soma,soma1;
    soma = 0;
    soma1 = 0;
    for(int i=0;i<9;i++){
        a[i] = rand()%10;
        soma += (a[i]*(10-i));
        soma1+= (a[i]*(11-i));
    }
   
    if(soma%11<2){
        a[9] = 0;
    }
    else{
        a[9] = 11 - (soma - (11 *(soma/11)));
    }
    soma1 += a[9] * 2;

    if(soma1%11<2){
        a[10] = 0;
    }
    else{
        a[10] = 11 - (soma1 - (11*(soma1/11)));
    }
    for(int i=0; i<11;i++){
            fprintf(fptr,"%d",a[i]);
    }
    fprintf(fptr,"%c\n",' ');

    return;
}