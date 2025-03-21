#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "entrada.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Descarta caracteres até encontrar '\n' ou EOF
}

bool validarString(const char *str){

    // Percorre toda a string
    for( int i = 0; str[i] != '\0'; i++){

        unsigned char c = str[i];
        if (!isalpha(c) && c != ' ' && c != '-') {
            return false;
        }
    }
    return true;
}

void lerString(const char *msg, char *destino, int tamanho_max) {
    
    while (1) {
        printf("%s", msg);

        limparBuffer(); // Limpa qualquer caractere residual antes da leitura
        
        if (fgets(destino, tamanho_max, stdin) == NULL) {
            printf("Erro ao ler entrada!\n");
            continue; // Reinicia a leitura
        }

        // Verifica se o '\n' foi armazenado na string
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0'; // Remove o '\n'
        } else {
            // Se não houver '\n', significa que o buffer ainda tem caracteres pendentes
            limparBuffer();
        }

        if (validarString(destino)) break;
        printf("Entrada inválida! Use apenas letras, espaços e hífens.\n");
    }
}

int lerInteiro(const char *msg){
    int valor;
    printf("%s", msg);
    while ( scanf("%d", &valor) != 1 ){
        system("cls");
        printf("Entrada inválida! Tente novamente: ");
        limparBuffer();
    }
    return valor;
}

float lerFloat(const char *msg){
    float valor;
    printf("%s", msg);
    while( scanf("%f", &valor) != 1 ){ // scanf retorna o número de campos que foram designados e convertidos com sucesso
        system("cls");
        printf("Entrada inválida! Tente novamente: \n");
        limparBuffer();
    }
    return valor;
}
