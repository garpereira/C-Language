#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
//Gabriel Almeida Rodrigues Pereira | RA: 143229 | Turma: Regina Celia Coelho

typedef struct{
    char letra;
    struct Tlista *proximo;
    struct Tlista *anterior;
}Tlista;

typedef Tlista *Plista;

Plista inicia(Plista lista,char letra){
    Plista novo = (Tlista*)malloc(sizeof(Tlista));
    novo->proximo = NULL;
    novo->anterior = NULL;
    novo->letra = letra;
    return novo;
}

Plista insere(Plista lista, char letra){
    Plista novo = (Tlista*)malloc(sizeof(Tlista));
    if(lista == NULL){
        return inicia(lista,letra);
    }
    novo->letra = letra;
    novo->proximo = NULL;
    Plista aux;
    aux = lista;
    while(aux->proximo != NULL){
        aux = aux->proximo;
    }
    aux->proximo = novo;
    novo->anterior = aux;
    return lista;
}

void TrocaLetras(Plista lista, Plista auxletra1, Plista auxletra2){
    char aux = auxletra1->letra;
    auxletra1->letra = auxletra2->letra;
    auxletra2->letra = aux;
    return;
}

Plista buscaletras(Plista lista, char letra1, char letra2){
    Plista busca;
    Plista auxletra1;
    Plista auxletra2;
    int achou1 = 0;
    int achou2 = 2;
    for(busca=lista;busca != NULL; busca = busca->proximo){
        if(busca->letra == letra1 && achou1 == 0){
            auxletra1 = busca;
            achou1++;
        }
        if(busca->letra == letra2 && achou2 == 2){
            auxletra2 = busca;
            achou2++;
        }
        if(achou1+achou2 == 4){
            TrocaLetras(lista, auxletra1, auxletra2);
            break;
        }
    }
    if(achou1+achou2 < 4){
        printf("\nLetra nao encontrada\n");
        return NULL;
    }
    return lista;
}


void imprime(Plista lista){
    Plista aux = (Tlista*)malloc(sizeof(Tlista));
    aux = lista;
    while(aux != NULL){
        printf("%c", aux->letra);
        aux = aux->proximo;
    }
}

int main(){
    Plista lista;
    lista = NULL;
    char palavra[MAX];
    char letra;
    char letra1;
    char letra2;
    int i;

    printf("Digite a palavra: ");
    scanf("%s",palavra);
    for(i=0;palavra[i] != '\0';i++){
        letra = palavra[i];
        lista = insere(lista,letra);
    }
    setbuf(stdin,NULL);
    printf("\nQuais letras deseja trocar?\nLetra1: ");
    scanf("%c",&letra1);
    setbuf(stdin,NULL);
    printf("\nLetra2: ");
    scanf("%c",&letra2);
    if(buscaletras(lista,letra1,letra2) == 0)
        return 0;
    printf("\nPalavra arrumada: ");
    imprime(lista);
return 0;
}
