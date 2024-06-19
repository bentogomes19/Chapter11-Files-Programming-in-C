#ifndef CADASTROVENDAS_H
#define CADASTROVENDAS_H

/*BIBLIOTECAS PRIMÁRIAS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>
/*FUNÇÕES EM ARQUIVOS .H*/
#include "BancoDeDados.h"
#include "menus.h"

void CadastroVendas()
{
    char resp;
    bool achou;
    int cod_cliente, cod_produto, qtd_usr, cod_NF, qtd_soma_usr = 0;
    float soma_valor = 0;
    FILE *arq, *arq2, *arq3, *temp1;
    arq = fopen("produtos.dat", "rb+");
    arq2 = fopen("clientes.dat", "rb+");
    if (arq2 == NULL)
    {
        printf("Nao ha clientes cadastrados...Por Favor, Tente novamente...\n");
    }
    else
    {
        Menu_CadastrarVendas();
        do
        {
            achou = false;
            printf("Digite o codigo do cliente: ");
            scanf("%d", &cod_cliente);

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
                printf("Cliente nao encontrado...Tente novamente....\n");
                system("pause");
                Menu_CadastrarVendas();
            }

        } while (achou == false);

        do
        {
            resp = 'S';
            do
            {
                achou = false;
                printf("COD_CLI # %d --> Digite o codigo do produto: ", cod_cliente);
                scanf("%d", &cod_produto);

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
                    printf("Codigo do produto nao encontrado...Tente novamnete...\n");
                    system("pause");
                    Menu_CadastrarVendas();
                }

            } while (achou == false);
            // MOSTRANDO O PRODUTO PARA O USUÁRIO
            printf("----------------------------\n");
            printf("Produto encontrado...       \n");
            printf("COD_PRODUTO: # %d           \n", produto.cod_produto);
            printf("NOME: # %s                  \n", produto.nome_produto);
            printf("CATEGORIA: # %s             \n", produto.categoria);
            printf("ESTQUE: # %d                \n", produto.qtd_estoque);
            printf("----------------------------\n");
            printf("PRECO UNIT: R$ %.2f         \n", produto.valor);
            printf("----------------------------\n");
            system("pause");

            printf("COD_PROD # %d --> Digite a quantidade: ", cod_produto);
            scanf("%d", &qtd_usr);
            venda.cod_produto[count_produto] = cod_produto; // PARA MOSTRAR AO USUÁRIO NA NOTA FISCAL
            venda.imposto[count_produto] = produto.valor * 0.205;
            if (produto.valor > 250)
            {
                venda.desconto[count_produto] = produto.valor * 0.10;
            }
            else if (strcmp(produto.categoria, "PROCESSADOR") == 0)
            {
                venda.desconto[count_produto] = produto.valor * 0.05;
            }
            else
            {
                venda.desconto[count_produto] = 0;
            }
            qtd_soma_usr += qtd_usr;
            produto.qtd_estoque -= qtd_usr;

            fseek(arq, -sizeof(produto), SEEK_CUR);
            fwrite(&produto, sizeof(produto), 1, arq); // Escrevendo a struct no arquivo "produtos.dat"

            count_produto++;
            soma_valor += qtd_usr * produto.valor;

            if (count_produto > 8)
            {
                printf("Voce atingiu o limite de comprar por notas...Caso queira realizar novas compras...Inicie outro cadastro...\n");
                system("pause");
            }
            else
            {
                fflush(stdin);
                printf("Deseja cadastrar mais produtos a Nota Fiscal.. [s][n]?: ");
                scanf("%c", &resp);
                resp = toupper(resp);
            }

        } while (count_produto <= 8 && resp == 'S');

        fclose(arq); // FECHANDO O ARQUIVO "Produtos.dat"
        arq3 = fopen("vendas.dat", "ab+");
        if (arq3 == NULL)
        {
            printf("Nao foi posssivel abrir o arquvio...\n");
            system("pause");
        }
        else
        {

            do
            {
                achou = false;
                printf("Digite o codigo da nota fiscal: ");
                scanf("%d", &cod_NF);

                rewind(arq3);
                while (fread(&venda, sizeof(venda), 1, arq3))
                {
                    if (cod_NF == venda.cod_NF)
                    {
                        achou = true;
                        break;
                    }
                }
                if (achou == true)
                {
                    printf("Nota fiscal ja cadastrada no sistema...Tente novamente....\n");
                    system("pause");
                }

            } while (achou == true);

            float soma_imposto = 0;
            float soma_desc = 0;
            /// INSERINDO OS DADOS NO ARQUIVO "vendas.dat"
            for (int i = 0; i < count_produto; i++)
            {
                soma_imposto += venda.imposto[i];
                soma_desc += venda.desconto[i];
            }
            venda.cod_cli = cod_cliente;
            venda.cod_NF = cod_NF;

            venda.preco_final = soma_valor + soma_imposto - soma_desc;
            fwrite(&venda, sizeof(venda), 1, arq3);

            printf("----------------------------------\n");
            printf("            NOTA FISCAL # %d       \n", venda.cod_NF);
            printf("----------------------------------\n");
            printf("COD_CLIENTE: %d                   \n", venda.cod_cli);
            printf("COD_PRODUTO: ");
            for (int i = 0; i < count_produto; i++)
            {
                printf("#%d  ", venda.cod_produto[i]);
            }
            printf("\nIMPOSTOS: ");
            for (int i = 0; i < count_produto; i++)
            {
                printf("R$ %.2f ", venda.imposto[i]);
            }
            printf("\nDESCONTOS: R$ %.2f                \n", soma_desc);
            printf("QUANTIDADE: %d                    \n", qtd_soma_usr);
            printf("----------------------------------\n");
            printf("VALOR FINAL: R$ %.2f \n\n", venda.preco_final);
            printf("----------------------------------\n");
        }
        fclose(arq3);
        system("pause");
    }
    VendasCadastradas();
}

#endif