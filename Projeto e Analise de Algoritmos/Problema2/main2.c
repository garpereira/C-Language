#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
5 1
7 7 7 9 10 13 18 20
3 2 4 4
4 3 4 8 9
5 3 8 9 9 10
4 9 12 20 23
*/

/*
5 2
7 7 7 9 10 13 18 20
3 2 4 4
4 3 4 8 9
5 3 8 9 9 10
4 9 12 20 23
*/

/*
5 4
3 126413 752631 946163
0
5 92683 456122 463803 687371 848812
1 404405
1 951157
*/

int aux = 0;
typedef struct{
  int *valor;
  int ini;
  int tam;
}sStruct;

typedef struct{
  int valor;
  int indice;
}sVetor;

void imprime(sStruct *main_vetor, int k){
  int i, j;
  for(i=0; i<k;i++){
    for(j=0;j<main_vetor[i].tam;j++)
      if(main_vetor[i].valor == NULL);
      else
        printf("%d ", main_vetor[i].valor[j]);
  }
}


void imprime2(sVetor *ord_vetor){
  int i;
  printf("\nPRINTANDO ORD VETOR....\n");
  for(i=0;i<aux;i++)
    printf("%d ",ord_vetor[i].valor);
}


void leitura(sStruct *main_vetor, int k, int controle){
  if(controle == k)
    return;
  int t_vetor, i;
  scanf("%d",&t_vetor);

  if(t_vetor == 0){
    main_vetor[k].valor = NULL;
    aux -= 1;
  }

  else{
    main_vetor[controle].valor = (int*)malloc(sizeof(int)*t_vetor);
    main_vetor[controle].ini = 0;
    main_vetor[controle].tam = t_vetor;

    for(i=0;i<t_vetor;i++)
      scanf("%d",&main_vetor[controle].valor[i]);
  }
  return leitura(main_vetor, k, controle+1);
}

sVetor * cria(sStruct *main_vetor, sVetor *ord_vetor, int k){
  int i, j = 0;
  ord_vetor = (sVetor*)malloc(sizeof(sVetor)*aux);
  for(i=0;i<k;i++){
    if(main_vetor[i].valor == NULL);
    else{
      ord_vetor[j].valor = main_vetor[i].valor[0];
      ord_vetor[j].indice = i;
      j++;
    }
  }
  //imprime2(ord_vetor);
  return ord_vetor;
}


int particiona(sVetor *ord_vetor, int inicio, int fim){
    int esq, dir;
    esq = inicio;
    dir = fim;
    sVetor *pivo, *auxiliar;
    pivo = (sVetor*)malloc(sizeof(sVetor));
    auxiliar = (sVetor*)malloc(sizeof(sVetor));
    *pivo = ord_vetor[inicio];
    while(esq < dir){
        while(ord_vetor[esq].valor <= pivo->valor)
            esq++;
        while(ord_vetor[dir].valor > pivo->valor)
            dir--;
        if(esq < dir){
            *auxiliar = ord_vetor[esq];
            ord_vetor[esq] = ord_vetor[dir];
            ord_vetor[dir] = *auxiliar;
        }
    }
    ord_vetor[inicio] = ord_vetor[dir];
    ord_vetor[dir] = *pivo;
    return dir;
}

void quicksort(sVetor *ord_vetor, int inicio, int fim){
    int pivo;
    if(fim > inicio){
        pivo = particiona(ord_vetor,inicio,fim);
        quicksort(ord_vetor,inicio,pivo-1);
        quicksort(ord_vetor,pivo+1,fim);
    }
}

