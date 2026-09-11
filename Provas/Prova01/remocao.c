#include <stdio.h>
#include <string.h>

#include "prova.h"

int remocao() {
    char codigo[5];
    printf("Insira o código do registro a ser deletado:\n> ");
    scanf(" %4s", &codigo);

    return remocao_c(codigo);
}

int remocao_c(char *codigo) {
    FILE *db = fopen("db.bin", "r+b");
    if(db == NULL)
        return -1;

    int32_t tam_atual;
    char cod_atual[5];
    for(;;) {
        fread(&tam_atual, sizeof(int32_t), 1, db);
        if(tam_atual == -1) break;
        if(tam_atual < 0) {
            fseek(db, -tam_atual, SEEK_CUR);
            continue;
        }

        fscanf(db, "%4[^|]s", cod_atual);
        if(strcmp(cod_atual, codigo) != 0) {
            fseek(db, tam_atual - 4, SEEK_CUR);
            continue;
        }

        fseek(db, -8, SEEK_CUR);
        tam_atual = -tam_atual;
        fwrite(&tam_atual, sizeof(int32_t), 1, db);
        break;
    }

    if(tam_atual == -1) {
        printf("Um registro com esse código não foi encontrado.\n\n");
        fclose(db);
        return -13;
    } else {
        printf("Registro deletado com sucesso!\n\n");
    }

    fclose(db);

    return 0;
}