#pragma once
#ifndef EXERCICIO_H
#define EXERCICIO_H

#include <stdio.h>
#define STR_SIZE 128
#define STR_SIZE_S "127"

typedef struct arquivos {
    FILE *cli, *tmp, *imp;
} arquivos_t;

typedef struct registro {
    long long cpf;
    char nome[STR_SIZE];
    char sobrenome[STR_SIZE];
    char telefone[STR_SIZE];
    char cidade[STR_SIZE];
} registro_t;

void insercao(arquivos_t *arquivos);

#endif