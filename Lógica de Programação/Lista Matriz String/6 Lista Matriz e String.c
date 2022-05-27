#include <stdio.h>

int main() {
    int i, j, acertos=0;
    typedef struct {
        char respostas[5][10];
        char gabarito[10];
        int acertos[5];
    }NOTAS;
    NOTAS prova;
    for(i=0;i<5;i++){
        printf("\nRespostas Aluno %d:\n", i+1);
        for(j=0;j<10;j++){
            scanf("%c", &prova.respostas[i][j]);
        }
    }
    printf("Digite o Gabarito\n");
    for(i=0;i<10;i++){
            scanf("%c", &prova.gabarito[i]);
    }
    printf("\nResultado:\n");
    for(i=0;i<5;i++){
        printf("\nAluno %d: ", i+1);
        for(j=0;j<10;j++){
            if(prova.respostas[i][j] == prova.gabarito[j]){
                acertos++;
            }
        }
        prova.acertos[i] = acertos;
        printf("%d pontos.\n", prova.acertos[i]);
        acertos=0;
    }
    return 0;
}