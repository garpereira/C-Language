#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Gabriel Almeida Rodrigues Pereira | RA: 143229 | Turma: Regina Celia Coelho

typedef struct{
    int idcandidato;
    int nota;
    char resposta;
}FILA;

void lendocandidatos(FILA *candidatos,int qtdcand){
    int i;
    for(i=0;i<qtdcand;i++){
        printf("\nID do candidato: ");
        scanf("%d", &candidatos[i].idcandidato);
        printf("\nNota do candidato: ");
        scanf("%d", &candidatos[i].nota);
        while(candidatos[i].nota <0 || candidatos[i].nota > 100){
            printf("\nNota invalida\nNota do candidato: ");
            scanf("%d", &candidatos[i].nota);
        }
    }
}

void organizando(FILA *candidatos, int qtdcand){
    int i, j;
    int aux;
    //bubble sort
    for(i=0;i<qtdcand;i++){
        for(j=0;j<qtdcand-1;j++){
            if(candidatos[j].nota < candidatos[j+1].nota){
                    //organizando nota
                aux = candidatos[j+1].nota;
                candidatos[j+1].nota = candidatos[j].nota;
                candidatos[j].nota = aux;
                    //organizando id
                aux = candidatos[j+1].idcandidato;
                candidatos[j+1].idcandidato = candidatos[j].idcandidato;
                candidatos[j].idcandidato = aux;
            }
        }
    }
}

void imprimelista(FILA *candidatos, int qtdcand){
    int i;
    for(i=0;i<qtdcand;i++){
        printf("\nID do candidato: %d, nota: %d\n",candidatos[i].idcandidato,candidatos[i].nota);
    }
}

void lendoresposta(FILA *candidatos,int qtdcand,int qtdvag, int *pvagas){
    int i;
    int vagas = 0;
    for(i=0;i<qtdcand;i++){
        printf("\nResposta candidato %d (s\\n): ",candidatos[i].idcandidato);
        scanf("%c",&candidatos[i].resposta);
        setbuf(stdin,NULL);
        if(candidatos[i].resposta == 's'){
            vagas++;
        }
        if(vagas == qtdvag){
            printf("\nVagas lotadas\n");
            break;
        }
        setbuf(stdin,NULL);
    }
    *pvagas = vagas;
}

int main(){
    int qtdcand;
    int qtdvag;
    int i;
    int vagas = 0;
    FILA *candidatos;
    printf("Quantos candidatos: ");
    scanf("%d", &qtdcand);
    printf("\nQuantas vagas: ");
    scanf("%d", &qtdvag);
    candidatos=(FILA*)malloc(qtdcand*sizeof(FILA));
    lendocandidatos(candidatos,qtdcand);
    organizando(candidatos,qtdcand);
    printf("\n|Lista dos Candidatos|\n");
    imprimelista(candidatos,qtdcand);
    setbuf(stdin,NULL);
    lendoresposta(candidatos,qtdcand,qtdvag,&vagas);
    if(vagas == 0){
        printf("\nNao ha novos alunos");
        return 0;
    }
    else{
        printf("\n|Lista novos alunos|\n");
        for(i=0;i<qtdcand;i++){
            if(candidatos[i].resposta == 's'){
                printf("\nID do candidato: %d\n", candidatos[i].idcandidato);
            }
        }
    }
return 0;
}
