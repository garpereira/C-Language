#include <stdio.h>
#include <string.h>

int main() {
    int i,j, escolha, conta=1, tamanho;
    char aluno[20];
    typedef struct{
        char nomes[20];
    }NOMES;
    NOMES nome[5];

    printf("Digite o Nome dos Alunos\n");
    scanf("%s",nome[0].nomes);
    while(conta<5){
        printf("Deseja adicionar mais Alunos a lista?\n\n0 Sim    1 Nao\n");
        scanf("%d", &escolha);
        if(escolha == 1){
            break;
        }
        printf("Digite o nome do Aluno\n");
        scanf("%s",nome[conta].nomes);
        conta++;
    }
    conta = 0;
    printf("Qual aluno deseja procurar?\n");
    scanf("%s", aluno);
    getchar();
    tamanho = strlen(aluno);
    for(i=0;i<5;i++) {
        for (j = 0; j < tamanho; j++) {
            if (aluno[j] == nome[i].nomes[j]) {
                conta++;
            }
        }
        if (conta == tamanho) {
            strcpy(aluno,nome[i].nomes);
            conta = 0;
            printf("\n%s",aluno);
            break;
        }
        conta=0;
    }
    return 0;
}