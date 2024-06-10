#ifndef AUMENTO_H
#define AUMENTO_H

#include <stdio.h>
#include <stdlib.h>

#include "registros.h"

void aumento() // proporcionar aumento de 15% aos produtos
{
    FILE *arq, *temp;
    arq = fopen("produtos.dat", "rb");
    temp = fopen("temp.dat", "ab+");
    if (arq == NULL || temp == NULL)
    {
        printf("Nao foi possivel abrir o arquivo...\n");
        system("pause");
    }
    else
    {
        printf("[03] - AUMENTAR PRODUTO EM 15 %\n\n");

        while (fread(&produto, sizeof(produto), 1, arq))
        {
            produto.preco = produto.preco + (produto.preco * 0.15);
            fwrite(&produto, sizeof(produto), 1, temp);
        }

        fclose(arq);
        fclose(temp);

        remove("produtos.dat");
        rename("temp.dat", "produtos.dat");
    }
    printf("Precos alterados com sucesso...\n");
    system("pause");
}

#endif