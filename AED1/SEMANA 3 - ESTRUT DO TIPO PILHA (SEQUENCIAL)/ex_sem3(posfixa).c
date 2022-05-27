#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Gabriel Almeida Rodrigues Pereira | RA: 143229 | Turma: Regina Celia Coelho
typedef struct Posfix {
  int top;
  int size;
  char *expr;
} Pos;

Pos* alocarPilha(int n) {
  Pos *p = (Pos *) malloc (n * sizeof(Pos));

  p->top = -1;
  p->size = n;
  p->expr = (char *) malloc (n * sizeof(char));

  return p;
}

int prioridadeOp(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    case '^':
      return 3;
    default:
      return -1;
  }
}

int InfixaPosfixa(char *expr, int size) {

  int i, lenght = size;
  for (i = 0; i < size; i++) {
    if (expr[i] == '(' || expr[i] == ')') lenght--;
  }

  Pos *pilha = alocarPilha(size);
  char expr_f[lenght]; // Expressão final sem os parenteses
  int j = -1; // inicializador da posição para a expressão final

  for (i = 0; i < size; i++) {
    if((expr[i] >= '0' && expr[i] <= '9'){
      j++;
      expr_f[j] = expr[i];
    } else if (expr[i] ==  '(') {
      pilha->top++;
      pilha->expr[pilha->top] = '(';
    } else if (expr[i] ==  ')') {
      while (pilha->top > -1 && pilha->expr[pilha->top] != '(') {
        j++;
        expr_f[j] = pilha->expr[pilha->top];
        pilha->top--;
      }
      if (pilha->top > -1 && pilha->expr[pilha->top] != '(')
        return -1; // PROBLEMA AQUI
      else pilha->top--; // Se encontrar o (, tira ele da pilha
    } else {
      while (pilha->top > -1 && prioridadeOp(expr[i]) <= prioridadeOp(pilha->expr[pilha->top])) {
        j++;
        expr_f[j] = pilha->expr[pilha->top];
        pilha->top--;
      }
      pilha->top++;
      pilha->expr[pilha->top] = expr[i];
    }
  }
  // (A+B*(C-D)) <- teste
  printf("%s", expr_f);

  return 0;
}

int main(void) {
  char expr[50];

  scanf("%s", expr);
  int length = strlen(expr);

  InfixaPosfixa(expr, length);

  return 0;
}
