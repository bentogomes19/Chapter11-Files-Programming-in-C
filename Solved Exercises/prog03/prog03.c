#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*BIBLIOTECAS E FUNÇÕES*/

#include "registros.h"           // ARQUIVO ONDE SE ENCONTRA OS REGISTROS
#include "cadastrarEstilistas.h" // FUNÇÃO PARA CADASTRAR OS ESTILISTAS
#include "cadastrarRoupas.h"     // FUNÇÃO PARA O CADASTRO DE ROUPAS
#include "cadastrarEstacoes.h"   // FUNÇÃO PARA O CADASTRO DAS ESTAÇÕES
#include "relatorio.h"           // UM RELATÓRIO COM TODAS AS ROUPAS CADASTRAS

int main(void) // função principal do programa
{

    int op;
    do
    {
        system("cls");
        printf("*************** LOJAS MARSELHA - XVII ***************\n");
        printf("                   MENU PRINCIPAL                    \n");
        printf("            [01] - CADASTRAR ESTILISTAS              \n");
        printf("            [02] - CADASTRAR ESTACOES                \n");
        printf("            [03] - CADASTRAR ROUPAS                  \n");
        printf("            [04] - APRESENTAR RELATORIO              \n");
        printf("            [05] - SAIR                              \n");
        printf("***************   ESCOLHA UMA OPCAO    **************\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            cadastrarEstilistas();
            break;
        case 2:
            cadastrarEstacoes();
            break;
        case 3:
            cadastrarRoupas();
            break;
        case 4:
            relatorio();
            break;
        case 5:
            break;
        default:
            printf("Codigo invalido...Tente novamente...\n");
            system("pause");
            break;
        }

    } while (op != 5);

    return 0;
}