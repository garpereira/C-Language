#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 2
//Gabriel Almeida Rodrigues Pereira | RA: 143229 | Turma : Regina Celia Coelho
typedef struct{
    int pontos;
    int id_jogador;
    struct Tlista *proximo;
}Tlista;
typedef Tlista *Plista;

Plista inicia(Tlista *lista){
    Tlista *novo = (Tlista*)malloc(sizeof(Tlista));
    novo->proximo = novo;
    novo->pontos = 0;
    novo->id_jogador = 0;
    return novo;
}

Plista insere(Plista ultimo, int id_jogador){
    Plista novo = (Tlista*)malloc(sizeof(Tlista));
    Plista aux;
    novo->id_jogador = id_jogador;
    novo->pontos=0;
    if(ultimo == NULL){
        novo->proximo = novo;
        return novo;
    }

    aux = ultimo;
    while(aux->proximo != ultimo){
        aux = aux->proximo;
    }
    if(ultimo != NULL){
        aux->proximo = novo;
        novo->proximo = ultimo;
    }
}

int cartaspontos(char cartas[MAX]){

    if(strcmp(cartas,"A")==0)
        return 11;
    else if(strcmp(cartas,"Q")==0 || strcmp(cartas,"K")==0 || strcmp(cartas,"J")==0 || strcmp(cartas,"10")==0)
        return 10;
    else if(cartas[0]>='2' && cartas[0] <='9' && cartas[1]=='\0')
        return cartas[0]-'0';
    else
        return 1;
}
void imprime(Plista lista, int cpy_qtd){
    Plista aux=lista;
    if(cpy_qtd == 1){
        aux=aux->proximo;
        printf("Jogador %d: %d pontos\n", aux->id_jogador,aux->pontos);
    }
    else{
        while(aux->proximo != lista){
            printf("Jogador %d: %d pontos\n", aux->id_jogador,aux->pontos);
            aux=aux->proximo;
            if(aux->proximo == lista){
                printf("Jogador %d: %d pontos\n", aux->id_jogador,aux->pontos);
            }
        }
    }

}
void remover(Plista perdedor, int *cpy_qtd){
    Tlista *aux = perdedor;
    int copia = *cpy_qtd;
    printf("Jogador %d perdeu, %d pontos\n",aux->id_jogador,aux->pontos);
    aux=aux->proximo;
    while(aux->proximo != perdedor){
        aux=aux->proximo;
    }
    copia--;
    *cpy_qtd = copia;
    aux->proximo = perdedor->proximo;
    free(perdedor);
}

int main(){
    Tlista *lista = NULL;
    char carta[MAX]; //A = 11 | J,Q,K = 10 | 2 a 10
    int id_jogador = 1;
    int qtd_jogadores;
    int cpy_qtd;
    int i;
    Tlista *primeiro;
    printf("\nQuantos Jogadores: ");
    scanf("%d",&qtd_jogadores);
    cpy_qtd = qtd_jogadores;
    for(i=0;i<qtd_jogadores;i++){
        if(lista==NULL){
            lista=insere(lista, i+1);
            primeiro=lista;
        }else{
            insere(lista, i+1);
        }
    }
    do{
        if(lista == primeiro)
            imprime(primeiro, cpy_qtd);
        printf("Qual a carta do Jogador %d: \n",lista->id_jogador);
        scanf("%s",&carta);
        setbuf(stdin,NULL);


        while(cartaspontos(carta) == 1){
            printf("Carta invalida\nDigite outra: ");
            scanf("%s",&carta);
        }

        lista->pontos += cartaspontos(carta);
        if(lista->pontos>21){
         if(lista == primeiro)
            primeiro = primeiro->proximo;
            remover(lista, &cpy_qtd);
        }
        if(cpy_qtd == 1){
            printf("\nVenceu ->");
            imprime(primeiro, cpy_qtd);
            break;
        }
        if(lista->pontos == 21){
            printf("\nJogador %d venceu\n", lista->id_jogador);
            break;
        }
        lista = lista->proximo;
    }while(lista->pontos != 21);

    return 0;
}
