#include <stdio.h>
#include <err.h>

#include "exercicio.h"

int main(void) {
    // Abrir arquivos no modo "append" garante que caso eles não existam,
    // eles sejam criados. E, caso eles existam, não apaguem eles.
    FILE *clientes = fopen("clientes.bin", "a");
    FILE *temp     = fopen("temp.bin", "a");
    if(clientes == NULL || temp == NULL) {
        err(1, "Arquivos essenciais não puderam ser criados.");
    }

    // Menu básico, chama as funções devidas, definidas em "exercicio.h"
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
            case 5:
                merge();
                break;
        }
    }

    return 0;
}