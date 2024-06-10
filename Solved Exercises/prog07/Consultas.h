#ifndef CONSULTAS_H
#define CONSULTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "BancoDeDados.h"
#include "menus.h"
#include "Cadastros.h"

char categoria[40];

void validarCategoria2(int cat)
{
    if (cat == 1)
    {
        strcpy(categoria, "MEMORIAS");
    }
    if (cat == 2)
    {
        strcpy(categoria, "DEVICE STORAGE");
    }
    if (cat == 3)
    {
        strcpy(categoria, "PERIFERICOS");
    }
    if (cat == 4)
    {
        strcpy(categoria, "ACESSORIOS");
    }
    if (cat == 5)
    {
        strcpy(categoria, "PLACAS DE VIDEO");
    }
    if (cat == 6)
    {
        strcpy(categoria, "PLACA MAE");
    }
    if (cat == 7)
    {
        strcpy(categoria, "PROCESSADOR");
    }
    if (cat == 8)
    {
        strcpy(categoria, "UTILITARIOS");
    }
}

void consulta01() // CONSULTAR TODOS OS PRODUTOS CADASTRADOS
{
    FILE *arq;
    system("cls");
    layoutconsultas();
    ProdutosCadastrados(arq);
}

void consulta02() // CONSULTAR OS PRODUTOS CADASTRADOS POR CATEGORIAS
{
    bool achou;
    int cat;
    FILE *arq;
    system("cls");
    layoutconsultas();
    layoutcategorias();
    printf("Escolha uma categoria: ");
    scanf("%d", &cat);
    validarCategoria2(cat);

    if (cat > 7 && cat < 0)
    {
        CodigoInvalido();
    }

    arq = fopen("produtos.dat", "rb");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo... ou nao ha produtos cadastrados..\n");
        Sleep(1200);
    }
    else
    {
        achou = false;

        while (fread(&produto, sizeof(produto), 1, arq))
        {
            if (strcmp(categoria, produto.categoria) == 0)
            {
                achou = true;
                break;
            }
        }
        if (achou == false)
        {
            printf("Produto nao encontrado no sistema...Tente novamente...\n");
        }
        else
        {

            printf("=================================================================================================================\n");
            printf("##   CODIGO    ##           DESCRICAO              ##                 CATEGORIA             ##    PRECO     ##   \n");
            printf("=================================================================================================================\n");
            fseek(arq, 0, SEEK_SET);
            while (fread(&produto, sizeof(produto), 1, arq))
            {
                if (strcmp(categoria, produto.categoria) == 0)
                {
                    printf("##    %-8d ## %-32s ## %-37s ## R$ %-9.2f  ##\n", produto.cod_produto, produto.nome_produto, produto.categoria, produto.preco_produto);
                }
            }
        }
    }
    fclose(arq);
    system("pause");
}

void consultas03() // CONSULTAR PRODUTOS PELO CODIGO
{
    bool achou;
    int cod_produto;
    FILE *arq;
    arq = fopen("produtos.dat", "rb+");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquvio ou o sistema nao possui cadastrados...\n");
        system("pause");
    }
    else
    {
        achou = false;
        system("cls");
        layoutconsultas();

        printf("Digite o codigo do produto: ");
        scanf("%d", &cod_produto);

        while (fread(&produto, sizeof(produto), 1, arq))
        {
            if (cod_produto == produto.cod_produto)
            {
                achou = true;
                break;
            }
        }

        if (achou == false)
        {
            printf("Produto nao encontrado... Consulte os produtos cadastrados e escolha um produto...\n");
            system("pause");
        }
        else
        {
            printf("=================================================================================================================\n");
            printf("##   CODIGO    ##           DESCRICAO              ##                 CATEGORIA             ##    PRECO     ##   \n");
            printf("=================================================================================================================\n");
            fseek(arq, 0, SEEK_SET);
            while (fread(&produto, sizeof(produto), 1, arq))
            {
                if (cod_produto == produto.cod_produto)
                {
                    printf("##    %-8d ## %-32s ## %-37s ## R$ %-9.2f  ##\n", produto.cod_produto, produto.nome_produto, produto.categoria, produto.preco_produto);
                }
            }
        }
    }
    fclose(arq);
    system("pause");
}

void consultas04()
{
    system("cls");
    layoutconsultas();
    TabelaEstoque();
}
void Consultas()
{
    int op;
    do
    {
        system("cls");
        MenuConsultas(); // Menus.h
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            consulta01();
            break;
        case 2:
            consulta02();
            break;
        case 3:
            consultas03();
            break;
        case 4:
            consultas04();
            break;
        case 5:
            break;
        default:
            CodigoInvalido();
            break;
        }
    } while (op != 5);
}

#endif