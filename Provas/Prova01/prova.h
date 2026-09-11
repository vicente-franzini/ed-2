#pragma once
#ifndef PROVA_H
#define PROVA_H

#include <stdint.h>

typedef struct registro {
    // Se positivo, registro existe
    // Se negativo, registro foi deletado e tem tamanho
    // "-tamanho"
    // Se -1, final do arquivo
    int32_t tamanho;

    char codigo[5];
    char faixa[61];
    char artista[51];
    char genero[21];
} registro_t;

int insercao();
int insercao_r(registro_t *reg);
int remocao();
int remocao_c(char *codigo);
int compactacao();
int dump();
int carrega_i();
int carrega_r();

#endif