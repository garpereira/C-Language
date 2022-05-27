#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[20];
    int idade;
    float altura;
}pessoa;
typedef pessoa *PESSOAS;


int main(){
    PESSOAS dados;
    dados = (PESSOAS)malloc(sizeof(pessoa));

    scanf("%s",dados->nome);
    scanf("%d",&dados->idade);
    scanf("%f",&dados->altura);
    printf("%s\n%d\n%.2f", dados->nome,dados->idade,dados->altura);
    free(dados);
    return 0;
}
