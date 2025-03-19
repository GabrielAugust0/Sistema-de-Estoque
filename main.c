#include <stdio.h>
#include <stdlib.h>
#include "estoque.h"


int main(){

    Estoque estoque;
    inicializarEstoque(&estoque, 2); // Começa com capacidade 2

    Produto p1 = {1, "Arroz", 10.0, 5};
    Produto p2 = {2, "Feijão", 8.5, 3};
    Produto p3 = {3, "Óleo", 15.0, 2};

    adicionarProduto(&estoque, p1);
    adicionarProduto(&estoque, p2);
    adicionarProduto(&estoque, p3); // Aqui o vetor será expandido automaticamente

    int opcao = 0;

    while(1){
        Produto p;
        printf("====== MENU ======\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Sair\n");
        scanf("%d", &opcao);
        adicionarProduto(&estoque, p);
    }

    listarProdutos(&estoque);
    
    liberarEstoque(&estoque); // Libera memória
}