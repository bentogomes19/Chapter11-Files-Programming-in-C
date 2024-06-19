// Criado por Bento Junior Suzart Gomes
#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "CadastroProdutos.h"
#include "CadastroClientes.h"
#include "CadastroVendas.h"
#include "Alteracoes.h"

int main(void)
{
    int op;
    do
    {
        system("cls");
        Menu_Principal();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            CadastroProdutos();
            break;
        case 2:
            CadastroClientes();
            break;
        case 3:
            CadastroVendas();
            break;
        case 4:
            produtosCadastrados();
            break;
        case 5:
            ClientesCadastrados();
            break;
        case 6:
            VendasCadastradas();
            break;
        case 7:
            Alteracoes();
            break;
        case 8:
            break;
        default:
            CodigoInvalido();
            break;
        }

    } while (op != 8);

    return 0;
}
