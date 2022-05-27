#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define DIM 9
int menor_jogada = 10;

/*
//todas as 8 posiçoes
//pos[i+2][j-1] (+15)
//pos[i-1][j-2] (-10)
//pos[i-2][j-1] (-17)
//pos[i-2][j+1] (-15)
//pos[i+1][j+2] (+10)
//pos[i+1][j-2] (+6)
//pos[i-1][j+2] (-6)
//pos[i+2][j+1] (+17)
*/

typedef struct{
  int i;
  int j;
  int pos;
  int flag;
}Scavalo;

void cria_cavalo(Scavalo *cavalo, int tabuleiro[DIM][DIM]){
  int i, j;
  int cont = 1;
  for(i=1;i<=8;i++){
    for(j=1;j<=8;j++){
      tabuleiro[i][j] = cont;
      cavalo[cont].pos = cont;
      cavalo[cont].i = i;
      cavalo[cont].j = j;
      cavalo[cont].flag = 0;
      cont++;
    }
  }
}


//procura se há algum candidato disponivel
bool busca(int *peoes, int pos, int qtd_peoes){
  int i;
  for(i=0;i<qtd_peoes;i++){
    if(peoes[i] == pos){
      return true;
    }
  }
  return false;
}


//atualizando os peoes para a casa adiante
void atualiza_peoes(int *peoes, Scavalo *aux_cavalo, int qtd_peoes){
  int i;
  for(i=0;i<qtd_peoes;i++){
    if(peoes[i] <= 64 && aux_cavalo[peoes[i]].flag == 1);//se nesta posição de peão, o cavalo ja houver visitado, então não será necessario atualizar, pois o peao ja foi capturado
    else
      peoes[i] += 8;
  }
}

//retornando os peoes para suas casas anteriores
void desatualiza_peoes(int *peoes, Scavalo *aux_cavalo, int qtd_peoes){
  int i;
  for(i=0;i<qtd_peoes;i++){
    if(peoes[i] <= 64 && aux_cavalo[peoes[i]].flag == 1);//se nesta posição de peão, o cavalo ja houver visitado, então não será necessario atualizar, pois o peao ja foi capturado
    else
      peoes[i] -= 8;
  }
}

//montando o subconjunto disponivel em relação ao numero de peoes disponiveis(qtd_peoes) e o tamanho do subconjunto anterior(qtd_p)
void monta_sub(int *aux, int *peoes, Scavalo *aux_cavalo, int qtd_peoes, int qtd_ant){
  int i;
  int cont = 0;
  for(i=0;i<qtd_ant;i++){
    if(peoes[i] <= 64 && aux_cavalo[peoes[i]].flag == 1);
    else if(peoes[i] > 64);
    else{
      aux[cont] = peoes[i];
      cont++;
    }
  }
}

