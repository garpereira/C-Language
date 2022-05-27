
#include <stdio.h>
#include <stdlib.h>





/* A lógica , é parecida com a LCS, só que ao inves voce adicionar quantas vezes uma ocorrencia aparece na outra, voce adiciona qual a sua MAIOR TAXA disponivel para aquele PESO, considerando que vc ja checou que a transacao atual possu.i um tamanho menor que a parte do bloco que vc esta vendo

 sabe aquele treco da mochila que vc verifica quais espaços vao ser utilizados ou nao usados?

  vc verifica com a soma do indice atual + o valor anterior no menor peso(pro que usa)

e pro que nao usa é o valor da linha anterior M[i-1][j]

 ai o que vc adiciona matriz, é o maio valor dessas 2 verificações

 porque ai vc vai sempre adicionar a maior taxa com o menor peso*/





typedef struct

{

    int valor;

    int tamMax;



} CHAVE;



//Função para verificar se a transação atual possui um tamanho de bytes maior que a parte do bloco analisada

void  Mempool( CHAVE *V, int size, int C)
{

    int blockchain[size+1][C+1];

    int i=0, j=0;



    for(i=1; i<= size; i++)
    {

        for (j =0; j<= C; j++)
        {

            if(V[i-1].tamMax > j)  //verifica se o tamanho da transação atual ultrapassa o limite
            {

                blockchain[i][j] = blockchain[i-1][j];

            }

        }

    }

}

//Função para achar a maior taxa disponível

int max_taxa(int taxa1, int taxa2)

{

    if(taxa1 > taxa2)
    {
        return taxa1;



    }
    else
    {

        return taxa2;

    }

}

//C = CAPACIDADE N NUM TRANSAÇOES

int Calcula(CHAVE *vet,int C, int N)
{



    int i, b;

    int M[N+1][C+1];

    int aux1=0,aux2=0; // auxiliares para guardar a maior taxa



    // construindo a tabela  M[][] utilizando bottom up

    for (i = 1; i <= N; i++)
    {

        for (b = 0; b <= C; b++)
        {

            if (i==0 || b==0)

                M[i][b] = 0;

            else if(vet[i-1].tamMax > b)  // faz a verificação

                Mempool( vet, N,  C);

            else // senão guardaremos as maiores taxas realizando as seguintes operações

            {

                aux1 =vet[i-1].valor +M[i-1][b- vet[i-1].tamMax];

                aux2 = M[i-1][b];

                // chamando a função max para achar as maiores taxas, temos :

                M[i][b] = max_taxa(aux1, aux2);

            }

        }

    }

    return M[N][C];

}



int main(void)
{



    int N, C;

    int i, j;

    int sol;



//printf("Digite o número de transações existentes no mempool N");

    scanf("%d", &N);



//printf("Digite a capacidade em bytes de um bloco,C");

    scanf("%d", &C);



    CHAVE *vetor;

    vetor = (CHAVE*) malloc(sizeof(CHAVE)*N);



    for (i = 0; i < N; i++)
    {

        //printf("\nDigite o valor da taxa e o tamanho em bytes:");

        scanf("%d %d",&vetor[i].valor, &vetor[i].tamMax);

    }



// A soma a  das taxas em CBL a serem obtidas caso o bloco seja inserido no blockchain é :

    sol = Calcula(vetor,C, N);

    printf ("%d", sol);



    return 0;



}
