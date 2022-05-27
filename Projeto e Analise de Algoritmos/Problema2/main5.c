#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 1000001

typedef struct{
  int *valor;
  int pos_atual;//posicao atual em que se encontra o menor valor do vetor
  int tam;
}Primario;

typedef struct{
  int valor;
  int pos_indice;
}Secundario;

void imprime1(Primario *primario, int k_itera){
  int i, j = 0;
  printf("\nIMPRIMINDO PRIMARIO...\n");
  for(i=0;i<k_itera;i++){
    if(primario[i].valor == NULL);
    else if(primario[i].pos_atual >= primario[i].tam);
    else{
      for(j=0;j<primario[i].tam;j++)
        printf("%d ",primario[i].valor[j]);
      printf("\n");
    }
  }
}

void imprime2(Secundario *secundario, int aux){
  int i;
  printf("\nIMPRIMINDO SECUNDARIO....\n");
  for(i=0;i<aux;i++){
    if(secundario[i].valor == MAX);
    else{
      printf("indice -> %d | valor -> %d\n",secundario[i].pos_indice,secundario[i].valor);
    }
  }
  printf("\n");
}


void lendo(Primario *primario, int k_itera, int stop, int *aux){
  if(stop >= k_itera)
    return;
  int N;
  scanf("%d", &N);
  if(N == 0){
    primario[stop].valor = (int*)malloc(sizeof(int));
    primario[stop].valor[0] = MAX;
    //primario[stop].valor = NULL;
    primario[stop].pos_atual = 0;
    primario[stop].tam = 0;
    *aux -= 1;
  }
  else{
    primario[stop].valor = (int*)malloc(sizeof(int)*N);
    int i;
    for(i=0;i<N;i++)
      scanf("%d",&primario[stop].valor[i]);
    primario[stop].pos_atual = 0;
    primario[stop].tam = N;
  }
  return lendo(primario, k_itera, stop+1, aux);
}

void cria_sec(Primario *primario, Secundario *secundario, int k_itera){
  int i, j = 0;
  for(i=0;i<k_itera;i++){
    if(primario[i].valor[0] == MAX);
    else if(primario[i].pos_atual >= primario[i].tam);
    else{
      secundario[j].valor = primario[i].valor[primario[i].pos_atual];
      secundario[j].pos_indice = i;
      j++;
    }
  }
}

void meuencontra(Primario *primario, Secundario *secundario,
int i, int j, int *max, int *min, int *indice){
  //printf("\nentrou no meuencontra uiui...");
    if(i == j){
      *max = secundario[i].valor;
      *min = secundario[i].valor;
      *indice = i;
    }
    else{
      if(i == j-1){
        if(secundario[i].valor < secundario[j].valor){
          *max = secundario[j].valor;
          *min = secundario[i].valor;
          *indice = i;
        }
        else{
          *max = secundario[i].valor;
          *min = secundario[j].valor;
          *indice = j;
        }
      }
      else{
        int mid = i+j/2;
        meuencontra(primario, secundario, i, mid, max, min, indice);
        int max1, min1, indice2;
        meuencontra(primario, secundario, mid+1, j, &max1, &min1, &indice2);
        if(*max < max1){
          *max = max1;
        }
        if(*min > min1){
          *min = min1;
          *indice = indice2;
        }
      }
    }    
  }

/*void MaxMin4(Primario *primario, Secundario *secundario, int Linf, int Lsup, int *Max, int *Min, int *indice){
  int Max1, Max2, Min1, Min2, Meio, indice1, indice2;
  if(Lsup - Linf <= 1){
    if(secundario[Linf].valor < secundario[Lsup].valor){
      *Max = secundario[Lsup].valor;
      *Min = secundario[Linf].valor;
      *indice = Linf;
    }
    else{
      *Max = secundario[Linf].valor;
      *Min = secundario[Lsup].valor;
      *indice = Lsup;
    }
    return;
  }
  Meio = (Linf + Lsup)/2;
  MaxMin4(primario, secundario, Linf, Meio, &Max1, &Min1, &indice1);
  MaxMin4(primario, secundario, Meio+1, Lsup, &Max2, &Min2, &indice2);
  if(Max1 > Max2){
    *Max = Max1;
  }
  else{
    *Max = Max2;
  }
  if(Min1 < Min2){
    *Min = Min1;
    *indice = indice1;
  }
  else{
    *Min = Min2;
    *indice = indice2;
  }
}*/

/*
void atualiza(Primario *primario, Secundario *secundario, int indice){
  //printf("\nATUALIZANDO...");
  int indicep = secundario[indice].pos_indice;
  primario[indicep].pos_atual += 1;
  if(primario[indicep].pos_atual >= primario[indicep].tam){
    primario[indicep].pos_atual = 0;
    primario[indicep].valor[0] = MAX;
    secundario[indice].valor = MAX;
  }
  else
    secundario[indice].valor = primario[indicep].valor[primario[indicep].pos_atual]; 
}*/