bool solucao(Scavalo *cavalo, int qtd_peoes, int pos_cavalo, int qtd_jogadas, int *peoes, int qtd_ant){
  Scavalo *aux_cavalo = cavalo;

  if(qtd_peoes == 0){//encontramos uma solução para este subconjunto
    printf("\nVENCEU FELAS | QTD PEOES -> %d | QTD JOGADAS -> %d\n", qtd_peoes, qtd_jogadas);
    if(qtd_jogadas < menor_jogada)
      menor_jogada = qtd_jogadas;
    return true;
  }
  else if(qtd_jogadas == 8){
    return false;
  }

  int *aux_peoes;
  aux_peoes = (int*)malloc(sizeof(int)*qtd_peoes);
  monta_sub(aux_peoes, peoes, aux_cavalo, qtd_peoes, qtd_ant);//monta subconjunto 
  int i, j;
  //utilizado para fazer as verificações das posições
  i = cavalo[pos_cavalo].i;
  j = cavalo[pos_cavalo].j;

  //pos[i+1][j-2] (+6)
  if(i+1 <= 8 && j-2 >= 1){//se a posição é valida para a pos_cavalo atual, então iremos verificar se existe peao
    if(busca(aux_peoes, pos_cavalo+6, qtd_peoes)){//se existir, então vamos recursar a função
      //peoes[k] = 0;
      aux_cavalo[pos_cavalo].flag = 1;//atualizo a posição dizendo que ja foi visitada
      atualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
      if(solucao(cavalo, qtd_peoes-1, pos_cavalo+6, qtd_jogadas+1, aux_peoes, qtd_peoes))
        return true;
      else
        desatualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
    }
    else
      aux_cavalo[pos_cavalo].flag = 0;//atualizo a posição dizendo que ja foi visitada
  }
  //pos[i+2][j-1] (+15)
  if(i+1 <= 8 && j-1 >= 1){
    if(busca(aux_peoes, pos_cavalo+15, qtd_peoes)){//se existir, então vamos recursar a função
      //peoes[k] = 0;
      aux_cavalo[pos_cavalo].flag = 1;//atualizo a posição dizendo que ja foi visitada
      atualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
      if(solucao(cavalo, qtd_peoes-1, pos_cavalo+15, qtd_jogadas+1, aux_peoes, qtd_peoes))
        return true;
      else
        desatualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
    }
  }
  //pos[i+2][j+1] (+17)
  if(i+2 <= 8 && j+1 <= 8){
    if(busca(aux_peoes, pos_cavalo+17, qtd_peoes)){//se existir, então vamos recursar a função
      //peoes[k] = 0;
      aux_cavalo[pos_cavalo].flag = 1;//atualizo a posição dizendo que ja foi visitada
      atualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
      if(solucao(cavalo, qtd_peoes-1, pos_cavalo+17, qtd_jogadas+1, aux_peoes, qtd_peoes))
        return true;
      else
        desatualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
    }
    else{
      aux_cavalo[pos_cavalo].flag = 0;//atualizo a posição dizendo que ja foi visitada
    }
  }
  //pos[i+1][j+2] (+10)
  if(i+1 <= 8 && j+2 <= 8){
    if(busca(aux_peoes, pos_cavalo+10, qtd_peoes)){//se existir, então vamos recursar a função
      //peoes[k] = 0;
      aux_cavalo[pos_cavalo].flag = 1;//atualizo a posição dizendo que ja foi visitada
      atualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
      if(solucao(cavalo, qtd_peoes-1, pos_cavalo+10, qtd_jogadas+1, aux_peoes, qtd_peoes))
        return true;
      else
        desatualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
    }
    else{
      aux_cavalo[pos_cavalo].flag = 0;//atualizo a posição dizendo que ja foi visitada
    }
  }
  //pos[i-1][j-2] (-10)
  if(i-1 >= 1 && j-2 >= 1){
    if(busca(aux_peoes, pos_cavalo-10, qtd_peoes)){//se existir, então vamos recursar a função
      //peoes[k] = 0;
      aux_cavalo[pos_cavalo].flag = 1;//atualizo a posição dizendo que ja foi visitada
      atualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
      if(solucao(cavalo, qtd_peoes-1, pos_cavalo-10, qtd_jogadas+1, aux_peoes, qtd_peoes))
        return true;
      else
        desatualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
    }
    else{
      aux_cavalo[pos_cavalo].flag = 0;//atualizo a posição dizendo que ja foi visitada
    }
  }
  //pos[i-2][j-1] (-17)
  if(i-2 >= 1 && j-1 >= 1){
    if(busca(aux_peoes, pos_cavalo-17, qtd_peoes)){//se existir, então vamos recursar a função
      //peoes[k] = 0;
      aux_cavalo[pos_cavalo].flag = 1;//atualizo a posição dizendo que ja foi visitada
      atualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
      if(solucao(cavalo, qtd_peoes-1, pos_cavalo-17, qtd_jogadas+1, aux_peoes, qtd_peoes))
        return true;
      else
        desatualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
    }
    else{
      aux_cavalo[pos_cavalo].flag = 0;//atualizo a posição dizendo que ja foi visitada
    }
  }
  //pos[i-2][j+1] (-15)
  if(i-2 >= 1 && j+1 <= 8){
    if(busca(aux_peoes, pos_cavalo-15, qtd_peoes)){//se existir, então vamos recursar a função
      //peoes[k] = 0;
      aux_cavalo[pos_cavalo].flag = 1;//atualizo a posição dizendo que ja foi visitada
      atualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
      if(solucao(cavalo, qtd_peoes-1, pos_cavalo-15, qtd_jogadas+1, aux_peoes, qtd_peoes))
        return true;
      else
        desatualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
    }
    else{
      aux_cavalo[pos_cavalo].flag = 0;//atualizo a posição dizendo que ja foi visitada
    }
  }
  //pos[i-1][j+2] (-6)
  if(i-1 >= 1 && j+2 <= 8){
    if(busca(aux_peoes, pos_cavalo-6, qtd_peoes)){//se existir, então vamos recursar a função
      //peoes[k] = 0;
      aux_cavalo[pos_cavalo].flag = 1;//atualizo a posição dizendo que ja foi visitada
      atualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
      if(solucao(cavalo, qtd_peoes-1, pos_cavalo-6, qtd_jogadas+1, aux_peoes, qtd_peoes))
        return true;
      else
        desatualiza_peoes(aux_peoes, aux_cavalo, qtd_peoes);
    }
    else{
      aux_cavalo[pos_cavalo].flag = 0;//atualizo a posição dizendo que ja foi visitada
    }
  }
  else{
    return false;
  }
}

