#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIM 8

int menor_jogada = 10;
int qtd_p;

typedef struct cavalo{
  int i;
  int j;
  int pos;
  struct cavalo *posicao;
}Scavalo;

Scavalo* inicia(Scavalo *cavalo, int pos){
  if(pos < 1 || pos > 64){
    //printf("\na pos coisou -> %d", pos);
    return cavalo;
  }
  if(cavalo == NULL){
    cavalo = (Scavalo*)malloc(sizeof(Scavalo));
    cavalo->pos = pos;
    cavalo->posicao = NULL;
    return cavalo;
  }
  else{
    cavalo->posicao = inicia(cavalo->posicao, pos);
    return cavalo;
  }
  return cavalo;
}

bool busca(int *vet, int pos, int *k){//busca peoes linear
  int i;
  for(i=0;i<qtd_p;i++)
    if(pos == vet[i]){
      *k = i;
      return true;
    }
  return false;
}

void atualiza_peoes(int *peoes){
  int i = 0;
  for(i=0;i<qtd_p;i++){
    if(peoes[i] > 0)
      peoes[i] += 8;
    if(peoes[i] > 64)
      peoes[i] = -100;
  }
}
/*
todas as 8 posiçoes
pos[i+2][j-1] (+15)
pos[i-1][j-2] (-10)
pos[i-2][j-1] (-17)
pos[i-2][j+1] (-15)
pos[i+1][j+2] (+10)
pos[i+1][j-2] (+6)
pos[i-1][j+2] (-6)
pos[i+2][j+1] (+17)
*/

void backtracking(Scavalo *cavalo, int pos_cavalo, int *peoes, int qtd_peoes, int qtd_jogadas){
  printf("\nPEAO NA POSICAO -> %d | QTD_JOGADAS -> %d",pos_cavalo, qtd_jogadas);
  if(qtd_peoes == 0 && qtd_jogadas == 8){//entao quer dizer que cavalo venceu felas
    //verificamos se foi a menor jogada
    if(qtd_jogadas < menor_jogada)
      menor_jogada = qtd_jogadas;
    return;
  }
  else if(qtd_peoes == 0){//cavalo capturou todos os peoes
    if(qtd_jogadas < menor_jogada)
      menor_jogada = qtd_jogadas;
    return;
  }
  else if(qtd_jogadas == 8){//limite de jogadas alcançado sem capturar todos peoes
    return;
  }
  int i,j, k = 0;
  int *aux_vet;
  pos_cavalo -= 1;
  //necessarios para a validação das posições
  i = cavalo[pos_cavalo].i;
  j = cavalo[pos_cavalo].j;
  //pos[i+2][j-1] (+15)
  if(i+2 <= 7 && j-1 >= 0){//(+15)posição valida
    //buscamos então se nesta posição há um peao
    if(busca(peoes, cavalo[pos_cavalo].pos+15, &k)){//busca no vetor peoes, se há alguma posição equivalente a que o cavalo pode assumir
      //se encontrou então atualizamos o vetor de peoes e recursamos o cavalo com a nova posição, atualizando a quantidade jogadas e diminuindo a qtde de peoes
      peoes[k] = 0;
      //atualizamos a posição dos peoes
      atualiza_peoes(peoes);
      backtracking(cavalo, cavalo[pos_cavalo].pos+15, peoes, qtd_peoes-1, qtd_jogadas+1);
    }
  }

  //pos[i-1][j-2] (-10)
  if(i-1 >=0 && j-2 >= 0){
    if(busca(peoes, cavalo[pos_cavalo].pos-10, &k)){
      peoes[k] = 0;
      atualiza_peoes(peoes);
      backtracking(cavalo, cavalo[pos_cavalo].pos-10, peoes, qtd_peoes-1, qtd_jogadas+1);
    }
  }

  //pos[i-2][j-1] (-17)
  if(i-2 >= 0 && j-1 >= 0){
    if(busca(peoes, cavalo[pos_cavalo].pos-17, &k)){
      peoes[k] = 0;
      atualiza_peoes(peoes);
      backtracking(cavalo, cavalo[pos_cavalo].pos-17, peoes, qtd_peoes-1, qtd_jogadas+1);
    }
  }

  //pos[i-2][j+1] (-15)
  if(i-2 >= 0 && j+1 <= 7){
    if(busca(peoes, cavalo[pos_cavalo].pos-15, &k)){
      peoes[k] = 0;
      atualiza_peoes(peoes);
      backtracking(cavalo, cavalo[pos_cavalo].pos-15, peoes, qtd_peoes-1, qtd_jogadas+1);
    }
  }

  //pos[i+1][j+2] (+10)
  if(i+1 <= 7 && j+2 <= 7){
    if(busca(peoes, cavalo[pos_cavalo].pos+10, &k)){
      peoes[k] = 0;
      atualiza_peoes(peoes);
      backtracking(cavalo, cavalo[pos_cavalo].pos+10, peoes, qtd_peoes-1, qtd_jogadas+1);
    }
  }

  //pos[i+1][j-2] (+6)
  if(i+1 <= 7 && j-2 >=  0){
    if(busca(peoes, cavalo[pos_cavalo].pos+6, &k)){
      peoes[k] = 0;
      atualiza_peoes(peoes);
      backtracking(cavalo, cavalo[pos_cavalo].pos+6, peoes, qtd_peoes-1, qtd_jogadas+1);
    }
  }

  //pos[i-1][j+2] (-6)
  if(i-1 >= 0 && j+2 <= 7){
    if(busca(peoes, cavalo[pos_cavalo].pos-6, &k)){
      peoes[k] = 0;
      atualiza_peoes(peoes);
      backtracking(cavalo, cavalo[pos_cavalo].pos-6, peoes, qtd_peoes-1, qtd_jogadas+1);
    }
  }

  //pos[i+2][j+1] (+17)
  if(i+2 <= 7 && j+1 <= 7){
    if(busca(peoes, cavalo[pos_cavalo].pos+17, &k)){
      peoes[k] = 0;
      atualiza_peoes(peoes);
      backtracking(cavalo, cavalo[pos_cavalo].pos+17, peoes, qtd_peoes-1, qtd_jogadas+1);
    }
  }
}

