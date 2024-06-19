#ifndef ALTERACOES_H
#define ALTERACOES_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "BancoDeDados.h"
#include "menus.h"
#include "CadastroProdutos.h"

void AlterarCliente()
{
    bool achou;
    int cod_cliente;
    FILE *arq2;
    arq2 = fopen("clientes.dat", "rb+");
    if (arq2 == NULL)
    {
        printf("Nao ha clientes cadastrados...Tente novamente....\n");
        system("pause");
    }
    else
    {
        printf("[01] - ALTERAR DADOS DO CLIENTE\n\n");

        do
        {
            printf("OBS: DIGITE 1 PARA VER OS CLIENTES CADASTRADOS || Digite o codigo do cliente: ");
            scanf("%d", &cod_cliente);
            fflush(stdin);
            if (cod_cliente == 1)
            {
                ClientesCadastrados();
            }
            else
            {
                achou = false;
                rewind(arq2);
                while (fread(&cliente, sizeof(cliente), 1, arq2))
                {
                    if (cod_cliente == cliente.cod_cliente)
                    {
                        achou = true;
                        break;
                    }
                }

                if (achou == false)
                {
                    printf("Nao ha clientes cadastrados com o codigo informado....\n");
                    system("pause");
                }
            }

        } while (cod_cliente == 1 || achou == false);

        char nome_cli[50], telefone[20];
        int cep;
        printf("Cliente Localizado!\n\n");
        printf("COD_CLIENTE: #%d\n", cliente.cod_cliente);
        printf("NOME: %s\n", cliente.nome_cli);
        printf("TELEFONE: %s\n", cliente.telefone);
        printf("CEP (ENDERECO): #%d\n", cliente.cep);

        printf("Aterar Dados....\n");
        printf("Digite o nome: ");
        fgets(nome_cli, 50, stdin);
        nome_cli[strcspn(nome_cli, "\n")] = '\0';
        fflush(stdin);

        printf("Digite o telefone: ");
        fgets(telefone, 20, stdin);
        telefone[strcspn(telefone, "\n")] = '\0';

        do
        {
            // CEP PARA SER VALIDO DEVE POSSUIR 8 DIGITOS SEM O "-"
            printf("Digite o CEP (ENDERECO): ");
            scanf("%d", &cep);

            if (cep < 10000000)
            {
                CodigoInvalido();
            }

        } while (cep < 10000000);

        strcpy(cliente.nome_cli, nome_cli);
        strcpy(cliente.telefone, telefone);
        cliente.cep = cep;
        cliente.cod_cliente = cod_cliente;

        fseek(arq2, -sizeof(cliente), SEEK_CUR);
        fwrite(&cliente, sizeof(cliente), 1, arq2);

        fclose(arq2);
        printf("Dados alterados com sucesso...\n");
        Sleep(600);
    }
}

void AlterarProdutos()
{
    int op;
    FILE *arq;
    int cod_produto;
    bool achou;

    arq = fopen("produtos.dat", "rb+");
    if (arq == NULL)
    {
        printf("Nao ha produtos cadastrados no sistema...Tente novamente...\n");
        system("pause");
    }
    else
    {
        printf("[02] - ALTERAR DADOS PRODUTOS\n");
        do
        {
            printf("OBS: DIGITE 1 PARA VER OS PRODUTOS CADASTRADOS || Digite o codigo do produto: ");
            scanf("%d", &cod_produto);
            fflush(stdin);
            if (cod_produto == 1)
            {
                produtosCadastrados();
            }
            else
            {
                achou = false;
                rewind(arq);
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
                    printf("Nao ha produtos cadastrados com o codigo informado....\n");
                    system("pause");
                }
            }

        } while (cod_produto == 1 || achou == false);

        int qtd_estoque;
        float valor;
        char nome_produto[60];

        printf("Produto Encontrado...\n");
        printf("COD_PRODUTO: # %d\n", produto.cod_produto);
        printf("NOME: %s\n", produto.nome_produto);
        printf("CATEGORIA: %s\n", produto.categoria);
        printf("VALOR UNIT(R$): R$ %.2f\n", produto.valor);
        printf("ESTOQUE: %d\n", produto.qtd_estoque);
        system("pause");

        printf("Digite o nome do produto: ");
        fgets(nome_produto, 60, stdin);
        nome_produto[strcspn(nome_produto, "\n")] = '\0';
        fflush(stdin);

        Categorias();
        do
        {
            printf("Informe a categoria: ", cod_produto);
            scanf("%d", &op);

            if (op > 7 || op < 0)
            {
                CodigoInvalido();
            }
            else
            {
                VerificarCategoria(op);
            }

        } while (op > 7 || op < 0);

        printf("Digite o valor R$: ");
        scanf("%f", &valor);

        printf("Digite a quantidade em estoque: ");
        scanf("%d", &qtd_estoque);

        strcpy(produto.nome_produto, nome_produto);
        produto.cod_produto = cod_produto;
        produto.valor = valor;
        produto.qtd_estoque = qtd_estoque;
        fseek(arq, -sizeof(produto), SEEK_CUR);
        fwrite(&produto, sizeof(produto), 1, arq);
        printf("Dados alterados com sucesso...\n");
        Sleep(800);
    }
    fclose(arq);
}

void ExcluirClientes()
{
    int cod_cli;
    bool achou;
    FILE *arq, *temp;
    arq = fopen("clientes.dat", "rb+");
    temp = fopen("temp.dat", "ab+");
    if (arq == NULL)
    {
        printf("Nao ha clientes cadastrados...\n");
        system("pause");
    }
    else
    {
        printf("[03] - EXCLUIR CLIENTE\n\n");
        achou = false;
        printf("Digite o codigo do cliente: ");
        scanf("%d", &cod_cli);

        while (fread(&cliente, sizeof(cliente), 1, arq))
        {
            if (cod_cli == cliente.cod_cliente)
            {
                achou = true;
                printf("Cliente encontrado...\n\n");
                printf("Cliente: %s\n", cliente.nome_cli);
                printf("Codigo: %d\n", cliente.cod_cliente);
                system("pause");
            }
            else
            {
                fwrite(&cliente, sizeof(cliente), 1, temp);
            }
        }

        if (achou == false)
        {
            printf("Nao foi possivel encontrar o cliente...Tente novamente...\n");
            system("pause");
        }
        else
        {
            fclose(arq);
            fclose(temp);

            fseek(arq, -sizeof(cliente), SEEK_CUR);

            remove("clientes.dat");
            rename("temp.dat", "clientes.dat");
            printf("Cliente excluido com sucesso....\n\n");
            Sleep(1600);
            ClientesCadastrados();
        }
    }
    fclose(arq);
    fclose(temp);
}

void Alteracoes()
{
    int op;
    do
    {
        Menu_Alteracoes();
        printf("Digit uma opcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            AlterarCliente();
            break;
        case 2:
            AlterarProdutos();
            break;
        case 3:
            ExcluirClientes();
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            CodigoInvalido();
            break;
        }

    } while (op != 6);
}

#endif