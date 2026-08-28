#include <stdio.h>
#include <err.h>

#include "exercicio.h"

int main(void) {
    // Assegura que os arquivos essenciais existem
    FILE *clientes = fopen("clientes.bin", "a");
    FILE *temp     = fopen("temp.bin", "a");
    if(clientes == NULL || temp == NULL) {
        err(1, "Arquivos essenciais não puderam ser criados.");
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
                insercao();
                break;
            case 2:
                remocao();
                break;
            case 3:
                atualizacao();
                break;
            case 4:
                busca();
                break;
        }
    }

    return 0;
}