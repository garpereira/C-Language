#include <stdio.h>

int main(){
    int matriz[10][20], vetor[10], soma=0, i, j;
    printf("insira valores da matriz\n");
    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            scanf("%d", &matriz[i][j]);
            soma +=matriz[i][j];
        }
        vetor[i] = soma;
    }
    printf("resultado da matriz\n");
    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            printf("%d ",matriz[i][j]*vetor[i]);
        }
        printf("\n");
    }
    return 0;
}