void MaxMin4(Primario *primario, int Linf, int Lsup, int *Max, int *Min, int *indice){
  int Max1, Max2, Min1, Min2, Meio, indice1, indice2;
  if(Lsup - Linf <= 1){
    if(primario[Linf].valor[primario[Linf].pos_atual] < primario[Lsup].valor[primario[Lsup].pos_atual]){
      *Max = primario[Lsup].valor[primario[Lsup].pos_atual];
      *Min = primario[Linf].valor[primario[Linf].pos_atual];
      *indice = Linf;
    }
    else{
      *Max = primario[Linf].valor[primario[Linf].pos_atual];
      *Min = primario[Lsup].valor[primario[Lsup].pos_atual];
      *indice = Lsup;
    }
    return;
  }
  Meio = (Linf + Lsup)/2;
  MaxMin4(primario, Linf, Meio, &Max1, &Min1, &indice1);
  MaxMin4(primario, Meio+1, Lsup, &Max2, &Min2, &indice2);
  if(Max1 > Max2){
    *Max = Max1;
  }
  else{
    *Max = Max2;
  }
  if(Min1 < Min2){
    *Min = Min1;
    *indice = indice1;
  }
  else{
    *Min = Min2;
    *indice = indice2;
  }
}


void atualiza(Primario *primario, Secundario *secundario, int indice){
  //printf("\nATUALIZANDO...");
  primario[indice].pos_atual += 1;
  if(primario[indice].pos_atual >= primario[indice].tam){
    primario[indice].pos_atual = 0;
    primario[indice].valor[0] = MAX;
  } 
}

unsigned long long soma(Primario *primario, int k_itera){
  int i;
  unsigned long long somador = 0;
  for(i=0;i<k_itera;i++){
    if(primario[i].valor[0] == MAX);
    else if(primario[i].pos_atual >= primario[i].tam);
    else{
      somador += primario[i].valor[primario[i].pos_atual];
    }
  }
  return somador;
}

unsigned long long soma2(Secundario *secundario, int aux){
  int i;
  unsigned long long somador = 0;
  for(i=0;i<aux;i++){
    if(secundario[i].valor == MAX);
    else
      somador+=secundario[i].valor;
  }
  return somador;
}

int main(){
  int k_itera, n_itera, aux, max, min, i, j, indice;
  unsigned long long resultado, resultado2;
  printf("\nok comecou\n");
  scanf("%d %d",&k_itera, &n_itera);
  Primario *primario;
  Secundario *secundario;
  primario = (Primario*)malloc(sizeof(Primario)*k_itera);
  aux = k_itera;
  lendo(primario,k_itera,0, &aux);
  //secundario = (Secundario*)malloc(sizeof(Secundario)*aux);
  //printf("\ncriando o cria sec com aux -> %d...", aux);
  //cria_sec(primario, secundario, k_itera);
  //printf("\ncriou\n");
  //imprime2(secundario,aux);
  for(i = 1; i<n_itera; i++){
    //printf("\nfoi meu encontra para i -> %d", i);
    MaxMin4(primario, 0, k_itera-1, &max, &min, &indice);
    //MaxMin4(primario, secundario, 0, aux-1, &max, &min, &indice);
    //meuencontra(primario, secundario, 0 ,aux-1, &max, &min, &indice);
    //printf("\nmax -> %d  min -> %d indice min -> %d", max, min, indice);
    atualiza(primario, secundario, indice);
    //imprime2(secundario, aux);
    //
  }
  //resultado = soma(primario, k_itera);
  //resultado2 = soma2(secundario, aux);
  //printf("\n");
  //printf("\nresultado1 -> %d",resultado);
  //printf("%llu",resultado);
  printf("\ncabo\n");
   //tempo = clock()-tempo;
 //printf("\ntempo -> %lf\n",(((double)tempo)/(CLOCKS_PER_SEC/1000)));
  return 0;
}


/*

5 1
7 7 7 9 10 13 18 20
3 2 4 4
4 3 4 8 9
5 3 8 9 9 10
4 9 12 20 23

5 2
7 7 7 9 10 13 18 20
3 2 4 4
4 3 4 8 9
5 3 8 9 9 10
4 9 12 20 23


5 4
3 126413 752631 946163
0
5 92683 456122 463803 687371 848812
1 404405
1 951157


5 5
1 1
1 2
1 3
1 4
1 5

5 5
3 126413 230000 270000
3 16000 80000 130000
3 240000 260000 300000
3 14000 50000 100000
3 900000 950000 999999

*/
