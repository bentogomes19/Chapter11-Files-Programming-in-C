#include <stdio.h>
#include <stdlib.h>

#include "registros.h"
#include "incluirProdutos.h"
#include "ConsultarProdutos.h"

/*15. Faça um programa para criar um arquivo chamado PRODUTOS.DAT, em que cada registro será composto
pelos seguintes campos: codigo, descricao e preco.

16. Faça um programa para incluir produtos no arquivo criado no Exercício 15, lembrando que não podem
existir dois produtos com o mesmo código.

17. Faça um programa para consultar a descrição de todos os produtos que possuem preço superior a R$
500,00.*/

int main(void)
{
    int op;
    do
    {
        system("cls");
        printf("**********************************************\n");
        printf("                    MENU DE OPCOES            \n");
        printf("**********************************************\n");
        printf("       [01] - INCLUIR PRODUTOS                \n");
        printf("       [02] - CONSULTAR PRODUTOS (>R$ 500,00 )\n");
        printf("       [03] - SAIR                            \n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            incluirProdutos();
            break;
        case 2:
            ConsultarProdutos();
            break;
        case 3:
            break;
        default:
            printf("Codigo invalido.... Tente novamente...\n");
            system("pause");
            break;
        }

    } while (op != 3);

    return 0;
}