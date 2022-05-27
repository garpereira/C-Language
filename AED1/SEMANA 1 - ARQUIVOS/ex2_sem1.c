#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[20];
    int idade;
    float altura;
}pessoa;
typedef pessoa *PESSOAS;


void imprimedados(PESSOAS dados){
    printf("%s\n%d\n%.2f", dados->nome,dados->idade,dados->altura);
}

int main(){
    PESSOAS dados;
    dados = (PESSOAS)malloc(sizeof(pessoa));

    scanf("%s",dados->nome);
    scanf("%d",&dados->idade);
    scanf("%f",&dados->altura);
    imprimedados(dados);
    free(dados);
    return 0;
}
