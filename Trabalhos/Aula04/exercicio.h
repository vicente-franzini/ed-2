#pragma once
#ifndef EXERCICIO_H
#define EXERCICIO_H

#include <stdint.h>

typedef struct registro {
    int32_t tamanho;
    char codigo[4];
    char nome[51];
    char seguradora[51];
    char tipo[31];
} registro_t;

void insercao();
void remocao();
void compactacao();
void dump();

#endif