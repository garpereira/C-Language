#include <stdio.h>

int main() {
    char A[100], B[100], letra[100];
    int i, j, k, conta[100], soma=0;
    for(i=0;i<100;i++){
        conta[i] = 0;
    }
    printf("Digite seus caracteres da primeira cadeia\n");
    scanf("%[^\n]", A);
    getchar();
    printf("Digite seus caracteres da segunda cadeia\n");
    scanf("%[^\n]",B);
    getchar();
    for(i=0;A[i] != '\0';i++){
        for(j=0;B[j] != '\0';j++) {
            if(A[i] == B[j]) {
            letra[i] = A[i];
            conta[i] = conta[i] + 1;
            soma += conta[i];
            }
        }
    }
    for(i=0;letra[i] != '\0';i++){
        if(conta[i] > 0) {
            printf("A letra %c em A | Aparece %d vezes em B\n", letra[i], conta[i]);
        }
    }
    printf("Cadeia A, aparece %d vezes em B\n", soma);

    return 0;
}