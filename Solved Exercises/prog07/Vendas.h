#ifndef VENDAS_H
#define VENDAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>

#include "BancoDeDados.h"
#include "menus.h"

void CadastrarClientes() // CADASTRO DE CLIENTES
{
    char nome_cli[40], telefone[20], endereco[60], cpf[13];
    int cod_cli;
    bool achou;
    FILE *arq3;
    arq3 = fopen("clientes.dat", "ab+");
    if (arq3 == NULL)
    {
        printf("Nao foi possivel abrir o arquivo ou nao ha clientes cadastrados...\n");
    }
    else
    {
        printf("[01] - CADASTRAR CLIENTES\n");

        do
        {
            achou = false;
            printf("Digite o codigo do cliente: ");
            scanf("%d", &cod_cli);
            fflush(stdin);

            while (fread(&Cliente, sizeof(Cliente), 1, arq3))
            {
                if (cod_cli == Cliente.cod_cliente)
                {
                    achou = true;
                    break;
                }
            }
            if (achou == true)
            {
                printf("Cliente ja cadastrado no sistema..\n ");
            }

        } while (achou == true);

        printf("Digite o nome do cliente: ");
        fgets(nome_cli, 40, stdin);
        nome_cli[strcspn(nome_cli, "\n")] = '\0';
        fflush(stdin);

        printf("Digite o telefone: ");
        fgets(telefone, 20, stdin);
        telefone[strcspn(telefone, "\n")] = '\0';

        printf("Digite o endereco: ");
        fgets(endereco, 60, stdin);
        endereco[strcspn(endereco, "\n")] = '\0';
        fflush(stdin);

        Cliente.cod_cliente = cod_cli;
        strcpy(Cliente.nome_cliente, nome_cli);
        strcpy(Cliente.telefone, telefone);
        strcpy(Cliente.endereco, endereco);

        fwrite(&Cliente, sizeof(Cliente), 1, arq3);
        printf("Cadastro realizado com sucesso...\n");
        Sleep(1600);
    }
    fclose(arq3);
    system("cls");
}

void CadastrarVendas()
{
    int cod_cli, cod_produto, qtd_cli, estoque_qtd;
    bool achou;
    FILE *arq5, *arq4, *arq3, *arq2, *arq, *temp;
    arq4 = fopen("vendas.dat", "ab+");
    arq3 = fopen("clientes.dat", "rb+");
    arq2 = fopen("estoque.dat", "rb+");
    arq = fopen("produtos.dat", "rb+");

    if (arq4 == NULL || arq3 == NULL || arq2 == NULL || arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo ou nao ha clientes cadastrados...\n");
    }
    else
    {
        printf("[02] - CADASTRAR VENDA\n");

        do
        {
            achou = false;
            printf("Digite o codigo do cliente: ");
            scanf("%d", &cod_cli);

            fseek(arq3, 0, SEEK_SET);
            while (fread(&Cliente, sizeof(Cliente), 1, arq3))
            {
                if (cod_cli == Cliente.cod_cliente)
                {
                    achou = true;
                    break;
                }
            }
            if (achou == false)
            {
                printf("Cliente nao encontrado...Tente novamente...\n");
            }
        } while (achou == false);

        do
        {
            achou = false;
            printf("Digite o codigo do produto: ");
            scanf("%d", &cod_produto);
            fseek(arq2, 0, SEEK_SET);

            while (fread(&estoque, sizeof(estoque), 1, arq2))
            {
                if (cod_produto == estoque.cod_produto)
                {
                    achou = true;
                    break;
                }
            }

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
                printf("Nao foi possivel encontrar o produto...Tente novamnete...\n");
            }

        } while (achou == false && cod_produto != 1);
        fclose(arq);
        fclose(arq3);
        arq5 = fopen("NotasFiscais.dat", "ab+");
        if (arq5 == NULL)
        {
            printf("Erro ao abrir o arquivo...\n");
        }
        else
        {

            printf("Produto encontrado....\n\n");
            printf("CODIGO ==> %d\n", produto.cod_produto);
            printf("NOME ==> %s\n", produto.nome_produto);
            printf("CATEGORIA ==> %s\n", produto.categoria);
            printf("VALOR ==> R$ %.2f\n", produto.preco_produto);
            printf("ESTOQUE ==> %d\n", estoque.qtd_estoque);
            system("pause");

            // A SER DESENVOLVIDA, ATUALIZAR O ESTOQUE...
            printf("Informe a quantidade desejada: ");
            scanf("%d", &qtd_cli);
            

            printf("Informe o codigo da nota fiscal: ");
            scanf("%d", &notaFiscal.cod_NF);

            printf("Aguarde...\n\n");
            Sleep(1600);
            system("cls");

            // GERANDO NOTA FISCAL PARA O CLIENTE
            notaFiscal.cod_cliente = cod_cli;
            notaFiscal.cod_produto = cod_produto;
            // CALCULAR IMPOSTO // ICMS = 18% + IOF = 2.5% TOTAL = 20.5%
            notaFiscal.imposto = produto.preco_produto * (0.205);
            if (produto.preco_produto > 350)
            {
                notaFiscal.desconto = produto.preco_produto * 0.15;
            }
            else
            {
                notaFiscal.desconto = 0;
            }
            notaFiscal.preco_final = (produto.preco_produto * qtd_cli) + notaFiscal.imposto - notaFiscal.desconto;
            strcpy(notaFiscal.nome_cliente, Cliente.nome_cliente);
            fwrite(&notaFiscal, sizeof(notaFiscal), 1, arq5);
        }

        fclose(arq5);

        printf("----------* NOTA FISCAL *----------\n");
        printf("NF #00%d \n", notaFiscal.cod_NF);
        printf("CODIGO_PRODUTO # %d \n", notaFiscal.cod_produto);
        printf("CODIGO_CLIENTE # %d \n", notaFiscal.cod_cliente);
        printf("VALOR R$ ** R$ %.2f\n", produto.preco_produto);
        printf("IMPOSTOS ** R$ %.2f \n", notaFiscal.imposto);
        printf("DESCONTO: ** R$ %.2f \n", notaFiscal.desconto);
        printf("QUANTIDADE: %d \n", qtd_cli);
        printf("--------------------------\n");
        printf("TOTAL: R$ %.2f\n", notaFiscal.preco_final);
        printf("CLIENTE: %s \n", notaFiscal.nome_cliente);
        system("pause");
    }
}

void Vendas()
{
    int op;
    // arq = produtos.dat, arq2 = estoque.dat, arq3 = clientes.dat, arq4 = vendas.dat;
    do
    {
        MenuVendas();
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            CadastrarClientes();
            break;
        case 2:
            CadastrarVendas();
            break;
        case 3:
            break;
        default:
            CodigoInvalido();
            break;
        }

    } while (op != 3);
}

#endif