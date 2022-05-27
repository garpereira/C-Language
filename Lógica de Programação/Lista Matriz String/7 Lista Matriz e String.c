#include <stdio.h>

int main(){
    float matriz[3][6], soma=0, soma2=0, media;
    int i, j;

    for(i=0;i<3;i++){
        for(j=0;j<6;j++){
            scanf("%f", &matriz[i][j]);
            if(j%2 == 0){
                soma += matriz[i][j];
            }
            if(j == 1 || j == 2){
                soma2 += matriz[i][j];
            }
        }
    }
    media = soma2/6;

    printf("A Soma das Colunas Impares: %.2f\n\nMedia Aritimerica da Segunda e Quarta Coluna: %.2f\n\n", soma, media);

    printf("Matriz modificada:\n");
    for(i=0;i<3;i++){
        for(j=0;j<6;j++){
            if(j == 5){
                matriz[i][j] = matriz[i][0] + matriz[i][1];
            }
            printf("%.2f ", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}