/*
todas as 8 posiçoes
pos[i+2][j-1] (+15)
pos[i-1][j-2] (-10)
pos[i-2][j-1] (-17)
pos[i-2][j+1] (-15)
pos[i+1][j+2] (+10)
pos[i+1][j-2] (+6)
pos[i-1][j+2] (-6)
pos[i+2][j+1] (+17)
*/

void caca_peoes(Scavalo *cavalo, int pos_cavalo, int *peoes, int qtd_peoes, int qtd_jogadas){//funcao necessaria para verificação em cada direção, caso a primaria nao encontre nenhum peao
  int aux_pos = pos_cavalo;
  int i, j;
  int *aux_peoes;
  i = cavalo[aux_pos].i;
  j = cavalo[aux_pos].j;
  if(qtd_jogadas == 8)
    return;
  backtracking(cavalo, pos_cavalo, peoes, qtd_peoes, qtd_jogadas);
  //verificamos para quais posições o cavalo de posição inicial pode andar
  if(i+2 <= 7 && j-1 >= 0){
    aux_peoes = peoes;
    atualiza_peoes(aux_peoes);
    caca_peoes(cavalo, aux_pos+15, aux_peoes, qtd_peoes, qtd_jogadas+1);
    //backtracking(cavalo, aux_pos+15, aux_peoes, qtd_peoes, qtd_jogadas+1);
  }
  if(i-1 >=0 && j-2 >= 0){
    aux_peoes = peoes;
    atualiza_peoes(aux_peoes);
    caca_peoes(cavalo, aux_pos-10, aux_peoes, qtd_peoes, qtd_jogadas+1);
    //backtracking(cavalo, aux_pos-10, aux_peoes, qtd_peoes, qtd_jogadas+1);
  }
  if(i-2 >= 0 && j-1 >= 0){
    aux_peoes = peoes;
    atualiza_peoes(aux_peoes);
    caca_peoes(cavalo, aux_pos-17, aux_peoes, qtd_peoes, qtd_jogadas+1);
    //backtracking(cavalo, aux_pos-17, aux_peoes, qtd_peoes, qtd_jogadas+1);
  }
  if(i-2 >= 0 && j+1 <= 7){
    aux_peoes = peoes;
    atualiza_peoes(aux_peoes);
    caca_peoes(cavalo, aux_pos-15, aux_peoes, qtd_peoes, qtd_jogadas+1);
    //backtracking(cavalo, aux_pos-15, aux_peoes, qtd_peoes, qtd_jogadas+1);
  }
  if(i+1 <= 7 && j+2 <= 7){
    aux_peoes = peoes;
    atualiza_peoes(aux_peoes);
    caca_peoes(cavalo, aux_pos+10, aux_peoes, qtd_peoes, qtd_jogadas+1);
    //backtracking(cavalo, aux_pos+10, aux_peoes, qtd_peoes, qtd_jogadas+1);
  }
  if(i+1 <= 7 && j-2 >=  0){
    aux_peoes = peoes;
    atualiza_peoes(aux_peoes);
    caca_peoes(cavalo, aux_pos+6, aux_peoes, qtd_peoes, qtd_jogadas+1);
    //backtracking(cavalo, aux_pos+6, aux_peoes, qtd_peoes, qtd_jogadas+1);
  }
  if(i-1 >= 0 && j+2 <= 7){
    aux_peoes = peoes;
    atualiza_peoes(aux_peoes);
    caca_peoes(cavalo, aux_pos-6, aux_peoes, qtd_peoes, qtd_jogadas+1);
    //backtracking(cavalo, aux_pos-6, aux_peoes, qtd_peoes, qtd_jogadas+1);
  }
  if(i+2 <= 7 && j+1 <= 7){
    aux_peoes = peoes;
    atualiza_peoes(aux_peoes);
    caca_peoes(cavalo, aux_pos+17, aux_peoes, qtd_peoes, qtd_jogadas+1);
    //backtracking(cavalo, aux_pos+17, aux_peoes, qtd_peoes, qtd_jogadas+1);
  }
}


