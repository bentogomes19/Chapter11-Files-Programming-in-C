#ifndef BANCODEDADOS_H
#define BANCODEDADOS_H

struct Produtos
{
    int cod_produto;       // CODIGO DO PRODUTO (EX- 4432)
    char nome_produto[50]; // NOME DO PRODUTO (EX - MEMORIA RAM 32GB CRUCIAL)
    float preco_produto;   // PRECO DO PRODUTO
    char categoria[40];    // CATEGORIA QUE O PRODUTO PERTENCE EX (MEMORIAS, DISPOSITIVOS DE ARMAZENAMENTO, PERIFERICOS, ACESSORIOS,
                           // PLACAS DE VIDEO, PLACA MAE, PROCESSADOR E UTILITARIOS.)
};

struct NotaFiscal
{
    int cod_NF;            // CODIGO DA NOTA FISCAL
    int cod_produto;       // CODIGO DO PRODUTO
    int cod_cliente;       // CODIGO DO CLIENTE
    float imposto;         // IMPOSTO A SER COBRADO
    float desconto;        // DESCONTO CASO O PRODUTO TENHA VALOR ACIMA DE 350 REAIS 15%
    float preco_final;     // APRESENTAR PRECO FINAL
    char nome_cliente[40]; // APRESENTAR CLIENTE
};

struct Estoque
{
    char categoria[40];    // CATEGORIA QUE O PRODUTO PERTENCE EX (MEMORIAS, DISPOSITIVOS DE ARMAZENAMENTO, PERIFERICOS, ACESSORIOS,
    char nome_produto[50]; // NOME DO PRODUTO
    int cod_produto;       // CODIGO DO PRODUTO
    int qtd_estoque;       // QUANTIDADE DO PRODUTO NO ESTOQUE
};

struct Clientes
{
    int cod_cliente;
    char nome_cliente[40]; // NOME DO CLIENTE
    char telefone[20];     // TELEFONE DO CLIENTE
    char endereco[60];     // ENDERECO DO CLIENTE
};

struct Produtos produto;      // REGISTRO DOS PRODUTOS
struct NotaFiscal notaFiscal; // REGISTRO DAS NOTAS FISCAIS
struct Estoque estoque;       // REGISTRO DO ESTOQUE DA EMPRESA
struct Clientes Cliente;      // REGISTRO DOS CLIENTES CADASTRADOS NO SISTEMA

#endif