#include <stdio.h>

int teto(double numero){
  int numeroint = numero;
  if(numero - numeroint > 0.0)
    return numeroint+1;
  return numero;
}

int main(){
  int vet[30];
  int i;
  int n_inicial, m_final;
  int dia_atual = 0;
  int total_dias = 0;
  int soma_vetor = 0;
  int media;

  scanf("%d %d", &n_inicial, &m_final);

  for(i=0;i<30;i++){
    scanf("%d",&vet[i]);
    soma_vetor += vet[i];
  }


 media = teto(soma_vetor/30.0);//calculo a media(teto)
 while(n_inicial < m_final){   
   if(dia_atual == 30)
     dia_atual = 0;
   n_inicial += media;//somo ao n_inicial
   soma_vetor += media-vet[dia_atual]; //calculo a diferença
   vet[dia_atual] = media;//substituo o valor antigo do vetor
   media = teto(soma_vetor/30.0);//gero a nova media(teto)
   
   total_dias++;
   dia_atual++;
 }
 printf("%d",total_dias);
  return 0;
}

/*150 10000
20 23 24 18 13 25 10 21 35 9 12 15 13 25 22 23 15 20 10 11 12 15 19 21 18 15 
22 29 14 31
soma 560*/

