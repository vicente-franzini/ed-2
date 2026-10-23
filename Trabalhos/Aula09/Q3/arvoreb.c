#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "arvoreb.h"

arvoreB_t *inicializarArvoreB() {
    pagina_t *raiz = (pagina_t *) calloc(1, sizeof(pagina_t));
    if(raiz == NULL) {
        perror("Erro na alocação da raiz\n");
        return NULL;
    }

    arvoreB_t *arvore = (arvoreB_t *) malloc(sizeof(arvoreB_t));
    if(arvore == NULL) {
        perror("Erro na alocação da árvore B\n");
        free(raiz);
        return NULL;
    }

    arvore->raiz = raiz;

    return arvore;
}

chave_t *buscarChave(arvoreB_t *arvoreB) {

}

int inserirChave(arvoreB_t *arvoreB, chave_t chave) {

}

int removerChave(arvoreB_t *arvoreB, chave_t chave) {

}