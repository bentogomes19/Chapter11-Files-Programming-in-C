#ifndef CADASTROPRODUTOS_H
#define CADASTROPRODUTOS_H
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

void VerificarCategoria(int op)
{
    if (op == 1)
    {
        strcpy(produto.categoria, "MEMORIAS");
    }
    if (op == 2)
    {
        strcpy(produto.categoria, "ARMAZENAMENTO");
    }
    if (op == 3)
    {
        strcpy(produto.categoria, "PROCESSADOR");
    }
    if (op == 4)
    {
        strcpy(produto.categoria, "PLACA-MAE");
    }
    if (op == 5)
    {
        strcpy(produto.categoria, "PLACA DE VIDEO");
    }
    if (op == 6)
    {
        strcpy(produto.categoria, "MONITOR");
    }
    if (op == 7)
    {
        strcpy(produto.categoria, "PERIFERICOS");
    }
    if (op == 8)
    {
        strcpy(produto.categoria, "FONTES DE ALIMENTACAO");
    }
    produto.categoria[strcspn(produto.categoria, "\n")] = '\0';
}

void CadastroProdutos()
{
    char resp = 'S';
    char nome_produto[60];
    bool achou;
    int cod_produto, qtd_estoque, op;
    float valor;
    FILE *arq;
    arq = fopen("produtos.dat", "ab+");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo...Tente novamente...\n");
    }
    else
    {
        while (resp == 'S')
        {
            Menu_CadastrarProdutos();
            do // VALIDAR CODIGO USUARIO
            {
                achou = false;
                printf("Digite o codigo do produto: ");
                scanf("%d", &cod_produto);
                fflush(stdin);

                if(cod_produto < 1000 || cod_produto > 9999)
                {
                    CodigoInvalido();
                    Menu_CadastrarProdutos();
                }
                else
                {

                    rewind(arq);
                    while (fread(&produto, sizeof(produto), 1, arq))
                    {
                        if (cod_produto == produto.cod_produto)
                        {
                            achou = true; // CODIGO INFORMADO É O MESMO JA CADASTRADO
                            break;
                        }
                    }
                    if (achou == true)
                    {
                        printf("O codigo informado ja existe em nosso sistema...Tente novamente...\n");
                        system("pause");
                        Menu_CadastrarProdutos();
                    }
                }

            } while ((cod_produto < 1000 || cod_produto > 9999) || (achou == true));

            printf("COD #%d -> Digite o nome do produto: ", cod_produto);
            fgets(nome_produto, 60, stdin);
            nome_produto[strcspn(nome_produto, "\n")] = '\0';
            fflush(stdin);

            printf("COD #%d Digite o valor unitário R$: ", cod_produto);
            scanf("%f", &valor);

            printf("COD #%d Informe o estoque: ", cod_produto);
            scanf("%d", &qtd_estoque);

            Categorias();
            do
            {
                printf("COD #%d Informe a categoria: ", cod_produto);
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
            // ARMAZENANDO OS DADOS NA STRUCT
            produto.cod_produto = cod_produto;
            strcpy(produto.nome_produto, nome_produto);
            produto.qtd_estoque = qtd_estoque;
            produto.valor = valor;

            fwrite(&produto, sizeof(produto), 1, arq);
            printf("Produto gravado com sucesso...\n");
            Sleep(1500);

            fflush(stdin);
            printf("Deseja continuar [s] [n] ?: ");
            scanf("%c", &resp);
            resp = toupper(resp);
        }
    }
    fclose(arq);
    produtosCadastrados();
}

#endif