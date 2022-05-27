#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*
5 4
3 126413 752631 946163
0
5 92683 456122 463803 687371 848812
1 404405
1 951157
*/


typedef struct{
  int *vetor;
  int tam;
  int ini;
}sVetores;


void leitura_vetores(sVetores *vetor, int K, int controle){
  if(controle == K)
    return;
  int N;//n valores do vetor a ser lido
  int valor;
  scanf("%d",&N);
  if(N == 0)
    vetor[controle].vetor =  NULL;
  else{
    vetor[controle].vetor = (int*)malloc(N*sizeof(int));//alocacao no vetor a ser lido
    vetor[controle].tam = N;
    vetor[controle].ini = 0;
    int i;
    for(i=0;i<N;i++)
      scanf("%d",&vetor[controle].vetor[i]);//leitura de n valores
      
  }
  return leitura_vetores(vetor, K, controle+1);//
}

int pega_pmra_pos(sVetores *vetor, int n){
  //printf("\nentrou em pega_pmra_pos....");
  if(vetor[n].vetor == NULL)
    return pega_pmra_pos(vetor, n+1);
  return n;
}


int verifica_menor(sVetores *vetor, int *menor_indice, int i){
  //printf("\nentrou em verifica_menor...");
  if(vetor[*menor_indice].vetor == NULL)
    return i;
  if(vetor[i].vetor[vetor[i].ini] < vetor[*menor_indice].vetor[vetor[*menor_indice].ini]){
    //printf("\nretornou i -> %d", i);
    return i;
  }
  //printf("\nretornou o menor indice -> %d...",m_indice);
  return *menor_indice;
}


/*void removendo_menor_indice(sVetores *vetor, int m_indice){
  //printf("\nentrou em removendo_menor_indice...");
  int i;
  //printf("\npegando tamanho do vetor...");
  //int tam = pega_tam(aux, m_indice);
  int tam = vetor[m_indice].tam;
  //printf("\npegou tamanho -> %d...", tam);

  if(tam == 1 || tam == 0){
    //printf("\ntam == 1...");
    vetor[m_indice].vetor = NULL;
    return;
  }
  int *aux;
  aux = (int*)malloc((tam-1)*sizeof(int));
  //printf("\ncriou auxx...");
  for(i = 0; i < tam-1; i++){
    *(&aux[i]) = vetor[m_indice].vetor[i+1];//trocando endereços de memoria
    //printf("\ntrocou end de [ %d ] -> [ %d ]...", i, i+1);
  }
  //printf("\natribuindo em vetor o aux...");
  *(&vetor[m_indice].vetor) = aux;
  vetor[m_indice].tam -= 1;
  //printf("\natribuiu");
}
*/

void soma_soma(sVetores *vetor, unsigned long long *soma, int *menor_indice, int i, int K){
  if(i == K)
    return;
  if(vetor[i].vetor == NULL)
    return soma_soma(vetor, soma, menor_indice, i+1, K);
  *soma += vetor[i].vetor[vetor[i].ini];
  *menor_indice = verifica_menor(vetor, menor_indice, i);
  return soma_soma(vetor, soma, menor_indice, i+1, K);
  
}

unsigned long long soma_menor_indice(sVetores *vetor, int K, int I, int controle){
  //printf("\nentrou em soma_menor_indice...");
  int i = 0;
  //printf("\npegando a primeira pos....");
  int menor_indice = pega_pmra_pos(vetor, 0);
  //printf("\npegou a primeira pos -> %d....",menor_indice);
  unsigned long long soma = 0;
  soma_soma(vetor, &soma, &menor_indice, i, K);
  /*for(i=0;i<K;i++){
    //printf("\nentrou no for de soma_menor_indice para i -> %d",i);
    if(vetor[i].vetor == NULL);
    else{
      //printf("\nentrou no else de soma_menor_indice....");
      soma += vetor[i].vetor[vetor[i].ini];//somando as primeiras posicoes
      menor_indice = verifica_menor(vetor, menor_indice, i);
      //printf("\nsaiu de verifica_menor igual a -> %d...",menor_indice);
    }
    //printf("\nsaiu do else de soma_menor_indice....");
  }*/
  if(controle+1 == I)
    return soma;
  //printf("\niniciando removendo_menor_indice....");
  if(vetor[menor_indice].ini+1 < vetor[menor_indice].tam)
    vetor[menor_indice].ini +=1;
  else
    vetor[menor_indice].vetor = NULL;
  
  //removendo_menor_indice(vetor, menor_indice);
  //printf("\nsaiu de removendo_menor_indice....");
  //printf("\nrecursando soma_menor_indice....");
  return soma_menor_indice(vetor, K, I, controle+1);
}


int main(){
  int K, I, N;
  unsigned long long resultado = 0;
  sVetores *vetor;
  scanf("%d %d",&K, &I);
  vetor = (sVetores*)malloc(K*sizeof(sVetores));
  //printf("\nlendo os vetores...\n");
  leitura_vetores(vetor, K, 0);
  //printf("\nleu os vetores...");
  //printf("\niniciando soma_menor_indice...");
  resultado = soma_menor_indice(vetor, K, I, 0);
  //printf("\nsaiu de soma_menor_indice...");
  printf("%llu",resultado);

  return 0;
}