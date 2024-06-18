#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Função auxiliar para verificar se um caractere é um operador
int ehOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Função auxiliar para verificar se uma string é uma função matemática
int ehFuncaoMatematica(char *token) {
    return (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 || strcmp(token, "log") == 0);
}

// Função auxiliar para verificar se um token é um operando (número ou função)
int ehOperando(char *token) {
    return (isdigit(token[0]) || token[0] == '.' || ehFuncaoMatematica(token));
}

// Função para calcular o resultado de uma expressão pós-fixa
float calcularPosFixa(char *expressao) {
    float pilha[512];  // Pilha para armazenar os operandos
    int topo = -1;     // Topo da pilha

    char expressaoCopia[512];
    strcpy(expressaoCopia, expressao);

    char *token = strtok(expressaoCopia, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || token[0] == '.') {
            // Se for um operando (número), empilha na pilha
            topo++;
            pilha[topo] = atof(token);
        } else if (ehOperador(token[0])) {
            // Se for um operador, desempilha os operandos, aplica o operador e empilha o resultado
            float op2 = pilha[topo--];
            float op1 = pilha[topo--];

            switch (token[0]) {
                case '+':
                    pilha[++topo] = op1 + op2;
                    break;
                case '-':
                    pilha[++topo] = op1 - op2;
                    break;
                case '*':
                    pilha[++topo] = op1 * op2;
                    break;
                case '/':
                    pilha[++topo] = op1 / op2;
                    break;
                case '^':
                    pilha[++topo] = pow(op1, op2);
                    break;
                default:
                    break;
            }
        } else if (ehFuncaoMatematica(token)) {
            // Se for uma função matemática, desempilha o operando, aplica a função e empilha o resultado
            float op = pilha[topo--];

            if (strcmp(token, "raiz") == 0) {
                pilha[++topo] = sqrt(op);
            } else if (strcmp(token, "sen") == 0) {
                pilha[++topo] = sin(op);
            } else if (strcmp(token, "cos") == 0) {
                pilha[++topo] = cos(op);
            } else if (strcmp(token, "tg") == 0) {
                pilha[++topo] = tan(op);
            } else if (strcmp(token, "log") == 0) {
                pilha[++topo] = log10(op);
            }
        }

        token = strtok(NULL, " ");
    }

    // O resultado final estará no topo da pilha
    return pilha[topo];
}

// Função auxiliar para converter um operador em uma string
void operadorParaString(char operador, char *str) {
    str[0] = ' ';
    str[1] = operador;
    str[2] = ' ';
    str[3] = '\0';
}

// Função para converter a expressão pós-fixa para infixada
char *getFormaInFixa(char *Str) {
    static char pilha[10][512];  // Pilha para armazenar sub-expressões
    int topo = -1;  // Topo da pilha

    char expressaoCopia[512];
    strcpy(expressaoCopia, Str);

    char *token = strtok(expressaoCopia, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || token[0] == '.') {
            // Se for um operando, empilha na pilha
            topo++;
            strcpy(pilha[topo], token);
        } else if (ehOperador(token[0])) {
            // Se for um operador, desempilha os operandos, cria uma sub-expressão e empilha de volta
            char op2[512];
            strcpy(op2, pilha[topo--]);
            char op1[512];
            strcpy(op1, pilha[topo--]);

            char subExpr[512];
            sprintf(subExpr, "(%s %c %s)", op1, token[0], op2);

            topo++;
            strcpy(pilha[topo], subExpr);
        } else if (ehFuncaoMatematica(token)) {
            // Se for uma função matemática, desempilha o operando, cria uma sub-expressão e empilha de volta
            char op[512];
            strcpy(op, pilha[topo--]);

            char subExpr[512];
            sprintf(subExpr, "%s(%s)", token, op);

            topo++;
            strcpy(pilha[topo], subExpr);
        }

        token = strtok(NULL, " ");
    }

    // A expressão infixada completa estará no topo da pilha
    char *resultado = malloc(strlen(pilha[topo]) + 1);
    strcpy(resultado, pilha[topo]);
    return resultado;
}

// Função para calcular o valor de uma expressão pós-fixa
float getValor(char *Str) {
    return calcularPosFixa(Str);
}
