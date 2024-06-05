#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct alunos
{
    int cod;
    char nome[50];
    float nota1;
    float nota2;
    float media;
};
struct alunos aluno;

void ExcluirNotas(FILE *arq)
{
    bool achou;
    char nome[40];
    FILE *temp;
    arq = fopen("alunos.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (arq == NULL || temp == NULL)
    {
        printf("Nao foi possivel abrir o arquivo...\n");
        system("pause");
    }
    else
    {
        achou = false;
        printf("[03] - EXCLUIR ALUNOS...\n");

        fflush(stdin);
        printf("Digite o nome de um aluno: ");
        gets(nome);
        fflush(stdin);

        while (fread(&aluno, sizeof(aluno), 1, arq))
        {
            if (strcmp(nome, aluno.nome) == 0)
            {
                achou = true;
            }
            else
            {
                fwrite(&aluno, sizeof(aluno), 1, temp);
            }
        }
        fclose(arq);
        fclose(temp);

        if (achou == true)
        {
            remove("cliente.dat");
            rename("temp.dat", "cliente.dat");
            printf("Aluno encontrado...\n");
            printf("Dados..\n");
            printf("Aluno: %s\n", aluno.nome);
            system("pause");
        }
        else
        {
            remove("temp.dat");
            printf("Nao foi possivel encontrar o aluno..\n");
            system("pause");
        }
    }
}

void MostrarNotas(FILE *arq)
{
    arq = fopen("alunos.dat", "rb");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquvio....\n");
        system("pause");
    }
    else
    {

        printf("                             [02] - MOSTRAR NOTAS                                 \n");
        printf("==================================================================================\n");
        printf("##   COD_ALUNO  ##      NOME       ##   NOTA1   ##   NOTA2    ##  MEDIA FINAL ##  \n");
        printf("==================================================================================\n");

        while (fread(&aluno, sizeof(aluno), 1, arq))
        {
            printf("        %-13d  %-18s  %-12.2f %-8.2f %.2f\n", aluno.cod, aluno.nome, aluno.nota1, aluno.nota2, aluno.media);
        }
    }
    fclose(arq);
    system("pause");
}

void CadastrarNotas(FILE *arq)
{
    char resp = 'S';
    bool achou;
    int cod_aluno;

    arq = fopen("alunos.dat", "ab+");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo...\n");
        system("pause");
    }
    else
    {
        printf("[01] - CADASTRAR NOTAS\n");

        while (resp == 'S')
        {
            do
            {
                achou = false;
                printf("Digite o codigo do aluno: ");
                scanf("%d", &cod_aluno);
                fflush(stdin);

                fseek(arq, 0, SEEK_SET);

                while (fread(&aluno, sizeof(aluno), 1, arq))
                {
                    if (cod_aluno == aluno.cod)
                    {
                        achou = true;
                        break;
                    }
                }
                if (achou == true)
                {
                    printf("O codigo informado ja existe no sistema...\n");
                    system("pause");
                }

            } while (achou == true);

            aluno.cod = cod_aluno;

            printf("Digite o nome: ", aluno.cod);
            gets(aluno.nome);
            fflush(stdin);

            printf("Digite a nota 1: ");
            scanf("%f", &aluno.nota1);

            printf("Digite a nota 2: ");
            scanf("%f", &aluno.nota2);

            aluno.media = (aluno.nota1 + aluno.nota2) / 2;

            fwrite(&aluno, sizeof(aluno), 1, arq);

            printf("Deseja continuar s/n?: ");
            scanf(" %c", &resp);
            resp = toupper(resp);
            fflush(stdin);
        }
    }

    fclose(arq);
}

int main(void)
{
    FILE *arq;
    int op;
    do
    {
        system("cls");
        printf("*********** MENU DE OPCOES ***********\n");
        printf("        [01] - CADASTRAR NOTAS        \n");
        printf("        [02] - MOSTRAR NOTAS          \n");
        printf("        [03] - EXCLUIR NOTAS          \n");
        printf("        [04] - SAIR                   \n");
        printf("**************************************\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            CadastrarNotas(arq);
            break;
        case 2:
            MostrarNotas(arq);
            break;
        case 3:
            ExcluirNotas(arq);
            break;
        case 4:
            break;
        default:
            printf("Codigo invalido...Tente novamente...\n");
            system("pause");
            break;
        }

    } while (op != 3);

    return 0;
}