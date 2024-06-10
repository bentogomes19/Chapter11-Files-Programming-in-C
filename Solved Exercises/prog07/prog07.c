#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "menus.h"
#include "Cadastros.h"
#include "Consultas.h"
#include "Alteracoes.h"
#include "Vendas.h"
#include "BancoDeDados.h" // REGISTROS

int main(void)
{
    int op;
    do
    {
        system("cls");
        MenuPrincipal();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            Consultas(); // CONSULTAS.H
            break;
        case 2: 
            Cadastros(); // CADASTROS.H
            break;
        case 3:
            Vendas(); // VENDAS.H
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            CodigoInvalido(); // MENSAGEM DO SISTEMA "MENUS.H"
            break;
        }
    } while (op != 6);

    return 0;
}