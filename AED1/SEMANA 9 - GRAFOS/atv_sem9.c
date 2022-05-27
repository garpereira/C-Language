#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
//Gabriel Almeida Rodrigues Pereira | RA: 143229 | Turma: Regina Celia Coelho

typedef struct no *pme;
struct no{
    int coord;
    pme proximo;
};
typedef pme DADOS[MAX];

void inicia(DADOS grafo, int n_vertices){
    int i;
    for(i=0;i<n_vertices;i++){
        grafo[i] = NULL;
    }
}

void insere(DADOS grafo, int coord1, int coord2, char pergunta[4]){
    pme novo, novo2, aux, aux2;
    int segura;
    novo=(pme)malloc(sizeof(struct no));
    novo2=(pme)malloc(sizeof(struct no));
    if(strcmp(pergunta, "nao") == 0){
        novo->coord = coord2-1;//caso nao seja direcionado, eu guardo os dois valores, assim consigo imprimir as conexoes x,y e y,x
        novo->proximo = NULL;
        if(grafo[coord1-1] == NULL)//guardando na linha coord1, o valor da coluna coord2
            grafo[coord1-1] = novo;
        else{
            for(aux=grafo[coord1-1]; aux->proximo != NULL; aux = aux->proximo);
                aux->proximo = novo;
        }
        novo2->coord = coord1-1;//senti a necessidade da criação de outro nó, para evitar conflito
        novo2->proximo = NULL;
        if(grafo[coord2-1] == NULL){//guardando na linha coord2 o valor da coluna coord1
            grafo[coord2-1] = novo2;
        }
        else{
            for(aux2=grafo[coord2-1];aux2->proximo != NULL; aux2=aux2->proximo);
                aux2->proximo = novo2;
        }
        return;
    }
    novo->coord = coord2-1;//caso seja direcionado, eu guardo um valor, assim imprimo x,y somente
    novo->proximo = NULL;
    if(grafo[coord1-1] == NULL)
        grafo[coord1-1] = novo;
    else{
        for(aux=grafo[coord1-1]; aux->proximo != NULL;aux = aux->proximo);
            aux->proximo = novo;
    }
}


void imprime(DADOS grafo, int n_vertices){
    int i, j;
    pme aux;
    printf("\nMatriz de adjacencia:\n\n");
    printf("    ");
    for(j=0;j<n_vertices;j++){
        printf(" %d ", j+1);
    }
    printf("\n");
    for(i=0;i<n_vertices;i++){
        aux = grafo[i];
        printf("\n%d   ", i+1);
        for(j=0;j<n_vertices;j++){
            if(aux!=NULL && aux->coord == j){
                printf(" 1 ");
                aux = aux->proximo;
                while(aux != NULL && aux->coord ==j) aux = aux->proximo;
            }
            else{
                printf(" 0 ");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}


void adjacentes(DADOS grafo,int n_vertices, int vertice, char pergunta[4]){
    int vet[n_vertices];
    pme aux;
    int j, i;
    int achou = 0;
    aux = grafo[vertice-1];
    for(j=0;j<n_vertices;j++){
        if(aux != NULL && strcmp(pergunta, "nao") == 0){
            for(i=0;i<achou;i++){
                if(vet[i] == aux->coord)//verifica se ja foi inserido a posicao
                    break;
            }
            if(vet[i] == aux->coord){
                aux=aux->proximo;
                break;
            }
            vet[j] = aux->coord;
            aux=aux->proximo;
            while(aux != NULL && aux->coord == vet[j])aux=aux->proximo;
            achou++;
        }
        else if(aux != NULL){
            vet[j] = aux->coord;
            aux=aux->proximo;
            while(aux != NULL && aux->coord == vet[j])aux=aux->proximo;
            achou++;
        }
    }
    if(achou == 0){
        printf("\nNao ha adjacentes para o vertice %d.\n", vertice);
    }
    else{
        printf("\nOs adjacentes ao vertice %d sao: ", vertice);
        for(j=0;j<achou;j++){
            if(j == achou-1)
                printf("e %d.", vet[j]+1);
            else
            printf("%d ", vet[j]+1);
        }
    }
}

void libera(DADOS grafo, int n_vertices){
    pme aux, aux2;
    int i;
    for(i=0;i<n_vertices;i++){
        aux = grafo[i];
        while(aux != NULL){
            aux2=aux;
            aux=aux->proximo;
            free(aux2);
        }
    }
}

int main(){
    DADOS grafo;
    int n_vertices=0;
    int coord1=0;
    int coord2=0;
    int limite = 0;
    int vertice;
    char pergunta[4];
    printf("\nInforme o numero de vertices: ");
    scanf("%d", &n_vertices);
    while(n_vertices <= 0 || n_vertices > MAX){
        printf("\nNumero de vertices invalido\nInforme o numero de vertices: ");
        scanf("%d", &n_vertices);
    }
    inicia(grafo, n_vertices);
    printf("\nO grafo eh orientado? ");
    scanf("%s",pergunta);
    setbuf(stdin,NULL);
    printf("\nInforme as conexoes(com virgula), digite 0 para encerrar ou ate o limite de entradas\n");
    scanf("%d,%d",&coord1,&coord2);
    while(coord1 > n_vertices || coord2 > n_vertices){
        printf("\nValor invalido, informe cada conexao(com virgula) de valor no maximo %d: ", n_vertices);
        scanf("%d,%d",&coord1,&coord2);
        if(coord1 == 0 || coord2 == 0){
            printf("\nNenhuma conexao informada, programa sera encerrado\n");
            return 0;
        }
    }
    insere(grafo, coord1, coord2, pergunta);
    limite++;
    while(limite < n_vertices*n_vertices || coord1 != 0 || coord2 != 0){
        coord1 = 0;//preciso zerar eles aqui para evitar entrada incorreta
        coord2 = 0;
        scanf("%d,%d",&coord1,&coord2);//se eu nao zerar ali em cima, e aqui for digitado x y, sem virgula, o valor passa despercebido
        while(coord1 > n_vertices || coord2 > n_vertices){
            printf("\nValor invalido, informe cada conexao(com virgula) de valor no maximo %d: ", n_vertices);
            scanf("%d,%d",&coord1,&coord2);
        }
        if(coord1 == 0 || coord2 == 0){
            break;
        }
        insere(grafo, coord1, coord2, pergunta);
        limite++;
    }
    printf("\nInforme o vertice que deseja saber seus adjacentes: ");
    scanf("%d", &vertice);
    while(vertice == 0 || vertice > n_vertices){
        printf("\nInforme um vertice correto de valor 1 a maximo %d: ", n_vertices);
        scanf("%d", &vertice);
    }
    imprime(grafo, n_vertices);
    adjacentes(grafo, n_vertices, vertice, pergunta);
    libera(grafo, n_vertices);

return 0;
}
