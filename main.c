#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "estoque.h"
#include "entrada.h"


int main(){

    Estoque estoque;
    inicializarEstoque(&estoque, 2, "estoque.txt"); // Começa com capacidade 2

    int opcao = 0;

    while(1){
        
        Produto p;
        system("cls");
        opcao = lerInteiro("====== MENU ======\n1 - Adicionar produto\n2 - Listar produtos\n3 - Remover o produto \n4 - Sair\n");

        switch(opcao){
            case 1:
                construirProduto(&p);      // Permite que o usuário digite as informações relacionadas ao produto que será adicionado

                if(verificarProduto(&estoque, &p) == 0){  // Verifica se o produto já está cadastrado. Se sim, exibe uma mensagem de erro
                    system("cls");
                    printf("====== ERRO ======\n");
                    printf("Produto já existe no estoque !\n");
                    printf("===================\n");
                    system("pause");
                    break;
                }

                if(verificarProduto(&estoque, &p) == 1){  // Verifica se as informações são válidas. Se sim, exibe uma mensagem de erro
                    system("cls");
                    printf("====== ERRO ======\n");
                    printf("Informações inválidas !\n");
                    printf("===================\n");
                    system("pause");
                    break;
                }

                adicionarProduto(&estoque, p);       // Adiciona o produto ao estoque caso ele não exista
                break;
            case 2:
                listarProdutos(&estoque);
                system("pause");
                break;
            case 3:
                removerProduto(&estoque);
                break;
            case 4:
                salvarEstoque(&estoque);    // Salva o estoque no arquivo
                liberarEstoque(&estoque);   // Libera memória
                exit(0);
        }
    }
}