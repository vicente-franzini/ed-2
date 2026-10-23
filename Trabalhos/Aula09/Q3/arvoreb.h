#pragma once
#ifndef ARVORE_B_H
#define ARVORE_B_H

#include <stddef.h>

typedef int chave_t;

const unsigned int ORDEM_ARVORE = 3;

typedef struct _pagina_t {

    // Quantas chaves tem na página
    size_t contador;

    // Vetor de chaves na página
    chave_t chaves[ORDEM_ARVORE - 1];

    // Vetor de filhos da página. NULL indica que não tem filho na posição
    // É possível verificar se a página é folha se filhos[0] == NULL
    struct _pagina_t *filhos[ORDEM_ARVORE];

    // Ponteiro para a página pai. NULL indica que é a página raiz
    struct _pagina_t *pai;
} pagina_t;

typedef struct _arvoreB_t {
    pagina_t *raiz;
} arvoreB_t;

// Inicializa uma árvore B e retorna
arvoreB_t *inicializarArvoreB();

// Retorna um ponteiro a uma chave na árvore, e retorna
// NULL caso não ache
chave_t *buscarChave(arvoreB_t *arvoreB);

// Insere uma chave na árvore B.
int inserirChave(arvoreB_t *arvoreB, chave_t chave);

// Remove uma chave na árvore B.
int removerChave(arvoreB_t *arvoreB, chave_t chave);

#endif