#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h>
#include "BancoDeDados.h"

// MENU PRINCIPAL DO PROGRAMA
void Menu_Principal()
{
    printf("--------------------------------------------------------\n");
    printf(" GERENCIAMENTO DE VENDAS/PRODUTOS -> LOJAS INFORMATICA  \n");
    printf("--------------------------------------------------------\n");
    printf("            [01] - CADASTRAR PRODUTOS                   \n");
    printf("            [02] - CADASTRAR CLIENTES                   \n");
    printf("            [03] - CADASTRAR VENDAS                     \n");
    printf("            [04] - MOSTRAR PRODUTOS CADASTRADOS         \n");
    printf("            [05] - MOSTRAR CLIENTES CADASTRADOS         \n");
    printf("            [06] - MOSTRAR VENDAS CADASTRADAS           \n");
    printf("            [07] - ALTERAR CADASTROS                    \n");
    printf("            [08] - SAIR                                 \n");
    printf("Escolha uma opcao: ");
}

// MENU CADASTRAR PRODUTOS
void Menu_CadastrarProdutos()
{
    system("cls"); // LIMPAR A TELA
    printf("------------------------------------------------\n");
    printf("### LOJAS INFORMATICA - CADASTRO DE PRODUTOS ###\n");
    printf("------------------------------------------------\n");
}

void Menu_CadastrarClientes()
{
    system("cls"); // LIMPAR A TELA
    printf("------------------------------------------------\n");
    printf("### LOJAS INFORMATICA - CADASTRO DE CLIENTES ###\n");
    printf("------------------------------------------------\n");
}

void Menu_CadastrarVendas()
{
    system("cls"); // LIMPAR A TELA
    printf("------------------------------------------------\n");
    printf("### LOJAS INFORMATICA - CADASTRO DE VENDAS   ###\n");
    printf("------------------------------------------------\n");
}

void Menu_Alteracoes()
{
    system("cls"); // LIMPAR A TELA
    printf("------------------------------------------------\n");
    printf("### LOJAS INFORMATICA - ALTERACOES           ###\n");
    printf("------------------------------------------------\n");
    printf("[01] - ALTERAR DADOS CLIENTES                   \n");
    printf("[02] - ALTERAR DADOS PRODUTOS                   \n");
    printf("[03] - EXCLUIR CLIENTES                         \n");
    printf("[04] - EXCLUIR PRODUTOS                         \n");
    printf("[05] - EXCLUIR NOTAS FISCAIS                    \n");
    printf("[06] - VOLTAR AO MENU                           \n");
}

// MOSTRAR PRODUTOS CADASTRADOS
void produtosCadastrados()
{
    int count_produtos = 0;
    float count_valor = 0;
    int count_estoque = 0;
    FILE *arq;
    arq = fopen("produtos.dat", "rb+");
    if (arq == NULL)
    {
        printf("Nao ha produtos cadastrados....Tente novamente...\n");
        system("pause");
    }
    else
    {
        system("cls");
        printf("=============================================================================================================\n");
        printf("#  CODIGO  ##             DESCRICAO             ##        CATEGORIA         ##    VALOR R$    ##  ESTOQUE  ##\n");
        printf("=============================================================================================================\n");

        while (fread(&produto, sizeof(produto), 1, arq))
        {
            count_produtos++;
            count_valor += produto.valor;
            count_estoque += produto.qtd_estoque;
            printf("#   %-6d ##    %-30s ##     %-20s ##  %s %-10.2f ##    %-6d ##\n", produto.cod_produto, produto.nome_produto, produto.categoria, "R$", produto.valor, produto.qtd_estoque);
        }
    }
    fclose(arq);
    printf("=============================================================================================================\n");
    printf(" PRODUTOS: %-63d TOTAL: R$ %.2f ## TOTAL: %d\n", count_produtos, count_valor, count_estoque);
    system("pause");
}

// MOSTRAR CLIENTES CADASTRADOS
void ClientesCadastrados()
{
    FILE *arq2;
    arq2 = fopen("clientes.dat", "rb+");
    if (arq2 == NULL)
    {
        printf("Nao ha clientes cadastrados...Tente novamente....\n");
        system("pause");
    }
    else
    {
        system("cls");
        printf("===========================================================================================================\n");
        printf("#  CODIGO  ##              CLIENTE              ##        TELEFONE          ##       ENDERECO  (CEP)     ##\n");
        printf("===========================================================================================================\n");

        while (fread(&cliente, sizeof(cliente), 1, arq2))
        {
            printf("#    %-5d ##      %-28s ##       %-18s ##       %-19d ##\n", cliente.cod_cliente, cliente.nome_cli, cliente.telefone, cliente.cep);
        }
    }
    fclose(arq2);
    system("pause");
}

// MOSTRAR TODAS AS VENDAS EFETUADAS
void VendasCadastradas()
{
    FILE *arq3;
    arq3 = fopen("vendas.dat", "rb+");
    if (arq3 == NULL)
    {
        printf("Nao ha vendas cadastradas...Tente novamente.....\n");
        system("pause");
    }
    else
    {
        system("cls");
        printf("==========================================================================\n");
        printf("#  CODIGO_NF  ##        VALOR FINAL      ##        CODIGO_CLIENTE       ##\n");
        printf("==========================================================================\n");
        while (fread(&venda, sizeof(venda), 1, arq3))
        {
            printf("#    %-7d  ##     %-8s %-9.2f  ##          %-17d  ##\n", venda.cod_NF, "R$", venda.preco_final, venda.cod_cli);
        }
    }
    fclose(arq3);
    system("pause");
}

void CodigoInvalido()
{
    printf("Codigo invalido...Tente novamente...\n");
    system("pause");
}

// CATEGORIAS DA LOJA

void Categorias()
{
    printf("**********************************\n");
    printf("           CATEGORIAS             \n");
    printf("    [01] - MEMORIAS               \n");
    printf("    [02] - ARMAZENAMENTO          \n");
    printf("    [03] - PROCESSADOR            \n");
    printf("    [04] - PLACA-MAE              \n");
    printf("    [05] - PLACA DE VIDEO         \n");
    printf("    [06] - MONITOR                \n");
    printf("    [07] - PERIFERICOS            \n");
    printf("    [08] - FONTES DE ALIMENTACAO  \n");
}

// VERIFICAR O TOTAL DE PRODUTOS + VALORES NO ESTOQUE
#endif