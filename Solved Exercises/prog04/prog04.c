#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct alunos
{
    int num;
    char nome[40];
    float nota1;
    float nota2;
    float media;
};
struct alunos aluno;

void criar()
{
    FILE *arq;
    arq = fopen("arquivo.dat", "ab");
    if (arq == NULL)
    {
        printf("Nao foi possivel criar o arquivo...\n");
        fclose(arq);
    }
    else
    {

        printf("Arquivo criado com sucesso..\n");
        system("pause");
        fclose(arq);
    }
}

void incluir()
{
    bool achou;
    int numero_aluno;
    char resp = 'S';
    FILE *arq;
    arq = fopen("arquivo.dat", "ab+");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo...\n");
        fclose(arq);
    }
    else
    {
        printf("[02] - INCLUIR\n");

        while (resp == 'S')
        {
            do
            {
                achou = false;
                printf("Digite o numero do aluno: ");
                scanf("%d", &numero_aluno);
                fflush(stdin);

                fseek(arq, 0, SEEK_SET);

                while (fread(&aluno, sizeof(aluno), 1, arq))
                {
                    if (numero_aluno == aluno.num)
                    {
                        achou = true;
                        break;
                    }
                }

                if (achou)
                {
                    printf("Codigo ja cadastrado...\n");
                    system("pause");
                }

            } while (achou == true);

            printf("Digite o seu nome: ");
            gets(aluno.nome);
            fflush(stdin);

            printf("Digite a nota 1: ");
            scanf("%f", &aluno.nota1);

            printf("Digite a nota 2: ");
            scanf("%f", &aluno.nota2);

            aluno.num = numero_aluno;
            aluno.media = (aluno.nota1 + aluno.nota2) / 2;

            fwrite(&aluno, sizeof(aluno), 1, arq);

            printf("Deseja continuar [s][n]?: ");
            scanf(" %c", &resp);
            resp = toupper(resp);
            fflush(stdin);
        }
    }
    fclose(arq);
}

void mostrar()
{
    FILE *arq;

    arq = fopen("arquivo.dat", "rb");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo..\n");
        system("pause");
    }
    else
    {
        printf("[03] - Mostrar...\n");

        printf("====================================================================================\n");
        printf("##     ALUNO     ##     NUM     ##     NOTA1     ##     NOTA2     ##    MEDIA    ## \n");
        printf("====================================================================================\n");

        while (fread(&aluno, sizeof(aluno), 1, arq))
        {
            printf("      %-17s %-15d %-13.2f %-12.2f %.2f\n", aluno.nome, aluno.num, aluno.nota1, aluno.nota2, aluno.media);
        }
    }

    fclose(arq);
    system("pause");
}

int main(void)
{
    int op;
    do
    {
        system("cls");
        printf("*********** MENU DE OPCOES ***********\n");
        printf("*           [01] - Criar             *\n");
        printf("*           [02] - Incluir           *\n");
        printf("*           [03] - Mostrar           *\n");
        printf("*           [04] - Sair              *\n");
        printf("**************************************\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            criar();
            break;
        case 2:
            incluir();
            break;
        case 3:
            mostrar();
            break;
        case 4:
            break;
        default:
            printf("Codigo invalido... Tente novamente...\n");
            system("pause");
            break;
        }

    } while (op != 4);

    return 0;
}