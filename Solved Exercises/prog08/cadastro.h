#ifndef CADASTRO_H
#define CADASTRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

void cadastro()
{
    FILE *arq;

    printf("*************************\n");
    printf("    TELA DE CADASTRO     \n");
    printf("*************************\n");
    printf("Digite o nome de usuario: ");
    fgets(user.nome, 16, stdin);
    user.nome[strcspn(user.nome, "\n")] = '\0';

    printf("Digite a sua senha: ");
    fgets(user.senha, 60, stdin);
    user.senha[strcspn(user.senha, "\n")] = '\0';
    fflush(stdin);

    if(strlen(user.senha) > 60)
    {
        printf("Nao é permitido o cadastro com mais de 60 caracteres...\n");
        system("pause");
    }
    else
    {
        printf("Cadastro feito com sucesso..\n");
        system("pause");
    }

    arq = fopen("dados.dat", "ab+");
    if(arq == NULL)
    {
        printf("Erro ao abrir o arquivo...\n");
        system("pause");
    }
    else
    {
        fwrite(&user, sizeof(user), 1, arq);
    }
    fclose(arq);

}


#endif