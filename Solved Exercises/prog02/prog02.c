#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

struct clientes
{
    int cod_cliente;
    char nome[30];
    char endereco[30];
    char telefone[14];
};
struct clientes cliente;

struct recebimentos
{
    int num_doc;
    float valor_doc;
    char data_emissao[10];
    char data_vencimento[10];
    int cod_cliente;
};
struct recebimentos recebi;

void AlterarRecebimentos()
{
    bool achou;
    int cod_cliente, num_doc;
    FILE *arq1, *arq2;
    arq1 = fopen("recebimentos.dat", "rb+");
    arq2 = fopen("clientes.dat", "rb+");
    if (arq1 == NULL || arq2 == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        system("pause");
    }
    else
    {
        printf("[07] - ALTERAR RECEBIMENTOS\n");
        achou = false;
        printf("Digite o codigo do cliente: ");
        scanf("%d", &cod_cliente);

        while (fread(&cliente, sizeof(cliente), 1, arq2)) // BUSCANDO CLIENTES
        {
            achou = true;
            break;
        }
        if (achou)
        {
            achou = false;
            printf("Cliente encontrado...\n\n");
            printf("Digite o numero do documento: ");
            scanf("%d", &num_doc);

            while (fread(&recebi, sizeof(recebi), 1, arq1)) // BUSCANDO RECEBIMENTOS
            {
                if (cod_cliente == recebi.cod_cliente && num_doc == recebi.num_doc)
                {
                    achou = true;
                    break;
                }
            }
            if (achou)
            {
                printf("Documento encontrado...\n");
                printf("Documento numero: %d\n", recebi.num_doc);
                printf("Valor R$: R$ %.2f\n", recebi.valor_doc);
                printf("Data emissao: %s\n", recebi.data_emissao);
                printf("Documento numero: %s \n", recebi.data_vencimento);
                system("pause");
            }
            else
            {
                printf("Nao foi possivel encontrar o recebimento...\n");
                system("pause");
            }
        }
        else
        {
            printf("Nao foi possivel encontrar um cliente com esse codigo...\n");
            system("pause");
        }

        fclose(arq1);
        fclose(arq2);
    }
}

