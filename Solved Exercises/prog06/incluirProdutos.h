#ifndef INCLUIRPRODUTOS_H
#define INCLUIRPRODUTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "registros.h"

void cadastrar()
{
    FILE *arq;
    bool achou;
    char resp = 'S';
    int cod_produto;
    arq = fopen("produtos.dat", "ab+");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquvio...\n");
        system("pause");
    }
    else
    {

        while (resp == 'S')
        {
            do
            {
                achou = false;
                printf("Digite o codigo do produto: ");
                scanf("%d", &cod_produto);
                fflush(stdin);

                fseek(arq, 0, SEEK_SET);

                while (fread(&produto, sizeof(produto), 1, arq))
                {
                    if (cod_produto == produto.codigo)
                    {
                        achou = true;
                        break;
                    }
                }
                if (achou == true)
                {
                    printf("Ja existe um produto cadastrado com este codigo...Tente novamente....\n");
                    system("pause");
                }

            } while (achou == true);

            printf("Informe a descricao do produto: ");
            fgets(produto.desc, 60, stdin);
            produto.desc[strcspn(produto.desc, "\n")] = '\0';
            fflush(stdin);

            printf("Digite o preco R$: ");
            scanf("%f", &produto.preco);
            produto.codigo = cod_produto;

            fwrite(&produto, sizeof(produto), 1, arq);

            printf("Deseja continuar s/n ?: ");
            scanf(" %c", &resp);
            resp = toupper(resp);
            fflush(stdin);
        }
    }

    fclose(arq); // Fecha o arquivo
}

void mostrarProdutos()
{
    FILE *arq1;
    arq1 = fopen("produtos.dat", "rb");
    if (arq1 == NULL)
    {
        printf("Nao ha produtos cadastrados...\n");
    }
    else
    {
        printf("=================================================================================\n");
        printf("##   CODIGO    ##            DESCRICAO              ##       PRECO (R$)      ##  \n");
        printf("==================================================================================\n");

        while (fread(&produto, sizeof(produto), 1, arq1))
        {
            printf("      %-15d  %-36s R$ %.2f \n", produto.codigo, produto.desc, produto.preco);
        }
    }

    fclose(arq1); // fecha o arquivo
    system("pause");
}

void incluirProdutos()
{
    int op;

    do
    {
        system("cls");
        printf("++++++++++++++++ INCLUIR PRODUTOS ++++++++++++++++\n");
        printf("            [01] - CADASTRAR PRODUTOS             \n");
        printf("            [02] - VER PRODUTOS CADASTRADOS       \n");
        printf("            [03] - VOLTAR AO MENU                 \n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            cadastrar();
            break;
        case 2:
            mostrarProdutos();
            break;
        case 3:
            break;
        default:
            printf("Codigo invalido...Tente novamente...\n");
            system("pause");
            break;
        }

    } while (op != 3);
}

#endif