#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cadastro.h"
#include "dados.h"

int main()
{
    bool achou;
    char nome1[16], senha1[60];
    FILE *arq;

    cadastro();

    do
    {
        system("cls");
        printf("**********************\n");
        printf("    TELA DE LOGIN     \n");
        printf("**********************\n");
        printf("Digite o usuario: ");
        fgets(nome1, 16, stdin);
        nome1[strcspn(nome1, "\n")] = '\0';

        printf("Digite a senha: ");
        fgets(senha1, 60, stdin);
        senha1[strcspn(senha1, "\n")] = '\0';
        fflush(stdin);

        achou = false;
        arq = fopen("dados.dat", "rb+");
        if (arq == NULL)
        {
            printf("Nao foi possivel abrir o arquvio...Tente novamente...\n");
            system("pause");
        }
        else
        {
            while (fread(&user, sizeof(user), 1, arq))
            {
                if (strcmp(nome1, user.nome) == 0 && strcmp(senha1, user.senha) == 0)
                {
                    achou = true;
                    break;
                }
            }
        }
        fclose(arq);
        if (achou == false)
        {
            printf("Usuario ou Senhas invalidas...Tente novamente...\n\n");
            system("pause");
        }
    } while (achou == false);

    printf("Bem vindo --> %s\n", nome1);

    return 0;
}