#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIM 8

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

//posso utilizar esta função como backtracing
Scavalo* preenche_cavalo(Scavalo *cavalo, int tabuleiro[DIM][DIM]){
    int k;
    for(k=0;k<64;k++){
        int i, j;
        i = cavalo[k].i;
        j = cavalo[k].j;
        Scavalo *aux;
        aux = cavalo[k].posicao;
        //printf("\ni -> %d | j -> %d",i,j);
        //pos[i+2][j-1] (+15)
        if(i+2 <= 7 && j-1 >= 0){
            if(tabuleiro[i+2][j-1] == cavalo[k].pos+15){
                //printf("\nentrou1, pos -> %d", cavalo[k].pos);
                cavalo[k].posicao = inicia(aux, cavalo[k].pos+15);
            }
        }
        
        aux = cavalo[k].posicao;
        if(i-1 >= 0 && j-2 >= 0){
            if(tabuleiro[i-1][j-2] == cavalo[k].pos-10){
                //printf("\nentrou2, pos -> %d", cavalo[k].pos);
                cavalo[k].posicao = inicia(aux, cavalo[k].pos-10);
            }
        }
        
        aux = cavalo[k].posicao;
        if(i-2 >= 0 && j-1 >= 0){
            if(tabuleiro[i-2][j-1] == cavalo[k].pos-17){
                //printf("\nentrou3, pos -> %d", cavalo[k].pos);
                cavalo[k].posicao = inicia(aux, cavalo[k].pos-17);
            }
        }
        
        aux = cavalo[k].posicao;
        if(i-2 >= 0 && j+1 <=7){
            if(tabuleiro[i-2][j+1] == cavalo[k].pos-15){
                //printf("\nentrou4, pos -> %d", cavalo[k].pos);
                cavalo[k].posicao = inicia(aux, cavalo[k].pos-15);
            }
        }
        
        aux = cavalo[k].posicao;
        if(i+1 <= 7 && j+2 <= 7){
            if(tabuleiro[i+1][j+2] == cavalo[k].pos+10){
                //printf("\nentrou5, pos -> %d", cavalo[k].pos);
                cavalo[k].posicao = inicia(aux, cavalo[k].pos+10);
            }
        }
        
        aux = cavalo[k].posicao;
        if(i+1 <= 7 && j-2 >= 0){
            if(tabuleiro[i+1][j-2] == cavalo[k].pos+6){
                //printf("\nentrou6, pos -> %d", cavalo[k].pos);
                cavalo[k].posicao = inicia(aux, cavalo[k].pos+6);
            }
        }
        
        aux = cavalo[k].posicao;
        if(i-1 >=0 && j+2 <=7){
            if(tabuleiro[i-1][j+2] == cavalo[k].pos-6){
                //printf("\nentrou7, pos -> %d", cavalo[k].pos);
                cavalo[k].posicao = inicia(aux, cavalo[k].pos-6);
            }
        }
        
        aux = cavalo[k].posicao;
        if(i+2 <= 7 && j+1 <= 7){
            if(tabuleiro[i+2][j+1] == cavalo[k].pos+17){
            //printf("\nentrou8, pos -> %d", cavalo[k].pos);
            cavalo[k].posicao = inicia(aux, cavalo[k].pos+17);
            }
        }
    }
    return cavalo;
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

void atualiza_peoes(int *pos_peoes, int peoes){
  int i;
  for(i=0;i<peoes;i++){
    if(pos_peoes[i] > 0)
      pos_peoes[i]+=8;
  }
}

void caca_peoes(Scavalo *cavalo, int pos_cavalo, int *pos_peoes){
  
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
  printf("\nPreenchendo o Tabuleiro...\n");
  preenche_tab(tabuleiro, cavalo);

  int peoes;
  int *pos_peoes;
  printf("\nDigite a quantidade de Peoes: ");
  scanf("%d",&peoes);
  pos_peoes = (int*)malloc(sizeof(int)*peoes);
  int i;
  printf("\nAgora digite suas posicoes\n");
  for(i=0;i<peoes;i++){
    printf("\nPeao[%d] -> ",i+1);
    scanf("%d",&pos_peoes[i]);
  }

  int pos_cavalo;
  printf("\nDigite a posicao do Cavalo: ");
  scanf("%d",&pos_cavalo);

  printf("\nPreenchendo o cavalo...");
  cavalo = preenche_cavalo(cavalo, tabuleiro);
  printf("\nTerminou de preencher.\n");

  //printf("\nTeste de print\ncavalo[0]->posicao->pos -> %d",cavalo[0].posicao->pos);
  //printf("\nTeste de print\ncavalo[0]->posicao->posicao->pos -> %d",cavalo[0].posicao->posicao->pos);

  for(i=0;i<64;i++){
    printf("\nCAVALO[%d] | JOGADAS POSSIVEIS -> [",cavalo[i].pos);
    imprime(cavalo[i].posicao);
    printf("]");
  }
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