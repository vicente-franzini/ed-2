#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exercicio.h"

void compactacao() {
    FILE *db = fopen("db.bin", "r+b");
    FILE *tmp = fopen("temp.bin", "w+b");
    if(db == NULL || tmp == NULL) {
        if(db != NULL) fclose(db);
        if(tmp != NULL) fclose(tmp);
        printf("Houve um erro na abertura do arquivo.\n\n");
        return;
    }

    fseek(db, 0, SEEK_END);
    long t_orig = ftell(db);

    fseek(db, 0, SEEK_SET);

    int32_t cod_atual = 0;
    registro_t reg;
    while(1) {
        fread(&cod_atual, sizeof(int32_t), 1, db);
        if(cod_atual == -1 || feof(db) || ferror(db)) break;
        if(cod_atual < 0) {
            fseek(db, -cod_atual, SEEK_CUR);
            continue;
        }

        long s = ftell(db);

        fscanf(db, "%3[^#]s", reg.codigo);
        fseek(db, 1, SEEK_CUR);

        fscanf(db, "%50[^#]s", reg.nome);
        fseek(db, 1, SEEK_CUR);

        fscanf(db, "%50[^#]s", reg.seguradora);
        fseek(db, 1, SEEK_CUR);

        fscanf(db, "%30[^#]s", reg.tipo);

        long e = ftell(db);
        fseek(db, cod_atual - (ftell(db) - s), SEEK_CUR);

        cod_atual = e - s + 1;

        fwrite(&cod_atual, sizeof(int32_t), 1, tmp);
        fprintf(
            tmp, "%s#%s#%s#%s#",
            reg.codigo, reg.nome, reg.seguradora, reg.tipo
        );

    }
    int x = 0x18;

    cod_atual = -1;
    fwrite(&cod_atual, sizeof(int32_t), 1, tmp);

    fclose(db);
    fclose(tmp);

    db = fopen("db.bin", "wb");
    tmp = fopen("temp.bin", "rb");

    if(db == NULL || tmp == NULL) exit(-1);

    char c = '\0';
    while((c = getc(tmp)) != EOF)
        putc(c, db);

    printf("Arquivo compactado! Tamanho reduzido em %d bytes.\n\n", t_orig - ftell(db));

    fclose(db);
    fclose(tmp);

}