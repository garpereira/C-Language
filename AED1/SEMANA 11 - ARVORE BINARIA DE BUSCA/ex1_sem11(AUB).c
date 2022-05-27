#include <stdio.h>
#include <stdlib.h>

//Gabriel Almeida Rodrigues Pereira | RA: 143229 | Turma: Regina Celia Coelho

typedef struct arv{
    int chave;
    struct arv* dir;
    struct arv* esq;
}TArv;
typedef TArv *PArv;

PArv create(int NO){
    PArv novo = (PArv)malloc(sizeof(TArv));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->chave = NO;
    return novo;
}

PArv insere(PArv ABB, int NO){
    if(ABB == NULL){
        PArv novo = (PArv)malloc(sizeof(TArv));
        novo->chave = NO;
        novo->dir = NULL;
        novo->esq = NULL;
        ABB = novo;
        return ABB;
    }
    else if(ABB->chave > NO){//para verificar a funcao verifABB, basta mudar de > pra <
        //printf("NO [ %d ] ESQUERDA\n", NO);
        ABB->esq = insere(ABB->esq,NO);
    }
    else if(ABB->chave < NO){//para verificar a funcao verifABB, basta mudar de < pra >
        //printf("NO [ %d ] DIREITA\n", NO);
        ABB->dir = insere(ABB->dir,NO);
    }
    return ABB;
}

int verifABBD(PArv ABB, int NORAIZ){
    if(ABB != NULL){
        if(ABB->dir != NULL){
            if(ABB->chave > ABB->dir->chave || ABB->chave < NORAIZ){//verificamos se a chave é maior que a da direita, se for é invalido, tambem verificamos agora se a chave é MENOR que o noraiz, que tambem torna a ABB invalida, pois estamos lendo agora o lado DIREITO
                return 1;
            }
        }
        if(ABB->esq != NULL){
            if(ABB->chave < ABB->esq->chave || ABB->chave < NORAIZ){//verificamos se a chave é menor que a da esquerda, se for é invalido, tambem verificamos agora se a chave é MENOR que o noraiz, que tambem torna a ABB invalida, pois estamos lendo agora o lado DIREITO
                return 1;
            }
        }
        verifABBD(ABB->esq,NORAIZ);
        verifABBD(ABB->dir,NORAIZ);
    }
    return 0;
}


int verifABBE(PArv ABB, int NORAIZ){
    if(ABB != NULL){
        if(ABB->dir != NULL){
            if(ABB->chave > ABB->dir->chave || ABB->chave > NORAIZ){//verifico se a chave é maior que a da direita, se for é invalido, e tambem verifico se a chave é maior que o noraiz, se for, também é invalido, pois aqui estaremos visualizando todos a esquerda do no PAI
                return 1;
            }
        }
        if(ABB->esq != NULL){
            if(ABB->chave < ABB->esq->chave || ABB->chave > NORAIZ){//verifico se a chave é menor que a da esquerda, se for é invalido, e tambem verifico se a chave é maior que o noraiz, se for, tambem é invalido, pos aqui estamos verificando todo o lado esquerdo primeiro
                return 1;
            }
        }
        verifABBE(ABB->esq,NORAIZ);
        if(ABB->chave == NORAIZ){//apos terminar o lado esquerdo, o programa retorna ao noraiz para passar ao lado direito, aqui faremos a chamada da funcao verifABBD, que é a mesma estrutura do verifABBE, porem com algumas alteracoes
            if(verifABBD(ABB->dir, NORAIZ) == 1)//apos encerrar a busca por todo o lado esquerdo, ele voltara na raiz e lera o raiz-chave novamente, e terá que passar para o lado direito, aqui verificaremos todo o lado direito agora
                return 1;
            else
                return 0;
        }
        verifABBE(ABB->dir,NORAIZ);
    }
    return 0;
}

void uniao(PArv ABBA, PArv ABBB){
    if(ABBB != NULL){
        insere(ABBA ,ABBB->chave);
        uniao(ABBA, ABBB->esq);
        uniao(ABBA, ABBB->dir);
    }
}

void imprime(PArv ABB){
    if(ABB != NULL){
        printf("(%d", ABB->chave);
        imprime(ABB->esq);
        imprime(ABB->dir);
        printf(")");
    }
}

void destruct(PArv ABB){
    if(ABB != NULL){
        destruct(ABB->esq);
        destruct(ABB->dir);
        free(ABB);
    }
}

int main(){
    PArv ABBA = NULL;
    PArv ABBB = NULL;
    FILE *farvA, *farvB;
    int NO;
    farvA = fopen("arvA.txt", "r");
    farvB = fopen("arvB.txt", "r");
    if(farvA == NULL || farvB == NULL){
        printf("\nNao foi possivel abrir o arquivo\n");
        return 0;
    }
    else
        printf("\nArquivo pronto para leitura\n");

    while(!feof(farvA)){//criando arvore A
        fscanf(farvA,"%d ",&NO);
        if(ABBA == NULL)
            ABBA = create(NO);
        insere(ABBA, NO);
    }
    while(!feof(farvB)){//criando arvore B
        fscanf(farvB,"%d ",&NO);
        if(ABBB == NULL)
            ABBB = create(NO);
        insere(ABBB, NO);
    }
    printf("\nArvoreA: ");
    imprime(ABBA);
    printf("\nArvoreB: ");
    imprime(ABBB);
    uniao(ABBA,ABBB);
    printf("\nArvoreAB: ");
    imprime(ABBA);
    printf("\n\nArvore de Busca Binaria ");
    if(verifABBE(ABBA,ABBA->chave) == 1)
        printf("[ INVALIDA ]\n");
    else
        printf("[ VALIDA ]\n");
    destruct(ABBA);
    destruct(ABBB);
return 0;
}
