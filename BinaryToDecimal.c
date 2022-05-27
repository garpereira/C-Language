//https://github.com/garpereira
#include <stdio.h>
#include <math.h>

int main(){
  long int binario;
  long int multip = 1;
  int contMultip = 0;
  int decimal = 0;
  scanf("%ld", &binario);
  do{
    if(binario-multip > 0){
      multip*=10;
      contMultip++;
    }
    else if(binario - multip <= 0){
      while(binario - multip < 0){
          multip/=10;
        contMultip--;
      }
      binario -= multip;
      decimal += pow(2,contMultip);
    }
  }while(binario != 0);

  printf("%d", decimal);
  return 0;
}

