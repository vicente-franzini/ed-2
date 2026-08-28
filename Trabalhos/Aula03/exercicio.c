#include <stdio.h>
#include <err.h>

#include "exercicio.h"

int main(void) {
    arquivos_t arquivos = {0};

    arquivos.cli = fopen("clientes.bin", "a+b");
    arquivos.tmp = fopen("temp.bin", "a+b");
    if(arquivos.cli == NULL || arquivos.tmp == NULL) {
        err(1, "Erro na abertura de arquivos");
    }

    int opcao = -1;
    while(opcao != 0) {
        printf(
            "Escolha sua opção:\n"
            " (0) Sair\n"
            " (1) Inserção\n"
            " (2) Remoção\n"
            " (3) Atualização\n"
            " (4) Busca\n"
            " (5) Merge\n\n"
            "> "
        );

        scanf(" %d", &opcao);
        switch(opcao) {
            default:
                printf("Opção inválida!\n");
                break;
            case 0: break;
            case 1:
                insercao(&arquivos);
                break;
        }
    }

    return 0;
}