#include <stdio.h>
#include <err.h>

#include "prova.h"

int main() {
    // Abrir arquivos no modo "append" garante que caso eles não existam,
    // eles sejam criados. E, caso eles existam, não apaguem eles.
    FILE *db = fopen("db.bin", "a");
    if(db == NULL) {
        err(1, "Arquivos essenciais não puderam ser criados.");
    }

    fclose(db);
    db = fopen("db.bin", "r+b");
    if(db == NULL) return -1;

    long s = ftell(db);
    fseek(db, 0, SEEK_END);
    if(s == ftell(db)) {
        int32_t h = -1;
        fwrite(&h, sizeof(int32_t), 1, db);
    }
    fclose(db);

    // Menu básico, chama as funções devidas, definidas em "exercicio.h"
    int opcao = -1;
    while(opcao != 0) {
        printf(
            "Escolha sua opção:\n"
            " (0) Sair\n"
            " (1) Inserção\n"
            " (2) Remoção\n"
            " (3) Compactação\n"
            " (4) Dump\n"
            " (5) Carrega (insere)\n"
            " (6) Carrega (remove)\n\n"
            "> "
        );

        scanf(" %d", &opcao);
        int status;
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
                compactacao();
                break;
            case 4:
                dump();
                break;
            case 5:
                carrega_i();
                break;
            case 6:
                carrega_r();
                break;
        }
    }
    
    return 0;
}