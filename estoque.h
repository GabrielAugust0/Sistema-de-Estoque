#ifndef ESTOQUE_H
#define ESTOQUE_H

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

void inicializarEstoque(Estoque *estoque, int capacidade);
void adicionarProduto(Estoque *estoque, Produto produto);
// void removerProduto(Estoque *estoque, int codigo, int *quantidade);
void liberarEstoque(Estoque *estoque);
void listarProdutos(Estoque *estoque);

#endif