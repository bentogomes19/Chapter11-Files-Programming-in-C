#ifndef CADASTROS_H
#define CADASTROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>

#include "BancoDeDados.h"
#include "menus.h"

void validarCategoria(char cat)
{
    if (cat == 1)
    {
        strcpy(produto.categoria, "MEMORIAS");
    }
    if (cat == 2)
    {
        strcpy(produto.categoria, "DEVICE STORAGE");
    }
    if (cat == 3)
    {
        strcpy(produto.categoria, "PERIFERICOS");
    }
    if (cat == 4)
    {
        strcpy(produto.categoria, "ACESSORIOS");
    }
    if (cat == 5)
    {
        strcpy(produto.categoria, "PLACAS DE VIDEO");
    }
    if (cat == 6)
    {
        strcpy(produto.categoria, "PLACA MAE");
    }
    if (cat == 7)
    {
        strcpy(produto.categoria, "PROCESSADOR");
    }
    if (cat == 8)
    {
        strcpy(produto.categoria, "UTILITARIOS");
    }
}

void ProdutosCadastrados(FILE *arq)
{
    arq = fopen("produtos.dat", "rb");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo... ou nao ha produtos cadastrados..\n");
        Sleep(1200);
    }
    else
    {
        printf("=================================================================================================================\n");
        printf("##   CODIGO    ##           DESCRICAO              ##                 CATEGORIA             ##    PRECO     ##   \n");
        printf("=================================================================================================================\n");
        while (fread(&produto, sizeof(produto), 1, arq))
        {
            printf("##    %-8d ## %-32s ## %-37s ## R$ %-9.2f  ##\n", produto.cod_produto, produto.nome_produto, produto.categoria, produto.preco_produto);
        }
    }
    fclose(arq);
    system("pause");
}

void Cadastros()
{
    FILE *arq, *arq2;
    arq = fopen("produtos.dat", "ab+"); // ABRIR O ARQUVIO PRODUTOS
    arq2 = fopen("estoque.dat", "ab+"); // ABRIR O ARQUIVO ESTOQUE
    if (arq == NULL || arq2 == NULL)
    {
        printf("Nao foi possivel abrir o arquivo..Tente novamente...\n");
        Sleep(600);
    }
    else
    {
        char categoria[40];
        char resp = 'S';
        bool achou;
        int cod_produto, cat;

        while (resp == 'S')
        {
            system("cls");
            MenuCadastro();
            do
            {
                achou = false;
                printf("Digite o codigo do produto: ");
                scanf("%d", &cod_produto);
                fflush(stdin);

                if (cod_produto > 9999 || cod_produto < 1000)
                {
                    CodigoInvalido();
                    MenuCadastro();
                }
                else
                {
                    fseek(arq, 0, SEEK_SET);
                    while (fread(&produto, sizeof(produto), 1, arq))
                    {
                        if (cod_produto == produto.cod_produto)
                        {
                            achou = true;
                            break;
                        }
                    }
                    if (achou == true)
                    {
                        printf("Produto ja cadastrado em nosso sistema...\n");
                        Sleep(500);
                        fseek(arq, 0, SEEK_CUR);
                        printf("Produto # %d\n", produto.cod_produto);
                        printf("# %s \n", produto.nome_produto);
                        printf("# %s \n", produto.categoria);
                        printf("# R$ %.2f \n\n", produto.preco_produto);
                        Sleep(2000);
                        system("cls");
                        MenuCadastro();
                    }
                }

            } while ((cod_produto > 9999 || cod_produto < 1000) || (achou == true));
            produto.cod_produto = cod_produto;

            printf("PRODUTO # %d -> Digite o nome do produto: ", produto.cod_produto);
            fgets(produto.nome_produto, 50, stdin);
            produto.nome_produto[strcspn(produto.nome_produto, "\n")] = '\0';
            fflush(stdin);

            do
            {
                layoutcategorias();
                printf("PRODUTO # %d -> Digite a categoria: ", produto.cod_produto);
                scanf("%d", &cat);

                if (cat > 7 && cat < 0)
                {
                    CodigoInvalido();
                }
            } while (cat > 7 && cat < 0);

            validarCategoria(cat);

            printf("PRODUTO # %d -> Digite o valor Unitario (R$): ", produto.cod_produto);
            scanf("%f", &produto.preco_produto);
            fflush(stdin);

            printf("PRODUTO # %d -> Digite a quantidade : ", produto.cod_produto);
            scanf("%d", &estoque.qtd_estoque);

            printf("Verifique Seus dados\n");
            printf("Produto # %d\n", produto.cod_produto);
            printf("# %s \n", produto.nome_produto);
            printf("# %s \n", produto.categoria);
            printf("# R$ %.2f \n", produto.preco_produto);
            printf("# %d\n\n", estoque.qtd_estoque);
            system("pause");

            strcpy(estoque.nome_produto, produto.nome_produto);
            strcpy(estoque.categoria, produto.categoria);
            estoque.cod_produto = produto.cod_produto;
            fwrite(&estoque, sizeof(estoque), 1, arq2);

            printf("Produto gravado com sucesso...\n");
            Sleep(1200);
            system("cls");
            fwrite(&produto, sizeof(produto), 1, arq);

            printf("Deseja continuar s/n ?: ");
            scanf(" %c", &resp);
            resp = toupper(resp);
            fflush(stdin);
        }
    }
    fclose(arq);
    fclose(arq2);

    ProdutosCadastrados(arq);
}

#endif