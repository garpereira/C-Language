#include <stdio.h>
#include <stdlib.h>


typedef struct{
  int taxa;
  int tamanho;
}Conj;

void ImprimeMatriz(int TamConj, int BlocoMax, int Matriz[TamConj][BlocoMax]){
  int i, j;
  for(i=0;i<TamConj;i++){
    for(j=0;j<BlocoMax;j++){
      printf("%d ",Matriz[i][j]);
    }
    printf("\n");
  }
}


int MontaTabela(Conj *ConjS, int TamConj, int BlocoMax){
  
  int Matriz[TamConj+1][BlocoMax+1];
  int i,j;
  for(i=0;i<=TamConj;i++)
    Matriz[i][0] = 0;
  for(i=1;i<=BlocoMax;i++)
    Matriz[0][i] = 0;

  for(i=1;i<=TamConj;i++){
    for(j=0;j<=BlocoMax;j++){
      //se o tamanho bytes dessa transacao for maior que o Blocoj entao é adicionado  a taxa anterior valida para este peso Matriz[i-1][j] na matriz
      if(ConjS[i-1].tamanho > j){
        Matriz[i][j] = Matriz[i-1][j];
      }
      else{
        //aqui definiremos duas variaveis que armazenam a maior Taxa na Matriz com base no Bloco(j)
        //atual e a taxa do ConjS(i) pois para o Bloco(j) atual, o tamanho do Bloco(i) não excede Bloco(j)
        /*em M1 é atribuido a soma da taxa atual que possui o tamanho menor que o Bloco(j) atual com a maior 
        taxa ja armazenada do Blocoj anterior que possui o menor tamanho, pois queremos que na ultima posicao
        tenha a soma de todas as maiores taxas que possuem o menor tamanho*/
        /*em M2 é atribuido a maior taxa atribuida anteriormente*/
        int M1 = ConjS[i-1].taxa + Matriz[i-1][j-ConjS[i-1].tamanho];
        int M2 = Matriz[i-1][j];
        /* como queremos que na ultima posicao tenha a soma de todas as maiores taxas que possuem o menor tamanho
        entao comparamos os dois resultados obtidos, como sabemos que os dois possuem o menor tamanho, então
        precisamos saber qual é a maior taxa para conseguirmos a solução ótima do problema*/
        if(M1 > M2)
          Matriz[i][j] = M1;
        else
          Matriz[i][j] = M2;
      }
    }
  }

  //ImprimeMatriz(TamConj+1,BlocoMax+1,Matriz);
  /*assim, com a matriz completa basta retornarmos o ultmo valor atribuido */
  return Matriz[TamConj][BlocoMax];
}

int main(){
  int TamConj, BlocoMax;
  int resultado;
  //printf("\nDigite quantas Ntransacoes e a Capacidade do bloco (N C): ");
  scanf("%d %d",&TamConj, &BlocoMax);

  Conj *ConjS;
  ConjS = (Conj*)malloc(sizeof(Conj)*TamConj);
  int i;
  //printf("\nDigite as Ntaxas e Ntamanhos das Ntransacoes\n");
  for(i=0;i<TamConj;i++){
    //printf("\nTransacao[%d]\nTaxa & Tamanho: ", i+1);
    scanf("%d %d",&ConjS[i].taxa, &ConjS[i].tamanho);
  }
  //printf("\nConjunto Preenchido.\n");

  resultado = MontaTabela(ConjS, TamConj, BlocoMax);
  printf("%d",resultado);
  return 0;
}


/*

4 5
4 2
5 2
2 1
8 3

  */