void funcaoextrema(Scavalo *cavalo, int qtd_peoes, int pos_cavalo, int *peoes){
  int i, j;
  i = cavalo[pos_cavalo].i;
  j = cavalo[pos_cavalo].j;
  int qtd_jogadas = 0;
  int pos;
  int flag = 0;

  //caso base
  if(solucao(cavalo, qtd_peoes, pos_cavalo, qtd_jogadas, peoes, qtd_peoes)){
    flag = 1;
    printf("\nCavalo venceu em %d!\nNro Jogadas feitas -> %d",pos_cavalo, menor_jogada);
  }
  if(flag == 0){
    printf("\nNao venceu na base -> %d :(", pos_cavalo);
  }

  //pos[i+1][j-2] (+6)
  if(i+1 <= 8 && j-2 >= 1){
    pos = +6;
    qtd_jogadas = 0;
    atualiza_peoes(peoes, cavalo, qtd_peoes);
    if(solucao(cavalo, qtd_peoes, pos_cavalo+6, qtd_jogadas+1, peoes, qtd_peoes)){
      flag = 1;
      printf("\nCavalo venceu em +%d!\nNro Jogadas feitas -> %d",pos, menor_jogada);
    }
    else{
      desatualiza_peoes(peoes, cavalo, qtd_peoes);
      printf("\nNao venceu em %d :(", pos);
    }
  }
  //pos[i+2][j-1] (+15)
  if(i+1 <= 8 && j-1 >= 1){
    pos = +15;
    qtd_jogadas = 0;
    atualiza_peoes(peoes, cavalo, qtd_peoes);
    if(solucao(cavalo, qtd_peoes, pos_cavalo+15, qtd_jogadas+1, peoes, qtd_peoes)){
      flag = 1;
      printf("\nCavalo venceu em +%d!\nNro Jogadas feitas -> %d",pos, menor_jogada);
    }
    else{
      desatualiza_peoes(peoes, cavalo, qtd_peoes);
      printf("\nNao venceu em %d :(", pos);
    }
  }
  //pos[i+2][j+1] (+17)
  if(i+2 <= 8 && j+1 <= 8){
    pos = +17;
    qtd_jogadas = 0;
    atualiza_peoes(peoes, cavalo, qtd_peoes);
    if(solucao(cavalo, qtd_peoes, pos_cavalo+17, qtd_jogadas+1, peoes, qtd_peoes)){
      flag = 1;
      printf("\nCavalo venceu em +%d!\nNro Jogadas feitas -> %d",pos,menor_jogada);
    }
    else{
      desatualiza_peoes(peoes, cavalo, qtd_peoes);
      printf("\nNao venceu em %d :(", pos);
    }
  }
  //pos[i+1][j+2] (+10)
  if(i+1 <= 8 && j+2 <= 8){
    pos = +10;
    qtd_jogadas = 0;
    atualiza_peoes(peoes, cavalo, qtd_peoes);
    if(solucao(cavalo, qtd_peoes, pos_cavalo+10, qtd_jogadas+1, peoes, qtd_peoes)){
      flag = 1;
      printf("\nCavalo venceu em +%d!\nNro Jogadas feitas -> %d",pos,menor_jogada);
    }
    else{
      desatualiza_peoes(peoes, cavalo, qtd_peoes);
      printf("\nNao venceu em %d :(", pos);
    }
  }
  //pos[i-1][j-2] (-10)
  if(i-1 >= 1 && j-2 >= 1){
    pos = -10;
    qtd_jogadas = 0;
    atualiza_peoes(peoes, cavalo, qtd_peoes);
    if(solucao(cavalo, qtd_peoes, pos_cavalo-10, qtd_jogadas+1, peoes, qtd_peoes)){
      flag = 1;
      printf("\nCavalo venceu em -%d!\nNro Jogadas feitas -> %d",pos,menor_jogada);
    }
    else{
      desatualiza_peoes(peoes, cavalo, qtd_peoes);
      printf("\nNao venceu em %d :(", pos);
    }
  }
  //pos[i-2][j-1] (-17)
  if(i-2 >= 1 && j-1 >= 1){
    pos = -17;
    qtd_jogadas = 0;
    atualiza_peoes(peoes, cavalo, qtd_peoes);
    if(solucao(cavalo, qtd_peoes, pos_cavalo-17, qtd_jogadas+1, peoes, qtd_peoes)){
      flag = 1;
      printf("\nCavalo venceu em -%d!\nNro Jogadas feitas -> %d",pos,menor_jogada);
    }
    else{
      desatualiza_peoes(peoes, cavalo, qtd_peoes);
      printf("\nNao venceu em %d :(", pos);
    }
  }
  //pos[i-2][j+1] (-15)
  if(i-2 >= 1 && j+1 <= 8){
    pos = -15;
    qtd_jogadas = 0;
    atualiza_peoes(peoes, cavalo, qtd_peoes);
    if(solucao(cavalo, qtd_peoes, pos_cavalo-15, qtd_jogadas+1, peoes, qtd_peoes)){
      printf("\nCavalo venceu em -%d!\nNro Jogadas feitas -> %d",pos,menor_jogada);
    }
    else{
      desatualiza_peoes(peoes, cavalo, qtd_peoes);
      printf("\nNao venceu em %d :(", pos);
    }
  }
  //pos[i-1][j+2] (-6)
  if(i-1 >= 1 && j+2 <= 8){
    pos = -6;
    qtd_jogadas = 0;
    atualiza_peoes(peoes, cavalo, qtd_peoes);
    if(solucao(cavalo, qtd_peoes, pos_cavalo-6, qtd_jogadas+1, peoes, qtd_peoes)){
      printf("\nCavalo venceu em -%d!\nNro Jogadas feitas -> %d",pos,menor_jogada);
    }
    else{
      desatualiza_peoes(peoes, cavalo, qtd_peoes);
      printf("\nNao venceu em %d :(", pos);
    }
  }
  else{
    if(flag == 0)
      printf("\nimpossible");
  }
}

