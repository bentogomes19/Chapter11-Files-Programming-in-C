#ifndef REGISTROS_H
#define REGISTROS_H

#include <stdbool.h>

struct estilistas // Registro do ESTILISTA
{
    int codigoEstilista; // CÓDIGO DO ESTILISTA
    char nome[40];       // NOME DO ESTILISTA
    float salario;       // SALARIO DO ESTILISTA
};

struct roupas // Registro das ROUPAS
{
    int codigoR;         // CÓDIGO DA ROUPA
    char descri[50];     // DESCRIÇÃO DA ROUPA (SAIA, BERMUDA, TOP, SUTIÃ)
    int codigoEstilista; // CÓDIGO DO ESTILISTA
    int codigoEstacao;   // CÓDIGO DA ESTAÇÃO
    int ano;             // ANO -> 2012, 2024...
};

struct estacao // Registro da ESTAÇÃO
{
    int codigoEstacao; // CODIGO DA ESTAÇÃO
    char nome[40];     // NOME DA ESTAÇÃO --> PRIMAVERA-VERÃO, OUTONO-INVERNO
};

struct estilistas estilista;
struct roupas roupa;
struct estacao estacao;


bool achou; // variável para fazer validações, verificar se o codigo do usuario é igual ao que existe no registro

#endif