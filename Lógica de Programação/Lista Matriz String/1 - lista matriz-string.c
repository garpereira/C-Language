#include <stdio.h>

int main(){
    int matriz[3][2], n, i, j;
    printf("insira valores da matriz\n");
    for(i=0;i<3;i++){
        for(j=0;j<2;j++){
            scanf("%d", &matriz[i][j]);
        }
    }
    printf("insira n qualquer inteiro\n");
    scanf("%d", &n);
    printf("resultado da multiplicacao\n");
    for(i=0;i<3;i++){
        for(j=0;j<2;j++){
            printf("%d ", matriz[i][j]*n);
        }
        printf("\n");
    }
    return 0;
}