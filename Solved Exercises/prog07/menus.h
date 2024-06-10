#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "BancoDeDados.h"

void MenuPrincipal() // MENU PRINCIPAL DO PROGRAMA
{
    printf("==========================================================================\n");
    printf("	  ## GERENCIAMENTO DE VENDAS/ESTOQUE LOJAS INFO100 ##                 \n");
    printf("==========================================================================\n");
    printf("		[01] - CONSULTAS              \n");
    printf("		[02] - CADASTROS              \n");
    printf("		[03] - VENDAS                 \n");
    printf("		[04] - ALTERACOES             \n");
    printf("		[05] - INFO                   \n");
    printf("		[06] - SAIR                   \n");
    printf("               DIGITE UMA OPCAO -->>  ");
}

void MenuConsultas() // MENU PARA CONSULTAS
{
    printf("=============================================================\n");
    printf("	          ## LOJAS INFO100 ## CONSULTAS                  \n");
    printf("=============================================================\n");
    printf("	[01] - CONSULTAR TODOS OS PRODUTOS CADASTRADOS NO SISTEMA\n");
    printf("	[02] - CONSULTAR PRODUTOS POR CATEGORIA                  \n");
    printf("	[03] - CONSULTAR PRODUTO                                 \n");
    printf("	[04] - CONSULTAR ESTOQUE                                 \n");
    printf("	[05] - VOLTAR                                            \n");
    printf("	Escolha uma opcao:                                       \n");
}

void MenuCadastro() // MENU REFERENTE AO CADASTRO DE PRODUTOS
{
    printf("===================================================================\n");
    printf("		## LOJAS INFO100 ## CADASTROS                              \n");
    printf("===================================================================\n");
    printf("	INFORMACOES SOBRE O PRODUTOS                                   \n");
    printf("	[#] CODIGO DO PRODUTO                                          \n");
    printf("	[#] NOME                                                       \n");
    printf("	[#] PRECO                                                      \n");
    printf("	[#] TIPO                                                       \n");
}

void MenuVendas() // MENU PARA EFETUAR VENDAS
{
    printf("===================================================================================\n");
    printf("			 			## LOJAS INFO100 ## VENDAS                                 \n");
    printf("===================================================================================\n");
    printf("	[01] - CADASTRAR CLIENTE		[02] - CADASTRAR VENDA     [03] - VOLTAR       \n");
    printf(" PARA O CADASTRO DE UMA VENDA E NECESSARIO O CADASTRO DO CLIENTE, APOS ISSO FACA O CADASTRO DA VENDA...\n");
}

void MenuAlteracoes() // MENU PARA ALTERACOES
{
    printf("===================================================================================\n");
    printf("			 			## LOJAS INFO100 ## ALTERACOES                             \n");
    printf("===================================================================================\n");
    printf("[01] - EDITAR CLIENTES [02] - ALTERAR DADOS DE UM PRODUTO [03] - ALTERAR PRECO     \n");
}

void layoutconsultas()
{
    printf("===============================================\n");
    printf("	## LOJAS INFO100 ## CONSULTAS              \n");
    printf("===============================================\n");
}

void layoutcadastros()
{
    printf("===================================================================================\n");
    printf("			 			## LOJAS INFO100 ## CADASTROS                              \n");
    printf("===================================================================================\n");
}

void layoutvendas()
{
    printf("===================================================================================\n");
    printf("			 			## LOJAS INFO100 ## VENDAS                                 \n");
    printf("===================================================================================\n");
}

void layoutAlteracoes()
{
    printf("===================================================================================\n");
    printf("			 			## LOJAS INFO100 ## ALTERACOES                             \n");
    printf("===================================================================================\n");
}

/* MENSAGENS DO SISTEMA */

void CodigoInvalido()
{
    printf("Codigo invalido...Tente novamente...\n");
    Sleep(900);
    system("cls");
}

void CadastroSucesso()
{
    printf("Produto Cadastrado com sucesso...\n");
    Sleep(500);
    printf("Aguarde...\n");
    Sleep(800);
    system("cls");
}

/* TABELAS DO SISTEMA */

void layoutcategorias()
{
    printf("[**** CATEGORIAS *****]\n");
    printf(" [1] MEMORIAS \n");
    printf(" [2] DEVICE STORAGE \n");
    printf(" [3] PERIFERICOS \n");
    printf(" [4] ACESSORIOS \n");
    printf(" [5] PLACAS DE VIDEO \n");
    printf(" [6] PLACAS MAE \n");
    printf(" [7] PROCESSADOR \n");
    printf(" [8] UTILITARIO \n");
}

void TabelaEstoque() // Mostrar o estoque do sistema
{
    int soma_produtos = 0;
    FILE *arq2;
    arq2 = fopen("estoque.dat", "rb+");
    if (arq2 == NULL)
    {
        printf("Nao foi possivel abrir o arquivo..\n");
        system("pause");
    }
    else
    {
        printf("=============================================================================================================\n");
        printf("##  CODIGO   ##              PRODUTO               ##         CATEGORIA        ##    QUANTIDADE ESTOQUE   ## \n");
        printf("=============================================================================================================\n");
        while (fread(&estoque, sizeof(estoque), 1, arq2))
        {
            printf("##    %-5d  ##  %-33s ## %-24s ##  %-21d  ##\n", estoque.cod_produto, estoque.nome_produto, estoque.categoria, estoque.qtd_estoque);
            soma_produtos += estoque.qtd_estoque;
        }

        printf("Total de itens : %d\n", soma_produtos);
    }

    fclose(arq2);
    system("pause");
}


#endif