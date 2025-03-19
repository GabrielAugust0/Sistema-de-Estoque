#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estoque.h"


int quantidadeProdutos(const char *arquivo){
    
    FILE *file = fopen(arquivo, "r");

    // Verificar se há estoque salvo
    if( file == NULL ){
        printf("Arquivo não encontrado. Criando novo estoque !\n");
        return 1;
    }

    int quantidade;
    char buffer[256];

    // Contar a quantidade de itens no arquivo
    while( fgets(buffer, sizeof(buffer), file) != NULL ){
        quantidade++;
    }

    fclose(file);

    return quantidade;
}

void inicializarEstoque(Estoque *estoque, int capacidade, const char *arquivo){

    // Lê quantos produtos existem no estoque e define a capacidade do vetor dinâmico como o dobro
    capacidade = quantidadeProdutos("estoque.txt")*2;

    estoque->produtos = (Produto *) malloc(capacidade * sizeof(Produto));
    estoque->total = 0;
    estoque->capacidade = capacidade;

    FILE *file = fopen(arquivo, "r");

    if( file == NULL ){
        printf("Arquivo não encontrado. Criando novo estoque!\n");
        return;
    }

    while( fscanf(file, "%d;%49[^;];%f;%d\n",
                  &estoque->produtos[estoque->total].codigo,
                  estoque->produtos[estoque->total].nome,
                  &estoque->produtos[estoque->total].preco,
                  &estoque->produtos[estoque->total].quantidade) != EOF ){

        estoque->total++;
    }

    fclose(file);
    printf("Estoque carregado com sucesso! %d produtos \n", estoque->total);
}

bool verificarProduto(Estoque *estoque, Produto *produto){
    
    for(int i = 0; i < estoque->total; i++){
        if(estoque->produtos[i].codigo == produto->codigo || produto->codigo < 0){
            return true;
        }
        else if( strcmp(estoque->produtos[i].nome, produto->nome) == 0){
            return true;
        }
        else if(produto->preco < 0){
            return true;
        }
        else if(produto->quantidade < 0){
            return true;
        }
    }
    return false;
}

void salvarEstoque(Estoque *estoque){

    FILE *arquivo = fopen("estoque.txt", "w"); // Abre o arquivo para escrita

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    for( int i = 0; i < estoque->total; i++){
        fprintf(arquivo,"%d;%s;%.2f;%d\n", 
                estoque->produtos[i].codigo, 
                estoque->produtos[i].nome, 
                estoque->produtos[i].preco, 
                estoque->produtos[i].quantidade);
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Estoque salvo com sucesso!\n");
}

void construirProduto(Produto *produto){
    system("cls");
    printf("Digite qual o codigo do produto: ");
    scanf("%d", &produto->codigo);
    printf("Digite o nome do produto: ");
    getchar(); // Limpar o buffer do teclado
    fgets(produto->nome, sizeof(produto->nome), stdin);
    printf("Digite o preco do produto: ");
    scanf("%f", &produto->preco);
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
        printf("Codigo: %d | Produto: %s | Preco: R$ %.2f | Em estoque: %d\n", 
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

