#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <stdbool.h>


typedef struct Produto{
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
}Produto;

typedef struct Estoque{
    Produto *produtos;    // Vetor dinâmico de produtos
    int total;            // Número atual de produtos no estoque
    int capacidade;        // Capacidade máxima
}Estoque;

void inicializarEstoque(Estoque *estoque, int capacidade, const char *arquivo);
void adicionarProduto(Estoque *estoque, Produto produto);
// void removerProduto(Estoque *estoque, int codigo, int *quantidade);
void liberarEstoque(Estoque *estoque);
void listarProdutos(Estoque *estoque);
void construirProduto(Produto *produto);
int verificarProduto(Estoque *estoque, Produto *produto);
void salvarEstoque(Estoque *estoque);

#endif