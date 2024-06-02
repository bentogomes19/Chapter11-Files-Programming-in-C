#ifndef CADASTRARROUPAS_H
#define CADASTRARROUPAS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "registros.h"

void RoupasCadastradas(FILE *arq1)
{
    arq1 = fopen("roupas.dat", "rb+");
    if(arq1 == NULL)
    {
        printf("Nao foi possivel abrir o arquivo..\n");
        system("pause");
    }
    else
    {
        system("cls");
        printf("            ROUPAS CADASTRADAS              \n");
        printf("==================================================================================================\n");
        printf("##   COD ROUPA   ##     DESCRICAO      ##    COD ESTILISTA    ##    COD ESTACAO    ##   ANO   ##  \n");
        printf("==================================================================================================\n");

        while(fread(&roupa, sizeof(roupa), 1, arq1))
        {
            printf("         %-14d  %-22s  %-21d %-16d %d\n", roupa.codigoR, roupa.descri, roupa.codigoEstilista, roupa.codigoEstacao, roupa.ano);
        }
        
        fclose(arq1);
        system("pause");
    
    }
}


void cadastrarRoupas()
{
    int cod_estilista, cod_estacao, cod_roupa;
    char resp = 'S';
    FILE *arq1, *arq2, *arq3;

    arq1 = fopen("roupas.dat", "ab+");      // ARQUIVO DAS ROUPAS
    arq2 = fopen("estilistas.dat", "rb"); // ARQUIVO DOS ESTILISTAS
    arq3 = fopen("estacoes.dat", "rb");   // ARQUIVO DAS ESTAÇÕES
    if (arq1 == NULL || arq2 == NULL || arq3 == NULL)
    {
        printf("nao foi possivel abrir o arquivo...\n");
        fclose(arq1);
        fclose(arq2);
        fclose(arq3);
        system("pause");
    }
    else
    {
        printf("[03] - CADASTRAR ROUPAS\n");

        while (resp == 'S')
        {
            achou = false;
            printf("Digite o codigo da roupa: "); // CODIGO DA ROUPA
            scanf("%d", &cod_roupa);
            fflush(stdin);

            while (fread(&roupa, sizeof(roupa), 1, arq1))
            {
                if (cod_roupa == roupa.codigoR) // SE USUARIO INFORMAR CODIGO IGUAL AO QUE JA TEMOS NAO PERMITIR O CADASTRO
                {
                    achou = true;
                    break;
                }
            }
            if (achou)
            {
                printf("O codigo informado ja existe...Tente novamente\n");
                system("pause");
                break;
            }

            roupa.codigoR = cod_roupa; // atualizar a variavel para o codigo valido

            printf("digite a descricao da roupa: ");
            gets(roupa.descri);
            fflush(stdin);

            do
            {
                achou = false;
                printf("Digite o codigo do estilista: ");
                scanf("%d", &cod_estilista);

                fseek(arq2, 0, SEEK_SET);

                while (fread(&estilista, sizeof(estilista), 1, arq2))
                {
                    if (cod_estilista == estilista.codigoEstilista)
                    {
                        achou = true;
                        printf("Estilista encontrado\n");
                        system("pause");
                        break;
                    }
                }

                if (achou == false)
                {
                    printf("Estilista nao encontrado... Tente novamente.\n");
                    system("pause");
                }

            } while (achou == false);

            do
            {
                achou = false;
                printf("Digite o codigo da estacao: ");
                scanf("%d", &cod_estacao);

                while (fread(&estacao, sizeof(estacao), 1, arq3))
                {
                    if (cod_estacao == estacao.codigoEstacao)
                    {
                        achou = true;
                        printf("Estacao encontrada...\n");
                        system("pause");
                        break;
                    }
                }

                if (achou == false)
                {
                    printf("Nao foi possivel encontrar a estacao... Tente novamente\n");
                    system("pause");
                }

            } while (achou == false);

            printf("Digite o ano: ");
            scanf("%d", &roupa.ano);

            roupa.codigoEstacao = cod_estacao;
            roupa.codigoEstilista = cod_estilista;
            roupa.codigoR = cod_roupa;

            fwrite(&roupa, sizeof(roupa), 1, arq1);

            printf("Deseja continuar s/n ?: ");
            scanf("%c", &resp);
            resp = toupper(resp);
            fflush(stdin);

        }

        fclose(arq1);
        fclose(arq2);
        fclose(arq3);
        
    }

    RoupasCadastradas(arq1);
}

#endif