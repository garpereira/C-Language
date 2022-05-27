#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct{
    char nome[20];
    int idade;
    float altura;
}pessoa;
typedef pessoa *PESSOAS;


void imprimedados(PESSOAS dados, int n){
    int i;
    for(i=0;i<n;i++)
    printf("\nDADOS[ %d ]\n%s\n%d\n%.2f",i,dados[i].nome,dados[i].idade,dados[i].altura);
}

int main(){
    PESSOAS dados;
    int n;
    int i;
    scanf("%d", &n);
    dados = (pessoa*)malloc(n*sizeof(PESSOAS));
    for(i=0;i<n;i++){
        printf("\nDigite Dados Pessoa [ %d ]\n", i);
        scanf("%s",dados[i].nome);
        scanf("%d",&dados[i].idade);
        scanf("%f",&dados[i].altura);
    }
    imprimedados(dados, n);
    return 0;
}
