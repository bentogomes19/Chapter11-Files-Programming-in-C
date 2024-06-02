#ifndef RELATORIO_H
#define RELATORIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void relatorio()
{
    int cod_estacao;
    FILE *arq1, *arq2, *arq3;

    arq1 = fopen("roupas.dat", "rb+");
    arq2 = fopen("estacoes.dat", "rb+");
    arq3 = fopen("estilistas.dat", "rb+");
    if (arq1 == NULL || arq2 == NULL || arq3 == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        system("pause");
    }
    else
    {
        achou = false;
        printf("[04] - RELATORIO.\n");
        printf("Digite o codigo da estacao?: ");
        scanf("%d", &cod_estacao);

        while (fread(&estacao, sizeof(estacao), 1, arq2))
        {
            if (cod_estacao == estacao.codigoEstacao)
            {
                achou = true;
                break;
            }
        }
        if (achou == false)
        {
            printf("Nao foi possivel encontrar o codigo informado.\n");
            fclose(arq1);
            fclose(arq2);
            fclose(arq3);
            system("pause");
        }
        else
        {

            printf("                        RELATORIO                           \n");
            printf("============================================================\n");
            printf("##    ROUPA     ##      ESTILISTA     ##     ESTACAO     ## \n");
            printf("============================================================\n");
            rewind(arq1);

            while (fread(&roupa, sizeof(roupa), 1, arq1))
            {
                if (cod_estacao == estacao.codigoEstacao)
                {
                    fseek(arq3, 0, SEEK_SET); // reinicia o cursor para o inicio do arquvio
                    while (fread(&estilista, sizeof(estilista), 1, arq3))
                    {
                        if (roupa.codigoEstilista == estilista.codigoEstilista)
                        {
                            printf("##  %-10s   ##  %15s   ##  %10s\n", roupa.descri, estilista.nome, estacao.nome);
                            break;
                        }
                    }
                }
            }
        }
    }

    fclose(arq1);
    fclose(arq2);
    fclose(arq3);
    system("pause");
}

#endif