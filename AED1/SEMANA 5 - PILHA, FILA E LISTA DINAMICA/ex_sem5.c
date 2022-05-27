#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

//Gabriel Almeida Rodrigues Pereira | RA: 143229 | Turma: Regina Celia Coelho

typedef struct{
    int codigo;
    float preco;
    char nome[MAX];
    struct Tlista *proximo;
}Tlista;

typedef Tlista *Plista;

Plista inicia(Tlista *Lista, int codigo, float preco, char nome[MAX]){
    Tlista *novo = (Tlista*)malloc(sizeof(Tlista));
    novo->proximo = NULL;
    novo->codigo = codigo;
    novo->preco = preco;
    strcpy(novo->nome,nome);
    return novo;
}

Plista insere_ord(Tlista *Lista, int codigo, float preco, char nome[MAX]){
    Tlista *novo;
    Tlista *aux = Lista;
    Tlista ant;
    while(aux->proximo != NULL){
        aux = Lista->proximo;
    }
    aux->proximo = (Tlista*)malloc(sizeof(Tlista));
    novo = aux->proximo;
    novo->proximo = NULL;
    novo->codigo = codigo;
    novo->preco = preco;
    strcpy(novo->nome,nome);
    aux = Lista;
}

Plista busca(Tlista *Lista, Tlista *codigo_busca){
    Tlista *aux = Lista;
    if(aux->codigo == codigo_busca){
        printf("\nPRODUTO ENCONTRADO\nCODIGO: %d, PRECO: %.2f, NOME: %s\n", aux->codigo,aux->preco,aux->nome);
        return Lista;
    }
    if(aux != NULL){
        busca(Lista->proximo, codigo_busca);
    }
    else{
        printf("\n| PRODUTO NAO ENCONTRADO |\n");
    }
}

Plista remover(Tlista *Lista, char nome[MAX]){
    Tlista *aux = Lista;
    Tlista *ant = Lista;

    if(strcmp(aux->nome,nome) == 0){
        printf("\n| REMOVENDO PRODUTO |\nCODIGO: %d | PRECO: %.2f | NOME: %s", aux->codigo, aux->preco, aux->nome);
        aux = Lista;
        Lista = Lista->proximo;
        free(aux);
        return Lista;
    }
    aux=aux->proximo;
    while(strcmp(aux->nome,nome) != 0){
        aux=aux->proximo;
        ant = ant->proximo;
    }
    printf("\n| REMOVENDO PRODUTO |\nCODIGO: %d | PRECO: %.2f | NOME: %s", aux->codigo, aux->preco, aux->nome);
    free(aux);
    ant->proximo = aux->proximo;
}

void imprime_lista(Tlista *Lista){
    if(Lista == NULL){
        printf("\n| LISTA VAZIA |\n");
    }
    while(Lista != NULL){
        printf("\nCODIGO: %d, PRECO: %.2f, NOME: %s\n", Lista->codigo,Lista->preco,Lista->nome);
        Lista = Lista->proximo;
    }
}


void destroi_lista(Tlista *Lista){
    if(Lista == NULL){
        printf("\n| LISTA VAZIA |\n");
        return;
    }
    Tlista *aux = Lista->proximo;
    printf("\nCODIGO: %d, PRECO: %.2f, NOME: %s", Lista->codigo,Lista->preco,Lista->nome);
    free(Lista);
    if(aux != NULL){
        destroi_lista(aux);
    }
}


int main(){
    Tlista *Lista;
    Lista=(Tlista*)malloc(sizeof(Tlista));
    int codigo = 0;
    int codigo_busca;
    int continua = 0;
    float preco = 0;
    char nome[MAX];
        printf("\nDigite PRECO do produto: ");
        scanf("%f", &preco);
        setbuf(stdin,NULL);
        printf("\nDigite NOME do produto: ");
        scanf("%s",nome);
        Lista = inicia(Lista, codigo, preco, nome);
        printf("\nDeseja continuar? < 0 > SIM | < outro valor > NAO: ");
        scanf("%d", &continua);
    while(continua == 0){
        codigo++;
        printf("\nDigite PRECO do produto: ");
        scanf("%f", &preco);
        setbuf(stdin,NULL);
        printf("\nDigite NOME do produto: ");
        scanf("%s",nome);
        insere_ord(Lista,codigo,preco,nome);
        printf("\nDeseja continuar? < 0 > SIM | < outro valor > NAO: ");
        scanf("%d", &continua);
    }
    printf("\n| PRODUTOS CADASTRADOS |\n");
    imprime_lista(Lista);
    printf("\n");
    printf("\nQual o CODIGO do produto deseja buscar: ");
    scanf("%d", &codigo_busca);
    busca(Lista,codigo_busca);
    printf("\nQual o NOME do produto deseja remover: ");
    scanf("%s", nome);
    remover(Lista,nome);
    printf("\n");
    printf("\n| PRODUTOS ATUALIZADOS |\n");
    imprime_lista(Lista);
    printf("\n| DESTRUINDO PRODUTOS |\n");
    destroi_lista(Lista);
return 0;
}
