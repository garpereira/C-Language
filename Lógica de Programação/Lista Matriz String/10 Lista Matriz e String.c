#include <stdio.h>
#include <string.h>


int main(){
    char l1, l2, palavra[100];
    int i;
    printf("Digite palavra\n");
    scanf("%[^\n]", palavra);
    getchar();
    printf("qual letra deseja trocar\n");
    scanf("%c", &l1);
    getchar();
    printf("por qual letra deseja trocar\n");
    scanf("%c", &l2);

    for(i=0;palavra[i] != '\0';i++){
        if(palavra[i] == l1) {
            palavra[i] = l2;
        }
    }
    printf("entao a palavra eh: %s", palavra);

    return 0;
}