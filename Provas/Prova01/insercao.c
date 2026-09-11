#include <stdio.h>
#include <string.h>

#include "prova.h"

int insercao() {
    registro_t reg = {0};

    printf("Insira o código da faixa (APENAS 4 CARACTERES)\n> ");
    scanf(" %4s", &reg.codigo);

    printf("\nInsira o Nome da faixa\n> ");
    scanf(" %60[^\n]s", &reg.faixa);

    printf("\nInsira o Nome do Artista\n> ");
    scanf(" %50[^\n]s", &reg.artista);

    printf("\nInsira o Gênero da faixa\n> ");
    scanf(" %20[^\n]s", &reg.genero);

    reg.tamanho = 8;
    reg.tamanho += strlen(reg.faixa);
    reg.tamanho += strlen(reg.artista);
    reg.tamanho += strlen(reg.genero);

    return insercao_r(&reg);
}

int insercao_r(registro_t *reg) {
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
        if(strcmp(cod_atual, reg->codigo) == 0) {
            printf("Um registro com esse código já existe!\n\n");
            fclose(db);
            return -1;
        }

        fseek(db, tam_atual - 4, SEEK_CUR);
    }
    fseek(db, 0, SEEK_SET);

    int32_t diff = INT32_MAX, diff_i = -1, diff_t = reg->tamanho;
    for(;;) {
        fread(&tam_atual, sizeof(int32_t), 1, db);
        if(tam_atual == -1) break;
        if(tam_atual >= 0) {
            fseek(db, tam_atual, SEEK_CUR);
            continue;
        }

        tam_atual = -tam_atual;
        if(
            tam_atual >= reg->tamanho && 
            tam_atual - reg->tamanho < diff
        ) {
            diff = tam_atual - reg->tamanho;
            diff_i = ftell(db);
            diff_t = tam_atual;
        }

        fseek(db, tam_atual, SEEK_CUR);
    }

    if(diff_i != -1)
        fseek(db, diff_i - 4, SEEK_SET);
    else
        fseek(db, - 4, SEEK_CUR);
    
    fwrite(&diff_t, sizeof(int32_t), 1, db);
    fprintf(
        db, "%s|%s|%s|%s|",
        reg->codigo, reg->faixa, reg->artista, reg->genero
    );

    if(diff_i == -1) fwrite(&diff_i, sizeof(int32_t), 1, db);
    fclose(db);

    printf("Registro inserido com sucesso!\n\n");
}