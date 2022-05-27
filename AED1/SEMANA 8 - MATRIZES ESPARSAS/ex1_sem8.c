#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
//Gabriel Almeida Rodrigues Pereira | RA: 143229 | Turma: Regina Celia Coelho
typedef struct no *pme;
struct no{
    int n_filme;//coluna
    char genero;
    pme proximo;
};
typedef pme dados[MAX];

void inicia(dados lista, int qtd_cliente){//inicia dados lista
    int i;
    for(i=0;i<qtd_cliente;i++){
        lista[i] = NULL;
    }
}


int verifica(dados lista, int i, int n_filme){
    pme aux;
    for(aux=lista[i];aux != NULL;aux = aux->proximo){
        if(aux->n_filme == n_filme-1){
            return 1;
        }
    }
    return 0;
}


void insere(dados lista, int i, int n_filme, char genero){
    pme novo, aux;
    novo = (pme)malloc(sizeof(struct no));
    novo->genero = genero;
    novo->n_filme = n_filme-1;//coluna, coloquei -1 para equiparar a posicao exata no vetor, pois se eu permitr que entre valor 10 por ex em um vetor de 10 posicoes, ele precisa alocar na posicao 9 do vetor
    novo->proximo = NULL;
    if(lista[i] == NULL){
        lista[i] = novo;
    }
    else{
        for(aux = lista[i];aux->proximo != NULL;aux = aux->proximo);
        aux->proximo = novo;
    }
}

void imprime_matriz(dados lista, int qtd_cliente, int qtd_catalogo){
    int i,j;
    pme aux;
    printf("\nMatriz inteira:\n");
    for(i=0;i<qtd_cliente;i++){
        aux = lista[i];
        for(j=0;j<qtd_catalogo;j++){
            if((aux != NULL) && (aux->n_filme==j)){
               printf(" 1 ");
               aux = aux->proximo;
            }
            else{
                printf(" 0 ");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

void imprime_condensada(dados lista, int qtd_cliente, int qtd_catalogo){
    int i,j;
    pme aux;
    printf("\nMatriz Condensada:\n");
    for(i=0;i<qtd_cliente;i++){
        aux = lista[i];
        printf("Cliente %d:\nFilmes assistidos( filme e genero ):\n",i+1);
        for(j=0;j<qtd_catalogo;j++){
            if((aux != NULL) && (aux->n_filme==j)){
               printf("%d   %c\n",aux->n_filme+1,aux->genero);
               aux = aux->proximo;
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

void mais_assistido(dados lista, int qtd_cliente, int qtd_catalogo){
    int i,j;
    int A=0,R=0,S=0,C=0,M=0,D=0,F=0,P=0;
    int maior;
    pme aux;
    for(i=0;i<qtd_cliente;i++){
        aux = lista[i];
        for(j=0;j<qtd_catalogo;j++){
            if((aux != NULL) && (aux->n_filme==j)){
                if(aux->genero == 'A'){
                    A++;
                }else if(aux->genero == 'R'){
                    R++;
                }else if(aux->genero == 'S'){
                    S++;
                }else if(aux->genero == 'C'){
                    C++;
                }else if(aux->genero == 'M'){
                    M++;
                }else if(aux->genero == 'D'){
                    D++;
                }else if(aux->genero == 'F'){
                    F++;
                }else if(aux->genero == 'P'){
                    P++;
                }
               aux = aux->proximo;
            }
        }
    }
    int vet[8] = {A,R,S,C,M,D,F,P};
    maior = A;
    for(i=0;i<8;i++){
        if(vet[i] > maior){
            maior = vet[i];
        }
    }
    if(maior == A)
        printf("\n\nO genero de filme mais assistido foi: Acao\n");
    else if(maior == R)
        printf("\n\nO genero de filme mais assistido foi: Romance\n");
    else if(maior == S)
        printf("\n\nO genero de filme mais assistido foi: Suspense\n");
    else if(maior == C)
        printf("\n\nO genero de filme mais assistido foi: Comedia\n");
    else if(maior == M)
        printf("\n\nO genero de filme mais assistido foi: Musical\n");
    else if(maior == D)
        printf("\n\nO genero de filme mais assistido foi: Drama\n");
    else if(maior == F)
        printf("\n\nO genero de filme mais assistido foi: Ficca\n");
    else if(maior == P)
        printf("\n\nO genero de filme mais assistido foi: Policial\n");
}

void libera(dados lista, int qtd_cliente){
    pme aux,aux2;
    int i;
    for(i=0;i<qtd_cliente;i++){
        aux=lista[i];
        while(aux != NULL){
            aux2 = aux;
            aux = aux->proximo;
            free(aux2);
        }
    }
}


int main(){
    dados lista;
    int qtd_cliente,qtd_catalogo, qtd_filme;
    int i,j;
    int n_filme;
    char genero;//(‘A' para ação, ‘R', para romance, 'S' para suspense, 'C' para comedia, 'M' para musical 'D' para drama, 'F' para ficcao e 'P' para policial
    printf("\nInsira a quantidade de filmes disponiveis no catalogo: ");
    scanf("%d", &qtd_catalogo);
    while(qtd_catalogo <= 0){
        printf("\nNecessario ter pelo menos 1 filme disponivel\nInsira um valor valido: ");
        scanf("%d", &qtd_catalogo);
    }
    printf("\nInsira a quantidade de clientes do servico: ");
    scanf("%d", &qtd_cliente);
    while(qtd_cliente <= 0){
        printf("\nNecessario ter pelo menos 1 cliente do servico\nInsira um valor valido: ");
        scanf("%d", &qtd_cliente);
    }
    inicia(lista,qtd_cliente);
    for(i=0;i<qtd_cliente;i++){
        printf("\nQuantos filmes cliente %d assistiu: ",i+1);
        scanf("%d", &qtd_filme);
        while(qtd_filme <=0 || qtd_filme > qtd_catalogo){
            printf("\nQuantidade invalida\nInsira valor de 1 ate %d: ",qtd_catalogo);
            scanf("%d",&qtd_filme);
        }
        for(j=0;j<qtd_filme;j++){
            setbuf(stdin,NULL);
            printf("\nQual o numero do %do filme: ",j+1);
            scanf("%d", &n_filme);
            while(n_filme <=0 || n_filme > qtd_catalogo){
                printf("\nFilme invalido\nInsira valor de 1 ate %d: ",qtd_catalogo);
                scanf("%d",&n_filme);
            }
            while(verifica(lista,i,n_filme) == 1){
                printf("\nFilme ja inserido\n\nDigite um filme valido: ");
                scanf("%d", &n_filme);
            }
            setbuf(stdin,NULL);
            printf("\nQual Genero do Filme: ");
            scanf("%c", &genero);
            while(genero != 'A' && genero != 'R' && genero != 'S' && genero != 'C' && genero != 'M' && genero != 'D' && genero != 'F' && genero != 'P'){
                setbuf(stdin,NULL);
                printf("\nGenero Invalido\nDigite um Genero valido do filme: ");
                scanf("%c", &genero);
            }
            insere(lista, i, n_filme, genero);
            setbuf(stdin,NULL);
        }
    }
    imprime_matriz(lista, qtd_cliente, qtd_catalogo);
    imprime_condensada(lista, qtd_cliente, qtd_catalogo);
    mais_assistido(lista, qtd_cliente, qtd_catalogo);
    libera(lista,qtd_cliente);
return 0;
}
