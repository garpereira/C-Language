#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    int *valor;
    int pos_ini;
    int tam;
}Primario;

typedef struct{
    int valor;
    int pos_indice;
    int pos_atual;
}Secundario;

void lendo(Primario *primario, int k_itera, int stop, int *novo_k){
    int N;
    int i;
    if(stop == k_itera)
        return;
    scanf("%d", &N);
    if(N == 0){
        primario[stop].valor = NULL;
        primario[stop].pos_ini = 0;
        primario[stop].tam = 0;
        *novo_k -= 1;
    }
    else{
        primario[stop].valor = (int*)malloc(sizeof(int)*N);
        primario[stop].pos_ini = 0;
        primario[stop].tam = N;
        for(i=0;i<N;i++)
            scanf("%d",&primario[stop].valor[i]);
    }
    return lendo(primario, k_itera, stop+1, novo_k);
}


void cria_sec(Secundario *secundario, Primario* primario, int novo_k, int k_itera){
    int i, j = 0;
    for(i=0;i<k_itera;i++){
        if(primario[i].valor == NULL);
        else{
            secundario[j].valor = primario[i].valor[0];
            secundario[j].pos_indice = i;
            j++;
        }
    }
    secundario[0].pos_atual = 0;
}


void imprime2(Secundario *secundario, int novo_k){
    int i;
    printf("\nIMPRIMINDO SECUNDARIO\n");
    for(i=secundario[0].pos_atual;i<novo_k;i++)
        printf("%d ", secundario[i].valor);
    printf("\n");
}

void merge(Secundario *secundario, int inicio, int meio, int fim){
  Secundario *temp;
  int p1, p2, tamanho, i, j, k;
  int fim1 = 0, fim2 = 0;
  tamanho = fim-inicio+1;
  p1 = inicio;
  p2 = meio+1;
  temp = (Secundario*)malloc(sizeof(Secundario)*tamanho);
  for(i=0; i<tamanho; i++){
    if(!fim1 && !fim2){
      if(secundario[p1].valor < secundario[p2].valor)
        temp[i] = secundario[p1++];
      else
        temp[i] = secundario[p2++];
      if(p1 > meio) fim1 = 1;
      if(p2 > fim) fim2 = 1;
    }
    else{
      if(!fim1)
        temp[i] = secundario[p1++];
      else
        temp[i] = secundario[p2++];
    }
  }
  for(j=0, k=inicio; j<tamanho; j++, k++)
    secundario[k] = temp[j];
  free(temp);
}
 
void mergeSort(Secundario *secundario, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio+fim)/2);
        mergeSort(secundario,inicio,meio);
        mergeSort(secundario,meio+1,fim);
        merge(secundario,inicio,meio,fim);
    }
}

void insertion(Secundario *secundario, int novo_k, int indice_atual){
    int i;
    Secundario *aux;
    //printf("\nANTES DO INSERTION\n");
    //imprime2(secundario,novo_k);
    aux = (Secundario*)malloc(sizeof(Secundario));
    for(i=indice_atual; i<novo_k-1; i++){
        if(secundario[i].valor > secundario[i+1].valor){
            *aux = secundario[i];
            secundario[i] = secundario[i+1];
            secundario[i+1] = *aux;
        }
        else
            break;
    }
    //printf("\nDEPOIS DO INSERTION\n");
    //imprime2(secundario, novo_k);
}


void iterando(Primario *primario, Secundario *secundario, int novo_k, int n_itera, int indice_atual, int stop){
    if(stop >= n_itera)
        return;
    int pos_original = secundario[indice_atual].pos_indice;//pegando o indice do qual este valor pertence
    primario[pos_original].pos_ini++;//atualizando a posição do vetor de valores a qual este valor em secundario pertence
    if(!(secundario[indice_atual].valor = primario[pos_original].valor[primario[pos_original].pos_ini]))//pegando o valor que esta na posicao inicial atual no vetor de valores desta posicao original
        indice_atual++;//retorna a funcao iterando com stop+1
    else{//se der certo a troca de valor
        //executamos o insertion
        insertion(secundario, novo_k, indice_atual);
    }
    secundario[0].pos_atual = indice_atual;//armazenando o menor indice valido no vetor secundario de valores
    return iterando(primario, secundario, novo_k, n_itera, indice_atual, stop+1);
}

unsigned long long soma(Secundario *secundario, int novo_k){
    int i;
    unsigned long long somador = 0;
    //printf("\nPOS ATUAL -> %d\n", secundario[0].pos_atual);
    for(i=secundario[0].pos_atual;i<novo_k;i++)
        somador += secundario[i].valor;
    return somador;
}

int main(){
    Primario *primario;
    Secundario *secundario;
    int k_itera, n_itera;
    int novo_k;
    unsigned long long resultado;
    scanf("%d %d", &k_itera, &n_itera);
    novo_k = k_itera;

    primario = (Primario*)malloc(sizeof(Primario)*k_itera);
    lendo(primario, k_itera, 0, &novo_k);

    secundario = (Secundario*)malloc(sizeof(Secundario)*novo_k);
    cria_sec(secundario, primario, novo_k, k_itera);
    mergeSort(secundario, 0, novo_k-1);
    iterando(primario, secundario, novo_k, n_itera, 0, 1);
    //printf("\nDEPOIS DE ITERAR\n");
    //imprime2(secundario, novo_k);
    resultado = soma(secundario, novo_k);
    //imprime2(secundario, novo_k);
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