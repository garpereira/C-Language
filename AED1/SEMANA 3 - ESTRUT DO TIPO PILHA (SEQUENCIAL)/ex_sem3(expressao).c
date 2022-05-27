#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct{
    char expressao[20];
    int topo;
    float numeros[MAX];
    int tamanho;
    char numerostr[MAX];
    int topostr;
    char guardasinal;
}Pilha;

void inicia_pilha(Pilha *ponteiro){
    ponteiro->topo = -1;
    ponteiro->topostr = -1;
    ponteiro = (Pilha*)malloc(ponteiro->tamanho*sizeof(Pilha));
}

int pilha_cheia(Pilha *ponteiro){
    if(ponteiro->topo == ponteiro->tamanho){
        printf("lista cheia\n");
        return 1;
    }
    else{
        return 0;
    }
}

int pilha_vazia(Pilha *ponteiro){
    if(pilha_cheia(ponteiro) == 0){
       printf("pilha vazia\n");
       return 0;
    }
    else{
        return 1;
    }
}


void ler_numeros(Pilha *ponteiro){
    float aux;
    int i;
    int avisarodou = 0;//variavel indica que ja foi lido outro sinal
    for(i=0;i<ponteiro->tamanho;i++){
        if(ponteiro->expressao[i] == '0' || ponteiro->expressao[i] == '1' || ponteiro->expressao[i] == '2' || ponteiro->expressao[i] == '3' || ponteiro->expressao[i] == '4' || ponteiro->expressao[i] == '5' || ponteiro->expressao[i] == '6' || ponteiro->expressao[i] == '7' || ponteiro->expressao[i] == '8' ||  ponteiro->expressao[i] == '9'){
            ponteiro->topostr++;//aumento a pilha de string
            ponteiro->numerostr[ponteiro->topostr] = ponteiro->expressao[i];//recebo o numero de 0 a 9 na string numerostr, na posicao topostr
        }
        else if(ponteiro->expressao[i] == '+' || ponteiro->expressao[i] == '-' || ponteiro->expressao[i] == '*' || ponteiro->expressao[i] == '/' || ponteiro->expressao[i] == '^'){//senao for um numero
            if(avisarodou > 0){//caso ja tenha rodado o for, ele entra aqui, analisando o sinal obtido anteriormente
                aux = atof(ponteiro->numerostr);//aux recebe o numero atual em numerostr
                switch(ponteiro->guardasinal){
                    case '+':
                        ponteiro->numeros[ponteiro->topo] += aux;
                        break;
                    case '-':
                        ponteiro->numeros[ponteiro->topo] -= aux;
                        break;
                    case '*':
                        ponteiro->numeros[ponteiro->topo] *= aux;
                        break;
                    case '/':
                        ponteiro->numeros[ponteiro->topo] /= aux;
                        break;
                    case '^':
                        ponteiro->numeros[ponteiro->topo] = pow(ponteiro->numeros[ponteiro->topo], aux);
                        break;
                }
                ponteiro->guardasinal = ponteiro->expressao[i];
                ponteiro->topostr = -1;
                break;
            }
            else{
                ponteiro->topo++;//aumento minha pilha de numeros float
                ponteiro->numeros[ponteiro->topo] = atof(ponteiro->numerostr);//insiro na posicao topo da pilha numeros float, o numero que tenho armazenado no vetor numerostr
                ponteiro->guardasinal = ponteiro->expressao[i];//armazeno o sinal obtido para realizar a operacao na proxima leitura
                ponteiro->topostr = -1;//zero o topostr para obter um novo numero na proxima leitura
                avisarodou++;
                break;
            }
        }
        else if(ponteiro->expressao[i] == '\0'){
            aux = atof(ponteiro->numerostr);//aux recebe o numero atual em numerostr
            switch(ponteiro->guardasinal){
                case '+':
                    ponteiro->numeros[ponteiro->topo] += aux;
                    break;
                case '-':
                    ponteiro->numeros[ponteiro->topo] -= aux;
                    break;
                case '*':
                    ponteiro->numeros[ponteiro->topo] *= aux;
                    break;
                case '/':
                    ponteiro->numeros[ponteiro->topo] /= aux;
                    break;
                case '^':
                    ponteiro->numeros[ponteiro->topo] = pow(ponteiro->numeros[ponteiro->topo], aux);
                    break;
            }
        }
    }
}

int main(){
    Pilha *ponteiro;
    ponteiro = (Pilha*)malloc(sizeof(Pilha));
    scanf("%s",ponteiro->expressao);
    inicia_pilha(ponteiro);
    ponteiro->tamanho = strlen(ponteiro->expressao);
    ler_numeros(ponteiro);
    printf("%.2f", ponteiro->numeros);
return 0;
}
