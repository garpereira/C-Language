#include <stdio.h>

int main() {
    int i, j;
    typedef struct {
        int cidade[5];
        float distancia[5][5];
        float combustivel;
    } VIAGEM;
    VIAGEM viagem;
    printf("Digite os Codigos das Cidades\n");
    for (i = 0; i < 5; i++) {
        scanf("%d", &viagem.cidade[i]);
        while (viagem.cidade[i] < 0) {
            printf("Codigo invalido, tente novamente\n");
            scanf("%d", &viagem.cidade[i]);
        }
    }
    printf("Digite a distancia das cidades\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (j == i) {
                viagem.distancia[i][j] = 0;
            } else {
                scanf("%f", &viagem.distancia[i][j]);
                while (viagem.distancia[i][j] < 0) {
                    printf("Valor de distancia invalido, tente novamente\n");
                    scanf("%f", &viagem.distancia[i][j]);
                }
            }
        }
    }
    printf("Quantos KM seu Veiculo faz por Litro?\n");
    scanf("%f", &viagem.combustivel);

    for (i = 0; i < 5; i++) {
        printf("Cidade de Origem: %d\n\n", viagem.cidade[i]);
        for (j = 0; j < 5; j++) {
            if(viagem.distancia[i][j] < 250.00){
                printf("Cidade Destino: %d | KM de Distancia: %.2f\n", viagem.cidade[j],viagem.distancia[i][j]);
            }
        }
    }

    for(i = 0;i < 5;i++){
        printf("\nCidade de Origem: %d\nCidades Destino:\n", viagem.cidade[i]);
        for(j = 0; j < 5;j++){
            printf("Codigo %d\nTotal Gasto: %.2f\n\n", viagem.cidade[j], viagem.distancia[i][j]/ viagem.combustivel);
        }
    }

return 0;
}