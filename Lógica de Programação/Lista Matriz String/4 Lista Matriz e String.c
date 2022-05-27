#include <stdio.h>

int main() {
    int matriz[5][5], n, verdade=0;
    int i, j;

    printf("Digite valores da matriz\n");
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            scanf("%d", &matriz[i][j]);
        }
    }
    printf("Qual valor deseja encontrar\n");
    scanf("%d", &n);

    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(matriz[i][j] == n){
                printf("Valor %d se encontra na Linha %d e Coluna %d\n",n,i,j);
                verdade = 1;
            }
        }
    }
    if(verdade == 0){
        printf("Valor nao encontrado\n");
    }
    return 0;
}