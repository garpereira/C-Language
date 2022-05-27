#include <stdio.h>

int main(){
    int matriz[10][10], n, i, j;
    for(i=0;i<10;i++) {
        for (j = 0; j < 10; j++) {
            if (i < j) {
                matriz[i][j] = (2 * i) + (7 * j);
            } else if (i == j) {
                matriz[i][j] = (3 * i * 2) - 1;
            } else {
                matriz[i][j] = (4 * i * 3) - (5 * j * 2) + 1;
            }
            printf("[ %d ] ", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}