void preenche_tab(int tabuleiro[DIM][DIM], Scavalo *cavalo){
  int i, j;
  int cont = 1;
  for(i=0;i<DIM;i++){
    for(j=0;j<DIM;j++){
      tabuleiro[i][j] = cont;
      cavalo[cont-1].pos = cont;
      cavalo[cont-1].i = i;
      cavalo[cont-1].j = j;
      cavalo[cont-1].posicao = NULL;
      //printf("%d ", cont);
      cont++;
    }
    //printf("\n");
  }
}

void imprime(Scavalo *cavalo){
   if(cavalo != NULL){
        printf("%d",cavalo->pos);
        if(cavalo->posicao == NULL);
        else
        printf(", ");
        imprime(cavalo->posicao);
    }
}

int main(){
  Scavalo *cavalo;
  cavalo = (Scavalo*)malloc(sizeof(Scavalo)*64);
  int tabuleiro[DIM][DIM];
  printf("\nPreenchendo o Tabuleiro e Cavalo...\n");
  preenche_tab(tabuleiro, cavalo);

  int qtd_peoes;
  int *pos_peoes;
  printf("\nDigite a quantidade de Peoes: ");
  scanf("%d",&qtd_peoes);
  qtd_p = qtd_peoes;
  pos_peoes = (int*)malloc(sizeof(int)*qtd_peoes);
  int i;
  printf("\nAgora digite suas posicoes\n");
  for(i=0;i<qtd_peoes;i++){
    printf("\nPeao[%d] -> ",i+1);
    scanf("%d",&pos_peoes[i]);
  }
  int pos_cavalo;
  printf("\nDigite a posicao do Cavalo: ");
  scanf("%d",&pos_cavalo);

  int qtd_jogadas = 0;
  printf("\nIniciando o Backtracking...");
  //backtracking(cavalo, pos_cavalo, pos_peoes, qtd_peoes, qtd_jogadas);
  caca_peoes(cavalo, pos_cavalo, pos_peoes, qtd_peoes, qtd_jogadas);
  printf("\nTerminou.\n");
  //printf("%d\n",menor_jogada);
  if(menor_jogada < 10)
    printf("%d\n",menor_jogada);
  else
    printf("impossible\n");
  return 0;
}

/*
todas as 8 posiçoes
pos[i+2][j-1] (+15)
pos[i-1][j-2] (-10)
pos[i-2][j-1] (-17)
pos[i-2][j+1] (-15)
pos[i+1[j+2] (+10)
pos[i+1[j-2] (+6)
pos[i-1][j+2] (-6)
pos[i+2][j+1] (+17)
*/