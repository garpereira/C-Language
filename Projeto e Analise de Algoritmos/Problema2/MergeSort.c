#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000
//estrutura utilizada do professor Andre Backes


void merge(int *vet,int inicio, int meio, int fim){
    int *vettemp;
    int fim1 = 0, fim2 = 0;
    int parte1,parte2;
    int tamanho;
    int i, j, k;
    tamanho = fim-inicio+1;
    parte1 = inicio;
    parte2 = meio+1;
    vettemp = (int *)malloc(tamanho*sizeof(int));
    if(vettemp != NULL){
        for(i=0;i<tamanho;i++){
            if(!fim1 && !fim2){//a exclamacao serve como NOT
                if(vet[parte1] < vet[parte2]){
                    vettemp[i] = vet[parte1++];
                }
                else
                    vettemp[i] = vet[parte2++];
                if(parte1>meio)
                    fim1=1;
                if(parte2>fim)
                    fim2=1;
            }
            else{
                if(!fim1){
                    vettemp[i] = vet[parte1++];
                }
                else{
                    vettemp[i] = vet[parte2++];
                }
            }
        }
        for(j=0,k=inicio;j<tamanho;j++,k++)
            vet[k] = vettemp[j];
    }
    free(vettemp);
}

void mergeSort(int *vet, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = (inicio+fim)/2;
        mergeSort(vet,inicio,meio);
        mergeSort(vet,meio+1,fim);
        merge(vet,inicio,meio,fim);
    }
}
int main(){
    int *vet;
    clock_t timer;
    int i,j,k,numb, K;
    scanf("%d", &numb);
    vet = (int *)malloc(numb*sizeof(int));
    srand(time(NULL));
    for(k=0;k<numb;k++){
        vet[k] = rand()%MAX;
        //scanf("%d",&vet[k]);
    }
    j = numb-1;
    i = 0;
    timer = clock();
    mergeSort(vet, i, j);
    timer = clock() - timer;
    //for(i=0;i<MAX;i++)
        //printf("%d ",vet[i]);
    free(vet);
    printf("\nTempo de execucao mergesort: %.2lf milissegundos",((double)timer)/((CLOCKS_PER_SEC/1000)));
return 0;
}
