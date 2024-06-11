#ifndef BANCODEDADOS_H
#define BANCODEDADOS_H

// REGISTRO PRODUTOS
struct produtos
{
    int cod_produto;       // CODIGO DO PRODUTO
    char nome_produto[60]; // NOME DO PRODUTO
    float valor;           // VALOR DO PRODUTO
    int qtd_estoque;       // QUANTIDADE EM ESTOQUE
    char categoria[50];    // CATEGORIA DO PRODUTO
};
struct produtos produto;

// REGISTRO CLIENTES
struct Clientes
{
    int cod_cliente;   // CODIGO DO CLIENTE
    char nome_cli[50]; // NOME DO CLIENTE
    char telefone[20]; // TELEFONE DO CLIENTE
    int cep;           // ENDEREÇO DO CLIENTE
};
struct Clientes cliente;

// REGISTRO VENDAS
struct Vendas
{
    int cod_NF;         // CODIGO DA NOTA FISCAL
    int cod_cli;        // CODIGO DO CLIENTE
    int cod_produto[8]; // CODIGO DO PRODUTO
    float preco_final;  // PREÇO FINAL = IMPOSTOS + DESCONTOS
    float imposto[8];   // IMPOSTO A SER COBRADO
    float desconto[8];  // DESCONTOS CASO OS PARÂMETROS SEJAM ATINGIDOS
    int qtd_usuario[8]; // QUANTIDADE DE PRODUTOS O CLIENTE DESEJA COMPRAR
};
struct Vendas venda;

int count_produto = 0;

#endif