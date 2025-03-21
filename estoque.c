#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"


int quantidadeProdutos(const char *arquivo){
    
    FILE *file = fopen(arquivo, "r");

    // Verificar se há estoque salvo
    if( file == NULL ){
        printf("Arquivo não encontrado. Criando novo estoque !\n");
        return 1;
    }

    // Caso exista estoque ...

    int quantidade = 0;
    char buffer[256];

    // Contar a quantidade de itens no arquivo
    while( fgets(buffer, sizeof(buffer), file) != NULL ){
        quantidade++;
    }

    fclose(file); // Garante que toda a informação que está no buffer será gravada na memória

    return quantidade;
}

void inicializarEstoque(Estoque *estoque, int capacidade, const char *arquivo){

    // Lê quantos produtos existem no estoque e define a capacidade do vetor dinâmico como o dobro
    capacidade = quantidadeProdutos("estoque.txt")*2;

    // Cria o estoque zerado
    estoque->produtos = (Produto *) malloc(capacidade * sizeof(Produto));
    estoque->total = 0;
    estoque->capacidade = capacidade;

    FILE *file = fopen(arquivo, "r");

    // Se não houver arquivo txt, retorna o estoque zerado
    if( file == NULL ){
        printf("Arquivo não encontrado. Criando novo estoque!\n");
        return;
    }

    // Caso tenha arquivo TXT, preenche o estoque 
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

int verificarProduto(Estoque *estoque, Produto *produto){
    
    // Retornos:
    // -1: Produto válido e não existe no estoque
    //  0: Produto já existe (código ou nome duplicado)
    //  1: Dados inválidos (preço, quantidade ou código negativo)

    for(int i = 0; i < estoque->total; i++){
        if(estoque->produtos[i].codigo == produto->codigo){
            return 0;
        }
        else if( strcmp(estoque->produtos[i].nome, produto->nome) == 0){
            return 0;
        }
        else if(produto->preco < 0){
            return 1;
        }
        else if(produto->quantidade < 0){
            return 1;
        }
        else if(produto->codigo < 0){
            return 1;
        }
    }
    return -1;
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
    produto->nome[strcspn(produto->nome, "\n")] = '\0';  // Remove o \n do final da string

    printf("Digite o preco do produto: ");
    scanf("%f", &produto->preco);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &produto->quantidade);
}

void adicionarProduto(Estoque *estoque, Produto produto){

    // Realocar a memória para adicionar o novo produto, se necessário...
    if(estoque->total >= estoque->capacidade){

        Produto *temp = (Produto *)realloc(estoque->produtos, 2 * estoque->capacidade * sizeof(Produto));
        // Confere se a alocação foi realizada com sucesso...
        if( temp == NULL){
            printf("Erro ao realocar memória!\n");
            return;
        }

        estoque->produtos = temp;
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

void removerProduto(Estoque *estoque){

    int codigo = 0;
    int qtd = 0;

    system("cls");
    printf("Digite o codigo do produto \n");
    scanf("%d", &codigo);
    system("cls");
    printf("Digite a quantidade que deseja remover \n");
    scanf("%d", &qtd);

    if( codigo <= 0 || qtd <= 0 ){
        system("cls");
        printf("Informacao invalida!\n");
        system("pause");
        return;
    }

    for(int i = 0; i < estoque->total; i++){

        if( estoque->produtos[i].codigo == codigo ){
            
            // Caso não tenha nenhum produto em estoque...
            if(estoque->produtos[i].quantidade <= 0  ){
                printf("Nao tem mais %s no estoque! \n", estoque->produtos[i].nome);
                system("pause");
                return;
            } 
            // Caso tenha menos do que a quantidade especificada...
            if(estoque->produtos[i].quantidade < qtd ){
                printf("So tem %d %s no estoque. Dessa forma, nao foi possivel remover.\n",
                        estoque->produtos[i].quantidade,
                        estoque->produtos[i].nome);
                system("pause");
                return;
            }
            

            estoque->produtos[i].quantidade -= qtd;
            
            printf("Foram removidos %d %s \n",
                   qtd,
                   estoque->produtos[i].nome);
            system("pause");
            return;
        }
    }

    system("cls");
    printf("O codigo %d nao eh correspondente a nenhum produto do estoque. \n", codigo);
    system("pause");
}

void liberarEstoque(Estoque *estoque){
    free(estoque->produtos);
    estoque->total = 0;
    estoque->capacidade = 0;
}

