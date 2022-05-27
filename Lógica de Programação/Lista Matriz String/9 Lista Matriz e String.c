#include <stdio.h>

int main() {
    int i, menor, qualcarro;
    typedef struct{
        char modelo[100];
        int consumo;
    }CARRO;
    CARRO carros[5];

    for(i=0;i<5;i++){
        printf("Digite Modelo do Carro %d\n", i+1);
        scanf("%s", &carros[i].modelo);
        printf("Quantos KM por Litro faz\n");
        scanf("%d", &carros[i].consumo);
        printf("\n");
    }
    menor = carros[0].consumo;
    for(i=0;i<5;i++){
        if(carros[i].consumo > menor){
            menor = carros[i].consumo;
            qualcarro=i;
        }
    }
    printf("Carro mais Economico\n");
    printf("Modelo: %s\nKM por Litro: %d\n\n", carros[qualcarro].modelo,menor);

    printf("Gasto em 1000KM\n\n");
    for(i=0;i<5;i++){
        printf("Modelo: %s\nCombustivel Gasto: %.2f Litros\n\n", carros[i].modelo,1000.00/carros[i].consumo);
    }

    return 0;
}