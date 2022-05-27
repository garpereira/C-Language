#include <stdio.h>
#include <string.h>

int main() {
    char palavra[100];
    int i, tamanho;

    scanf("%[^\n]", palavra);
    tamanho = strlen(palavra);
    for(i = tamanho; i > -1 ;i--){
        printf("%c", palavra[i]);
    }
    return 0;
}