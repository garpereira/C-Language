#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct horse{
  int i;
  int j;
  int pos;
  struct horse *posicao;
  int flag;
}Cavalo;

//funcao que gera as posicoes do cavalo no tabuleiro com suas respectivas posicoes
void cria_cavalo(Cavalo *cavalo){
  int i, j;
  int cont = 1;
  for(i=1;i<=8;i++){
    for(j=1;j<=8;j++){
      cavalo[cont].i = i;
      cavalo[cont].j = j;
      cavalo[cont].pos = cont;
      cavalo[cont].flag = 0;
      cavalo[cont].posicao = NULL;
      cont++;
    }
  }
}


Cavalo* inicia(Cavalo *cavalo, int pos){
  if(pos < 1 || pos > 64){
    //printf("\na pos coisou -> %d", pos);
    return cavalo;
  }
  if(cavalo == NULL){
    cavalo = (Cavalo*)malloc(sizeof(Cavalo));
    cavalo->pos = pos;
    cavalo->flag = 0;
    cavalo->posicao = NULL;
    return cavalo;
  }
  else{
    cavalo->posicao = inicia(cavalo->posicao, pos);
    return cavalo;
  }
  return cavalo;
}

//funcao responsavel pela criacao dos subconjuntos para cada posicao do cavalo
Cavalo* gerando_sub(Cavalo *cavalo){
  int k;
  for(k=1;k<65;k++){
    int i, j;
    i = cavalo[k].i;
    j = cavalo[k].j;
    Cavalo *aux;
    aux = cavalo[k].posicao;
    //printf("\ni -> %d | j -> %d",i,j);
    //pos[i+2][j-1] (+15)
    if(i+2 <= 8 && j-1 >= 1){
      cavalo[k].posicao = inicia(aux, cavalo[k].pos+15);
    }
    
    aux = cavalo[k].posicao;
    if(i-1 >= 1 && j-2 >= 1){
      cavalo[k].posicao = inicia(aux, cavalo[k].pos-10);
    }
    
    aux = cavalo[k].posicao;
    if(i-2 >= 1 && j-1 >= 1){
      cavalo[k].posicao = inicia(aux, cavalo[k].pos-17);
    }
    
    aux = cavalo[k].posicao;
    if(i-2 >= 1 && j+1 <=8){
      cavalo[k].posicao = inicia(aux, cavalo[k].pos-15);
    }
    
    aux = cavalo[k].posicao;
    if(i+1 <= 8 && j+2 <= 8){
      cavalo[k].posicao = inicia(aux, cavalo[k].pos+10);
    }
    
    aux = cavalo[k].posicao;
    if(i+1 <= 8 && j-2 >= 1){
      cavalo[k].posicao = inicia(aux, cavalo[k].pos+6);
    }
    
    aux = cavalo[k].posicao;
    if(i-1 >=1 && j+2 <=8){
      cavalo[k].posicao = inicia(aux, cavalo[k].pos-6);
    }
    
    aux = cavalo[k].posicao;
    if(i+2 <= 8 && j+1 <= 8){
      cavalo[k].posicao = inicia(aux, cavalo[k].pos+17);
    }
  }
  return cavalo;
}

void atualiza(int *peoes, int n_peoes){
  int cont = 0;
  int i=0;
  while(cont < n_peoes){
    if(peoes[i] == 0 || peoes[i] > 64);
    else{
      peoes[i] += 8;
      cont++;
    }
    i++;
  }
}

void desatualiza(int *peoes, int n_peoes){
  int cont = 0;
  int i=0;
  while(cont < n_peoes){
    if(peoes[i] == 0);
    else{
      peoes[i] -= 8;
      cont++;
    }
    i++;
  }
}