int main(){
  int qtd_peoes, pos_cavalo;
  int *peoes;
  int tabuleiro[DIM][DIM];
  int i;
  Scavalo *dados_cavalo;
  printf("\nInforme a quantidade de peoes: ");
  scanf("%d",&qtd_peoes);

  peoes = (int*)malloc(sizeof(int)*qtd_peoes);
  for(i=0;i<qtd_peoes;i++){
    printf("\nDigite a posicao do peao %d -> ", i+1);
    scanf("%d",&peoes[i]);
  }

  printf("\nDigite a posicao do Cavalo -> ");
  scanf("%d",&pos_cavalo);
  dados_cavalo = (Scavalo*)malloc(sizeof(Scavalo)*65);//considerar 1 a 64(mais facil para implementacao)
  cria_cavalo(dados_cavalo, tabuleiro);

  /*
  printf("\nImprimindo as informacoes do cavalo...\n");
  for(i=1;i<65;i++){
    printf("\ncavalo pos -> %d | i -> %d | j -> %d",dados_cavalo[i].pos, dados_cavalo[i].i, dados_cavalo[i].j);
  }*/
  funcaoextrema(dados_cavalo, qtd_peoes, pos_cavalo, peoes);
  printf("\nMenor jogada armazenada -> %d",menor_jogada);
  return 0;
}