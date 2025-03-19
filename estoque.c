#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estoque.h"


void inicializarEstoque(Estoque *estoque, int capacidade){
    estoque->produtos = (Produto *) malloc(capacidade * sizeof(Produto));
    estoque->total = 0;
    estoque->capacidade = capacidade;
}

bool verificarProduto(Estoque *estoque, Produto *produto){
    
    for(int i = 0; i < estoque->total; i++){
        if(estoque->produtos[i].codigo == produto->codigo){
            return true;
        }
        else if(estoque->produtos[i].nome == produto->nome){
            return true;
        }
        else if(estoque->produtos[i].preco == produto->preco){
            return true;
        }
        else if(estoque->produtos[i].quantidade == produto->quantidade){
            return true;
        }

    }
    return false;
}

void construirProduto(Estoque *estoque, Produto *produto){
    system("cls");
    printf("Digite qual o codigo do produto: ");
    scanf("%d", &produto->codigo);
    printf("Digite o nome do produto: ");
    scanf("%s", produto->nome);
    printf("Digite o preco do produto: ");
    scanf("%.2f", &produto->preco);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &produto->quantidade);
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