void AlterarClientes()
{
    bool achou;
    int cod_cliente, c;
    FILE *arq;

    arq = fopen("clientes.dat", "rb+");
    if (arq == NULL)
    {
        printf("Erro ao ler o arquivo.\n");
        system("pause");
    }
    else
    {
        printf("[06] - ALTERAR DADOS DO CLIENTE.\n");

        printf("Digite o codigo do cliente: ");
        scanf("%d", &cod_cliente);
        while ((c = getchar()) != '\n' && c != EOF)
            ; // Limpa o buffer de entrada

        achou == false;

        while (fread(&cliente, sizeof(cliente), 1, arq))
        {
            if (cod_cliente == cliente.cod_cliente)
            {
                achou = true;
                break;
            }
        }
        if (achou)
        {
            printf("Cliente: %s\n", cliente.nome);
            printf("Endereco: %s\n", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            system("pause");

            printf("Digite o nome do cliente: ");
            fgets(cliente.nome, 30, stdin);
            cliente.nome[strcspn(cliente.nome, "\n")] = '\0'; // remove o caracter \n "quebra de linha"

            printf("Digite o novo endereco: ");
            fgets(cliente.endereco, 30, stdin);
            cliente.endereco[strcspn(cliente.endereco, "\n")] = '\0';

            printf("Digite o novo telefone: ");
            fgets(cliente.telefone, 14, stdin);
            cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0';

            fseek(arq, -sizeof(cliente), SEEK_CUR); // fseek(variavel logica do arquivo, )
            fwrite(&cliente, sizeof(cliente), 1, arq);

            printf("Dados alterados com sucesso.\n");
            Sleep(1000);
        }
        else
        {
            printf("Cliente nao encontrado.\n");
            system("pause");
        }

        fclose(arq);
    }
}

void ExcluirClientes()
{
    int cod_cliente;
    bool achou;
    FILE *arq1, *arq2, *temp1, *temp2;

    arq1 = fopen("clientes.dat", "rb");
    temp1 = fopen("temp1.dat", "wb");

    printf("\n[05] - EXCLUIR CLIENTES\n");

    achou = false;

    printf("Digite o codigo do cliente: ");
    scanf("%d", &cod_cliente);

    while (fread(&cliente, sizeof(cliente), 1, arq1))
    {
        if (cod_cliente == cliente.cod_cliente)
        {
            achou = true;
        }
        else
        {
            fwrite(&cliente, sizeof(cliente), 1, temp1);
        }
    }

    fclose(arq1);
    fclose(temp1);

    if (achou == true)
    {
        remove("clientes.dat");
        rename("temp1.dat", "clientes.dat");
        printf("Cliente Excluido com sucesso..\n");
        system("pause");

        achou = false;

        arq2 = fopen("recebimentos.dat", "rb");
        temp2 = fopen("temp2.dat", "wb");

        while (fread(&recebi, sizeof(recebi), 1, arq2))
        {
            if (cod_cliente == recebi.cod_cliente)
            {
                achou = true;
            }
            else
            {
                fwrite(&recebi, sizeof(recebi), 1, temp2);
            }
        }

        fclose(arq2);
        fclose(temp2);

        if (achou == true)
        {
            remove("recebimentos.dat");
            rename("temp2.dat", "recebimentos.dat");
            printf("Recebimentos Excluidos com sucesso.\n");
            system("pause");
        }
        else
        {
            remove("temp2.dat");
            printf("O cliente nao possui recebimentos.\n");
            system("pause");
        }
    }
    else
    {
        printf("Nao foi possivel encontrar o cliente.\n");
        system("pause");
    }
}

void MostrarRecebimentos()
{
    FILE *arq;

    arq = fopen("recebimentos.dat", "rb+");
    if (arq == NULL)
    {
        printf("Nao e possivel abrir o arquvio..\n");
        system("cls");
    }
    else
    {
        printf("****************** BANCO NACIONAL - RECEBIMENTOS ******************\n");
        printf("                          RECEBIMENTOS                             \n");
        printf("=================================================================================================================\n");
        printf(" ##  DOCUMENTO   ##      VALOR (R$)    ##     DATA EMISSAO     ##    DATA VENCIMENTO     ##   CLIENTE      ##    \n");
        printf("=================================================================================================================\n");

        while (fread(&recebi, sizeof(recebi), 1, arq))
        {
            printf("       %-20d  %-16.2f   %-23s  %-21s  %d\n", recebi.num_doc, recebi.valor_doc, recebi.data_emissao, recebi.data_vencimento, recebi.cod_cliente);
        }

        fclose(arq);
        system("pause");
    }
}

void IncluirRecebimentos()
{
    FILE *arq, *arq2;

    arq = fopen("recebimentos.dat", "ab+");
    arq2 = fopen("clientes.dat", "rb+");
    if (arq == NULL || arq2 == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        system("pause");
    }
    else
    {
        int num_doc;
        int cod_cliente;
        char resp = 'S';
        bool achou;

        printf("[03] - INCLUIR RECEBIMENTOS\n");

        while (resp == 'S')
        {
            do
            {    
                achou = false;
                printf("Digite o codigo do cliente: ");
                scanf("%d", &cod_cliente);
                
                rewind(arq2);

                while (fread(&cliente, sizeof(cliente), 1, arq2))
                {
                    if (cod_cliente == cliente.cod_cliente)
                    {
                        achou = true;
                        break;
                    }
                }
                if (achou == false)
                {
                    printf("Cliente nao encontrado. Consulte o item 2 para ver os clientes cadastrados.\n");
                    system("pause");
                    break;
                }
            } while (achou == false);

            do
            {
                achou = false;
                printf("Digite o numero do documento: ");
                scanf(" %d", &num_doc);
                
                fseek(arq, 0, SEEK_SET);

                while (fread(&recebi, sizeof(recebi), 1, arq))
                {
                    if (num_doc == recebi.num_doc)
                    {
                        achou = true;
                        break;
                    }
                }
                if (achou == true)
                {
                    printf(" O codigo informado ja existe no sistema... Tente novamente\n");
                    system("pause");
                }
            } while (achou == true);
            recebi.num_doc = num_doc;
            recebi.cod_cliente = cod_cliente;

            printf("Cod # %d -> Digite o valor do documento R$: ", recebi.cod_cliente);
            scanf("%f", &recebi.valor_doc);
            fflush(stdin);

            printf("Cod # %d -> Digite a data da emissao: ", recebi.cod_cliente);
            fgets(recebi.data_emissao, 10, stdin);
            recebi.data_emissao[strcspn(recebi.data_emissao, "\n")] = '\0';

            printf("Cod # %d -> Digite a data da vencimento: ", recebi.cod_cliente);
            fgets(recebi.data_vencimento, 10, stdin);
            recebi.data_vencimento[strcspn(recebi.data_vencimento, "\n")] = '\0';

            fwrite(&recebi, sizeof(recebi), 1, arq);
            
            printf("Deseja continuar [s] [n]: ");
            scanf(" %c", &resp);
            resp = toupper(resp);
            fflush(stdin);

            if (resp == 'N')
            {
                break;
            }
        }

        fclose(arq);
        fclose(arq2);
    }
}

void MostrarClientes()
{
    FILE *arq;
    arq = fopen("clientes.dat", "rb");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        system("pause");
    }
    else
    {
        printf("[02] - MOSTRAR CLIENTES\n");
        printf("=====================================================================================\n");
        printf(" ##  CODIGO   ##      NOME      ##        ENDERECO        ##       TELEFONE       ## \n");
        printf("=====================================================================================\n");

        while (fread(&cliente, sizeof(cliente), 1, arq))
        {
            printf("       %-12d  %-18s  %-25s %s \n", cliente.cod_cliente, cliente.nome, cliente.endereco, cliente.telefone);
        }

        fclose(arq);
        system("pause");
    }
}

