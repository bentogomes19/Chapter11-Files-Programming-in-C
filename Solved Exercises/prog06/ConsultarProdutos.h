#ifndef CONSULTARPRODUTOS_H
#define CONSULTARPRODUTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registros.h"

void ConsultarProdutos()
{
    FILE *arq;
    arq = fopen("produtos.dat", "rb");
    if(arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo...\n");
        system("pause");
    }
    else
    {
        printf("[02] - CONSULTAR PRODUTOS COM MAIS DE R$ 500,00\n\n");

        printf("=================================================================================\n");
        printf("##   CODIGO    ##            DESCRICAO              ##       PRECO (R$)      ##  \n");
        printf("==================================================================================\n");

        while(fread(&produto, sizeof(produto), 1, arq))
        {
            if(produto.preco > 500)
            {
                printf("      %-15d  %-36s R$ %.2f \n", produto.codigo, produto.desc, produto.preco);
            }
        }
    }

    fclose(arq);
    system("pause");
}

#endif