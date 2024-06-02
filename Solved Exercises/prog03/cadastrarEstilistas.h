#ifndef CADASTRARESTILISTAS_H
#define CADASTRARESTILISTAS_H

#include "registros.h" // VARIAVEIS GLOBAIS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void arquivo_teste(FILE *arq)
{
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo...Reinicie o programa");
        system("pause");
    }
}

void mostrarEstilistas(FILE *arq)
{
    arq = fopen("estilistas.dat", "rb");
    arquivo_teste(arq);

    system("cls"); // VER OS ESTILISTAS CADASTRADOS
    printf("                        ESTILISTAS CADASTRADOS                         \n");
    printf("=======================================================================\n");
    printf("##    CODIGO     ##         NOME          ##      SALARIO (R$)    ##   \n");
    printf("=======================================================================\n");

    while (fread(&estilista, sizeof(estilista), 1, arq))
    {
        printf("     %-11d %-6s %-17s %-10s R$ %.2f \n", estilista.codigoEstilista, "##", estilista.nome, "##", estilista.salario);
    }

    fclose(arq);

    system("pause");
}

void cadastrarEstilistas()
{
    char resp = 'S';
    int codigoEstilista, op;
    FILE *arq;
    arq = fopen("estilistas.dat", "ab+"); // abre o arquivo "estilistas.dat" com a possibilidade de anexar dados ao arquIVO

    arquivo_teste(arq); // verifica se o arquivo foi aberto

    /* MENU DO PROGRAMA */
    printf("[01] - CADASTRAR ESTILISTAS\n\n");
    printf("Dados a serem cadastrados (Codigo do estilista, Nome do Estilista e Salario)...\n\n");
    printf("DIGITE 1 PARA VER OS ESTILISTAS CADASTRADOS OU ZERO PARA INICIAR UM CADASTRO... ");
    scanf(" %d", &op);
    if (op == 1) // ESTILISTAS CADASTRADOS
    {
        mostrarEstilistas(arq);
    }
    if(op == 0) // INICIAR CADASTROS
    {
        while (resp == 'S')
        {
            do // Cada estilista possui seu codigo -> codigo unico, logo nao permitir o cadastro de codigos iguais
            {
                achou = false;                            // Significa que o codigo NAO foi encontrado
                printf("Digite o codigo do estilista: "); // CODIGO DO ESTILISTA
                scanf(" %d", &codigoEstilista);
                fflush(stdin);

                fseek(arq, 0, SEEK_SET); // O CURSOR RETORNA AO COMEÇO DO ARQUIVO "PONTEIRO ZERO"

                while (fread(&estilista, sizeof(estilista), 1, arq)) // PROCURA NO ARQUIVO SE EXISTE ALGUM CODIGO IGUAL
                {
                    if (codigoEstilista == estilista.codigoEstilista)
                    {
                        achou = true; // Significa que o codigo FOI ENCONTRADO, portanto, nao permitir o cadastro
                        printf("O codigo informado ja existe em nosso sistema... Tente novamente...\n");
                        system("pause");
                        break; // encerra o laço pois ja verificou-se que o usuario inseriu um codigo semelhante cadastrado no sistema
                    }
                }

            } while (achou == true);
            estilista.codigoEstilista = codigoEstilista;

            printf("Digite o nome do estilista: ");
            gets(estilista.nome);

            printf("Digite o salario do estilista R$: ");
            scanf(" %f", &estilista.salario);

            fwrite(&estilista, sizeof(estilista), 1, arq);

            printf("Deseja continuar [s] [n] ?: ");
            scanf(" %c", &resp);
            resp = toupper(resp);
            fflush(stdin);
        }

        fclose(arq); // fecha o arquivo "estilistas.dat"

        mostrarEstilistas(arq);

    }
    if (op != 1 && op != 0)
    {
        fclose(arq);
        printf("Codigo invalido...Tente novamente\n");
        system("pause");
    }

}

#endif