#include <stdio.h>
#include <stdlib.h>

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


int main(){

    Estoque estoque;
    inicializarEstoque(&estoque, 2); // Começa com capacidade 2

    Produto p1 = {1, "Arroz", 10.0, 5};
    Produto p2 = {2, "Feijão", 8.5, 3};
    Produto p3 = {3, "Óleo", 15.0, 2};

    adicionarProduto(&estoque, p1);
    adicionarProduto(&estoque, p2);
    adicionarProduto(&estoque, p3); // Aqui o vetor será expandido automaticamente

    listarProdutos(&estoque);
    
    liberarEstoque(&estoque); // Libera memória
}

void inicializarEstoque(Estoque *estoque, int capacidade){
    estoque->produtos = (Produto *) malloc(capacidade * sizeof(Produto));
    estoque->total = 0;
    estoque->capacidade = capacidade;
}

void adicionarProduto(Estoque *estoque, Produto produto){

    // Realocar a memória para adicionar o novo produto, se necessário...
    if(estoque->total >= estoque->capacidade){
        estoque->produtos = (Produto *) realloc(estoque->produtos, 2 * estoque->capacidade * sizeof(Produto));
        estoque->capacidade *= 2; // Dobra a capacidade
    }

    // Após a memória ser realocada, adicionar o novo produto
    estoque->produtos[estoque->total] = produto;
    estoque->total++;
    printf("Produto %s adicionado com sucesso!\n", produto.nome);
}

void listarProdutos(Estoque *estoque){
    for(int i = 0; i < estoque->total; i++){
        printf("Codigo: %d | Produto: %s | Preco: %.2f | Em estoque: %d\n", 
                estoque->produtos[i].codigo, 
                estoque->produtos[i].nome,
                estoque->produtos[i].preco,
                estoque->produtos[i].quantidade);
    }
}

void liberarEstoque(Estoque *estoque){
    free(estoque->produtos);
    estoque->total = 0;
    estoque->capacidade = 0;
}