void merge(sVetor *ord_vetor, int inicio, int meio, int fim){
  sVetor *temp;
  int p1, p2, tamanho, i, j, k;
  int fim1 = 0, fim2 = 0;
  tamanho = fim-inicio+1;
  p1 = inicio;
  p2 = meio+1;
  temp = (sVetor*)malloc(sizeof(sVetor)*tamanho);
  for(i=0; i<tamanho; i++){
    if(!fim1 && !fim2){
      if(ord_vetor[p1].valor < ord_vetor[p2].valor)
        temp[i] = ord_vetor[p1++];
      else
        temp[i] = ord_vetor[p2++];
      if(p1 > meio) fim1 = 1;
      if(p2 > fim) fim2 = 1;
    }
    else{
      if(!fim1)
        temp[i] = ord_vetor[p1++];
      else
        temp[i] = ord_vetor[p2++];
    }
  }
  for(j=0, k=inicio; j<tamanho; j++, k++)
    ord_vetor[k] = temp[j];
  free(temp);
}

void mergeSort(sVetor *ord_vetor, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio+fim)/2);
        mergeSort(ord_vetor,inicio,meio);
        mergeSort(ord_vetor,meio+1,fim);
        merge(ord_vetor,inicio,meio,fim);
    }
}


void insertion(sVetor *ord_vetor){//sera sempre linear apos a ordenacao pior caso N, melhor caso 1
  int i;
  sVetor *auxiliar;
  auxiliar = (sVetor*)malloc(sizeof(sVetor));
  for(i=0;i<aux-1;i++){
    if(ord_vetor[i].valor > ord_vetor[i+1].valor){
      *auxiliar = ord_vetor[i];
      ord_vetor[i] = ord_vetor[i+1];
      ord_vetor[i+1] = *auxiliar;
    }
    else
      break;
  }
}

void iterando(sVetor *ord_vetor, sStruct *main_vetor, int n_itera){
  if(n_itera == 0)
    return;
  int i = 0, j = 0;
  int main_indice = ord_vetor[j].indice;
  while(main_vetor[main_indice].ini + 1 >= main_vetor[main_indice].tam){
    main_vetor[main_indice].ini += 1;
    i++;
    j++;
    main_indice = ord_vetor[j].indice;//pegando a primeira posicao valida 
  }
  if(i >= n_itera)
    return;
    main_vetor[main_indice].ini += 1;
    ord_vetor[j].valor = main_vetor[main_indice].valor[main_vetor[main_indice].ini];//fazendo a troca do menor valor para o proximo valor do vetor atualizado em main_vetor
    insertion(ord_vetor);
    //main_indice = ord_vetor[j].indice;
    //imprime2(ord_vetor);
    return iterando(ord_vetor, main_vetor, n_itera-1);
}


unsigned long long soma(sVetor *ord_vetor, sStruct *main_vetor){
  int i;
  unsigned long long somador = 0;
  for(i=0;i<aux;i++){
    if(main_vetor[ord_vetor[i].indice].valor == NULL);
    else if(main_vetor[ord_vetor[i].indice].ini >= main_vetor[ord_vetor[i].indice].tam);
      //printf("\nini ->%d | tam -> %d", main_vetor[ord_vetor[i].indice].ini, main_vetor[ord_vetor[i].indice].tam);
    else{
      //printf("\nini ->%d | tam -> %d", main_vetor[ord_vetor[i].indice].ini, main_vetor[ord_vetor[i].indice].tam);
      somador += ord_vetor[i].valor;
    }
  }
  return somador;
}


int main(){
  sStruct *main_vetor;
  sVetor *ord_vetor;
  int k, i, n_itera;
  unsigned long long resultado;
  scanf("%d %d", &k, &n_itera);
  aux = k;
  main_vetor = (sStruct*)malloc(sizeof(sStruct)*k);
  leitura(main_vetor, k, 0);
  //imprime(main_vetor, k);
  //printf("\n");
  ord_vetor = cria(main_vetor, ord_vetor, k);
  mergeSort(ord_vetor, 0, aux-1);
  //quicksort(ord_vetor, 0, aux-1);
  //printf("\nSAIU DO QUICK");
  //imprime2(ord_vetor);
  iterando(ord_vetor, main_vetor, n_itera-1);
  resultado = soma(ord_vetor, main_vetor);
  printf("%llu",resultado);
  return 0;
}


/*
5 1
7 7 7 9 10 13 18 20
3 2 4 4
4 3 4 8 9
5 3 8 9 9 10
4 9 12 20 23
*/