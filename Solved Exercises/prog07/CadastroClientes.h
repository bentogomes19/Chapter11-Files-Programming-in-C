#ifndef CADASTROCLIENTES_H
#define CADASTROCLIENTES_H

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

void CadastroClientes()
{
    bool achou;
    int cod_cliente;
    int cep;
    char telefone[20], resp = 'S';
    char nome_cli[50];
    FILE *arq2;
    arq2 = fopen("clientes.dat", "ab+");
    if (arq2 == NULL)
    {
        printf("Nao foi possivel abrir o arquivo...Tente novamente...\n");
        system("pause");
    }
    else
    {

        while (resp == 'S')
        {
            Menu_CadastrarClientes();

            do
            {
                achou = false;
                printf("Digite o codigo do cliente: ");
                scanf("%d", &cod_cliente);
                fflush(stdin);

                if (cod_cliente < 100 || cod_cliente > 999)
                {
                    CodigoInvalido();
                    Menu_CadastrarClientes();
                }
                else
                {
                    rewind(arq2);
                    while (fread(&cliente, sizeof(cliente), 1, arq2))
                    {
                        if (cod_cliente == cliente.cod_cliente)
                        {
                            achou = true;
                            break;
                        }
                    }

                    if (achou == true)
                    {
                        printf("Ja existe um cliente cadastrado com esse codigo...Tente novamente...\n");
                        system("pause");
                        Menu_CadastrarClientes();
                    }
                }
            } while ((cod_cliente < 100 || cod_cliente > 999) || (achou == true));

            printf("COD_CLI # %d --> Digite o nome: ", cod_cliente);
            fgets(nome_cli, 50, stdin);
            nome_cli[strcspn(nome_cli, "\n")] = '\0';
            fflush(stdin);

            printf("COD_CLI # %d --> Digite o telefone: ", cod_cliente);
            fgets(telefone, 20, stdin);
            telefone[strcspn(telefone, "\n")] = '\0';

            do
            {
                // CEP PARA SER VALIDO DEVE POSSUIR 8 DIGITOS SEM O "-"
                printf("COD_CLI # %d --> Digite o CEP (ENDERECO): ", cod_cliente);
                scanf("%d", &cep);

                if(cep < 10000000)
                {
                    CodigoInvalido();
                }
                
            } while (cep < 10000000);

            cliente.cod_cliente = cod_cliente;
            strcpy(cliente.nome_cli, nome_cli);
            strcpy(cliente.telefone, telefone);
            cliente.cep = cep;

            fwrite(&cliente, sizeof(cliente), 1, arq2);

            printf("Cliente cadastrado com sucesso...\n");
            Sleep(1600);

            fflush(stdin);
            printf("Deseja continuar [s][n] ?: ");
            scanf("%c", &resp);
            resp = toupper(resp);       
        }
    }
    fclose(arq2);
    ClientesCadastrados();
}

#endif