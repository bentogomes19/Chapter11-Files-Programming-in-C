#ifndef CADASTRARESTACOES_H
#define CADASTRARESTACOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "registros.h"

void mostrarEstacoes(FILE *arq)
{
    arq = fopen("estacoes.dat", "rb");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo\n");
        system("pause");
    }
    else
    {
        system("cls");

        printf("=====================================================\n");
        printf("##   CODIGO ESTACAO     ##         NOME          ##  \n");
        printf("=====================================================\n");

        while (fread(&estacao, sizeof(estacao), 1, arq))
        {
            printf("       %-25d  %s\n", estacao.codigoEstacao, estacao.nome);
        }
        fclose(arq);
        system("pause");
    }
}

void cadastrarEstacoes()
{

    int cod_estacao;
    char resp = 'S';
    FILE *arq;
    arq = fopen("estacoes.dat", "ab+");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo...\n");
        system("pause");
    }
    else
    {
        printf("[02] - CADASTRAR ESTACOES\n");

        while (resp == 'S')
        {

            achou = false;
            printf("Digite o codigo da estacao?: ");
            scanf("%d", &cod_estacao);
            fflush(stdin);

            while (fread(&estacao, sizeof(estacao), 1, arq))
            {
                if (cod_estacao == estacao.codigoEstacao)
                {
                    achou = true;
                    break;
                }
            }

            if (achou == true)
            {
                printf("o codigo informado ja esta cadastrado em nosso sistema.\n");
                system("pause");
                break;
            }

            estacao.codigoEstacao = cod_estacao;

            printf("Digite o nome da estacao: ");
            gets(estacao.nome);
            fflush(stdin);

            fwrite(&estacao, sizeof(estacao), 1, arq);

            printf("Deseja continuar [s] [n]?: ");
            scanf(" %c", &resp);
            resp = toupper(resp);
        }

        fclose(arq);
    }

    mostrarEstacoes(arq);
}

#endif