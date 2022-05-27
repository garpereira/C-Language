#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Gabriel Almeida Rodrigues Pereira | RA: 143229 | Turma: Regina Celia Coelho

typedef struct arv {
    char letra;
    struct arv* esq;
    struct arv* dir;
}TArv;
typedef TArv *PArv;

PArv cria(char letra){
    PArv novo = (PArv)malloc(sizeof(TArv));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->letra = letra;
    return novo;
}

void insere(PArv no, char pai, char filho, int nfilhos){
    if(nfilhos == 0)
        return;
    if(no->letra != pai){
        if(no->esq != NULL)
            insere(no->esq, pai, filho, nfilhos);
        if(no->dir != NULL)
            insere(no->dir, pai, filho, nfilhos);
            return;
    }
    PArv aux;
    if(no->esq == NULL)
        no->esq = cria(filho);
    else{
        aux = no->esq;
        while(aux->dir != NULL)
            aux = aux->dir;
        aux->dir = cria(filho);
    }
}

void imprime(PArv raiz,int opcao){
    if(raiz != NULL){
        if(opcao == 2)
            printf("(");
        if(opcao == 1)
            printf("(%c", raiz->letra);//imprime pre-ordem
        imprime(raiz->esq, opcao);
        if(opcao == 2)//imprime infixa
            printf("%c)", raiz->letra);
        imprime(raiz->dir, opcao);
        if(opcao == 1)
            printf(")");
    }
}


void imprimeFORB(PArv no){
    if(no != NULL){
        printf("%c ", no->letra);
        imprimeFORB(no->dir);
    }
}


void busca(PArv raiz,int opcao, char no){
    if(raiz != NULL){
        if(opcao == 3 && raiz->letra == no){
            imprimeFORB(raiz->esq);
            return;
        }
        if(opcao == 4 && raiz->letra == no){
            imprimeFORB(raiz);
            return;
        }
        busca(raiz->esq, opcao, no);
        busca(raiz->dir, opcao, no);
    }
}

void libera(PArv raiz){
    if(raiz != NULL){
        libera(raiz->esq);
        libera(raiz->dir);
        free(raiz);
    }
}

int main(){
    PArv raiz = NULL;
    FILE *farv;
    char pai;
    char filho, irmao;
    int nfilhos;
    int i;
    int opcao;
    farv = fopen("arv.txt", "r");
    if(farv == NULL){
        printf("\nNao foi possivel abrir o arquivo\n");
        return 0;
    }
    else
        printf("\nArquivo foi aberto para leitura\n\n");
    rewind(farv);
    while(!feof(farv)){
        fscanf(farv,"%c", &pai);
        if(raiz == NULL)
            raiz = cria(pai);
        fscanf(farv," %d", &nfilhos);
        for(i=0;i<nfilhos;i++){
            fscanf(farv," %c", &filho);
            insere(raiz, pai, filho, nfilhos);
        }
        fscanf(farv,"%c", &pai);
    }
    do{
        printf("\n\n1 - Imprimir a arvore resultante em pre-ordem\n2 - Imprimir a arvore resultante em ordem infixa\n3 - Imprimir os filhos de um dado no\n4 - Imprimir os irmao de um dado\n5 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            imprime(raiz,opcao);
            break;
        case 2:
            imprime(raiz,opcao);
            break;
        case 3:
            setbuf(stdin,NULL);
            printf("\nDe qual no deseja saber os filhos: ");
            setbuf(stdin,NULL);
            scanf("%c", &filho);
            printf("\nFilhos de %c: ", filho);
            busca(raiz,opcao,filho);
            break;
        case 4:
            setbuf(stdin,NULL);
            printf("\nDe qual no deseja saber os irmaos: ");
            setbuf(stdin,NULL);
            scanf("%c", &irmao);
            printf("\nIrmaos de %c: ",irmao);
            busca(raiz,opcao,irmao);
            break;
        case 5:
            libera(raiz);
            break;
        default:
            printf("\nOpcao invalida\n");
            break;
        }
    }while(opcao != 5);

return 0;
}