void CadastrarClientes()
{
    FILE *arq;

    arq = fopen("clientes.dat", "ab+");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        system("pause");
    }
    else
    {
        int c;
        int cod_cliente;
        bool achou;
        char resp = 'S';

        printf("[01] - CADASTROS CLIENTES\n\n");

        while (resp == 'S')
        {
            do
            {
                achou = false;
                printf("Digite o codigo do cliente: ");
                scanf(" %d", &cod_cliente);
                while ((c = getchar()) != '\n' && c != EOF)
                    ;

                fseek(arq, 0, SEEK_SET);

                while (fread(&cliente, sizeof(cliente), 1, arq))
                {
                    if (cod_cliente == cliente.cod_cliente) // NAO PODE EXISTIR CLIENTES COM O MESMO CODIGO
                    {
                        achou = true;
                        break;
                    }
                }
                if (achou)
                {
                    printf("Cliente com codigo ja cadastrado...Tente novamente.\n");
                }

            } while (achou == true);
            cliente.cod_cliente = cod_cliente;

            printf("Cliente #%d -> Digite o nome: ", cliente.cod_cliente);
            fgets(cliente.nome, 30, stdin);
            cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

            printf("Cliente #%d -> Digite o endereco: ", cliente.cod_cliente);
            fgets(cliente.endereco, 30, stdin);
            cliente.endereco[strcspn(cliente.endereco, "\n")] = '\0';

            printf("Cliente #%d -> Digite o telefone: ", cliente.cod_cliente);
            fgets(cliente.telefone, 14, stdin);
            cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0';

            fwrite(&cliente, sizeof(cliente), 1, arq);

            printf("Deseja continuar [s] [n]?: ");
            resp = getchar();
            resp = toupper(resp);
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            if (resp == 'N')
            {
                system("cls");
                break;
            }
        }

        fclose(arq);
    }
}

int main(void)
{
    int op;

    do
    {
        system("cls");
        printf("****************** BANCO NACIONAL - RECEBIMENTOS ******************\n");
        printf("                          MENU PRINCIPAL                           \n");
        printf("                   [01] - CADASTROS CLIENTES                       \n");
        printf("                   [02] - MOSTRAR CLIENTES                         \n");
        printf("                   [03] - INCLUIR RECEBIMENTOS                     \n");
        printf("                   [04] - MOSTRAR RECEBIMENTOS                     \n");
        printf("                   [05] - EXCLUIR CLIENTES                         \n");
        printf("                   [06] - ALTERAR CLIENTES                         \n");
        printf("                   [07] - ALTERAR RECEBIMENTOS                     \n");
        printf("                   [08] - SAIR                                     \n");
        printf("++++++++++++++++++++++++ ESCOLHA UMA OPCAO ++++++++++++++++++++++++\n");
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            CadastrarClientes();
            break;
        case 2:
            MostrarClientes();
            break;
        case 3:
            IncluirRecebimentos();
            break;
        case 4:
            MostrarRecebimentos();
            break;
        case 5:
            ExcluirClientes();
            break;
        case 6:
            AlterarClientes();
            break;
        case 7:
            AlterarRecebimentos();
            break;
        case 8:
            break;

        default:
            printf("Codigo invalido...Tente novamente..\n");
            system("pause");
            break;
        }

    } while (op != 8);

    return 0;
}