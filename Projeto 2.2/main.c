#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main()
{
    printf("Organizacao e Arquitetura de Computadores\n");
    printf("Trabalho pratico parte 2 - Disassembly\n");
    printf("Analizar e Escrever algoritmo/fluxograma correspondente ao algoritmo central; Descobrir a senha.\n");
    printf("Formato do Executavel: PE (Windows)\n");
    printf("Informe a Senha: ");

    int i, j;
    char senha_correta[] = "vonneumann";

    char senha[MAX];
    char comp[MAX];
    int ascii[MAX];

    scanf("%s", &senha);
    for(i = 0; i < strlen(senha); i++) {
        ascii[i] = (senha[i] - 3) - 0;
        comp[i] = (char)ascii[i];
    }

    if (strcmp(senha_correta, comp) == 0) {
        printf("CERTA RESPOSTA!!!!! PARABENS!");
        return 0;
    }

    else
        printf("Resposta Errada! Tente novamente... ");
    return 0;
}