void poda(Cavalo *cavalo){
  if(cavalo == NULL)
    return;
  poda(cavalo->posicao);
  cavalo = NULL;
}
//se encontrarmos pelo menos 1 peao em um dos elementos desse subconjunto pesquisado, então este subconjunto é solucao
//para algum Kpeao
bool busca(Cavalo *cavalo, int *peoes, int n_peoes){
  printf("\nENTROU NA BUSCA\n");
  if(cavalo == NULL){//quer dizer que nao encontramos nenhum valor do subconjunto que seja um peao
    return false;
  }
  int cont = 0;
  int i = 0;
  while(cont < n_peoes){
    if(peoes[i] == cavalo->pos){//se encontrarmos um valor que corresponda a um peão
      peoes[i] = 0;//retiramos o peao
      printf("\nENCONTROU NA POS %d", cavalo->pos);
      return true;
    }
    if(peoes[i] == 0);
    else{
      cont++;
    }
    i++;
  }
  return busca(cavalo->posicao, peoes, n_peoes);
}
//essa funcao precisa verificar se é possível encontrar uma solucao para os cavalos
//queremos verificar nesta função, as posicoes candidatas a ter um peao
//para isso, necessitamos verificar em cada cavalo[pos_cavalo].posicao->pos/cada cavalo[pos_cavalo].posicao
void encontra_solucao(Cavalo *cavalo, int pos_cavalo, int *peoes, int n_peoes, int n_jogadas, int *menor_jogada){
  printf("\nENTROU NO SOLUCAO | N JOGADAS -> %d | N PEOES -> %d | POS CAVALO -> %d", n_jogadas, n_peoes, pos_cavalo);
  if(n_peoes == 0){
    if(n_jogadas < *menor_jogada)
      *menor_jogada = n_jogadas;
    printf("\nVENCEU! | N JOGADAS -> %d",n_jogadas);
    return;
  }
  else if(n_jogadas == 8){
    return;
  }
  //agora queremos fazer essa busca de soluções até que zeremos os peoes do tabuleiro
  Cavalo *aux = (Cavalo*)malloc(sizeof(Cavalo));
  aux = &cavalo[pos_cavalo];
  if(busca(aux->posicao, peoes, n_peoes)){//se encontrarmos algum elemento que seja solução para este subconjunto
    //entao atualizamos os peoes e recursamos a funcao para todos elementos dessa posicao
    atualiza(peoes, n_peoes);
    aux = aux->posicao;
    while(aux != NULL){
      encontra_solucao(cavalo, aux->pos, peoes, n_peoes-1, n_jogadas+1, menor_jogada);
      aux = aux->posicao;
    }
    //podemos realizar a poda deste subconjunto, pois ele ja foi visitado
    //poda(cavalo[pos_cavalo].posicao);
    desatualiza(peoes, n_peoes);
    return;
  }
  //e se nao enconrtarmos nenhum elemento do subconjunto que seja uma solução?
  //entao teremos que assumir cada elemento do subconjunto como um possivel subconjunto de soluções
  else{
    aux = aux->posicao;
    if(aux == NULL);
    else{
      atualiza(peoes, n_peoes);
      while(aux != NULL){
        encontra_solucao(cavalo, aux->pos, peoes, n_peoes, n_jogadas+1, menor_jogada);
        aux = aux->posicao;
      }
      //apos a visita dos candidatos, podemos podar
      //poda(cavalo[pos_cavalo].posicao);
    }
  }
}

void imprime(Cavalo *cavalo){
   if(cavalo != NULL){
        printf("%d",cavalo->pos);
        if(cavalo->posicao == NULL);
        else
        printf(", ");
        imprime(cavalo->posicao);
    }
}


// objetivo da atividade é testar os casos em que o peao pode andar, e se em
 //algum subconjunto é encontrado a solução
int main(){
  Cavalo *cavalo;
  int pos_cavalo;
  int i;

  //precisamos ler as posições dos peoes que estao no tabuleiro
  int *peoes;
  int n_peoes;
  printf("\nInsira a quantidade de peoes -> ");
  scanf("%d",&n_peoes);
  peoes = (int*)malloc(sizeof(int)*n_peoes);
  for(i=0;i<n_peoes;i++){
    printf("\nDigite a posicao para peao %d -> ",i+1);
    scanf("%d",&peoes[i]);
  }

  //precisamos armazenas as posições que o cavalo pode andar ou seja (1 a 64)
  printf("\nDigite a posicao inicial do Cavalo -> ");
  scanf("%d",&pos_cavalo);
  cavalo = (Cavalo*)malloc(sizeof(Cavalo)*65);

  printf("\nCRIANDO CAVALO...");
  cria_cavalo(cavalo);//armazenna pos, com i e j

  printf("\nGERANDO SUB CONJUNTOS...\n");
  cavalo = gerando_sub(cavalo);//gera os subconjuntos de cada posicao

  //com os subconjuntos gerados, precisamos então verificar se encontramos soluções dados cada S subconjunto em cavalo
  int n_jogadas = 0;
  int menor_jogada = 10;
  encontra_solucao(cavalo, pos_cavalo, peoes, n_peoes, n_jogadas, &menor_jogada);
  printf("\nIMPRIMINDO SUB CONJUNTOS GERADOS...\n");
  /*for(i=1;i<65;i++){
    printf("\nCAVALO[%d] | JOGADAS POSSIVEIS -> [",cavalo[i].pos);
    imprime(cavalo[i].posicao);
    printf("]");
  }*/
  //portanto, tendo então os daods que iremos trabalhar, iremos fazer as funcoes
  //que nos permitem realizar as verificações, dado o limite de ações da posicao do cavalo
  return 0;
}