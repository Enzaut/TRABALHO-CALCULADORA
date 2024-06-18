#include <stdio.h>
#include "calculadora.h"

int main() {
    char posFixa1[] = "10 log 3 ^ 2 +";
    char posFixa2[] = "7 2 * 4 +";
    char posFixa3[] = "9 5 2 8 * 4 + * +";

    // Convertendo para a forma infixa e calculando o valor
    char *inFixa1 = getFormaInFixa(posFixa1);
    float valor1 = getValor(posFixa1);

    char *inFixa2 = getFormaInFixa(posFixa2);
    float valor2 = getValor(posFixa2);

    char *inFixa3 = getFormaInFixa(posFixa3);
    float valor3 = getValor(posFixa3);


    printf("Expressão Infixa 1: %s\n", inFixa1);
    printf("Valor da Expressão 1: %.2f\n\n", valor1);

    printf("Expressão Infixa 2: %s\n", inFixa2);
    printf("Valor da Expressão 2: %.2f\n\n", valor2);

    printf("Expressão Infixa 3: %s\n", inFixa3);
    printf("Valor da Expressão 3: %.2f\n\n", valor3);


    // Liberar a memória alocada para as strings infixas
    free(inFixa1);
    free(inFixa2);
    free(inFixa3);

    return 0;
}
