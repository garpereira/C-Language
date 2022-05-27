#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int verifica(FILE *arquivo, char pnome[20]){
    char nome[20];
    int conta = 0;
    while(!feof(arquivo)){
        fscanf(arquivo,"%s", nome);
        if(strcmp(pnome,nome) == 0){
            conta++;
        }
    }
    return conta;
}

int main(){
    FILE *arquivo;
    arquivo = fopen("arquivo.txt", "w");
    char nome[20];
    char pnome[20];
    scanf("%s", nome);
    do{
        fprintf(arquivo,"%s\n",nome);
        scanf("%s",nome);
    }while(strcmp(nome,"FIM") !=0);
    fclose(arquivo);
    arquivo = fopen("arquivo.txt", "r");
    scanf("%s",pnome);
    printf("\n%d", verifica(arquivo, pnome));
    return 0;
}
