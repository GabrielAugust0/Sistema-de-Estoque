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
        system("cls");
        printf("====== MENU ======\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                construirProduto(&estoque, &p);      // Permite que o usuário digite as informações relacionadas ao produto que será adicionado

                if(verificarProduto(&estoque, &p)){  // Verifica se o produto já está cadastrado. Se sim, exibe uma mensagem de erro
                    system("cls");
                    printf("====== ERRO ======\n");
                    printf("Produto já existe no estoque!\n");
                    printf("===================\n");
                    system("pause");
                    break;
                }

                adicionarProduto(&estoque, p);       // Adiciona o produto ao estoque caso ele não exista
                break;
            case 2:
                listarProdutos(&estoque);
                break;
            case 3:
                exit(0);
        }
    }
    
    liberarEstoque(&estoque); // Libera memória
}