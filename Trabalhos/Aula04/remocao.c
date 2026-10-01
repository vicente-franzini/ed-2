#include <stdio.h>
#include <string.h>

#include "exercicio.h"

void remocao() {
    FILE *db = fopen("db.bin", "r+b");
    if(db == NULL) {
        printf("Houve um erro na abertura do arquivo.\n\n");
        return;
    }

    // Obtém todas as informações do cliente, para armazenar no arquivo.
    char codigo[4];

    printf("Insira o código do segurado (APENAS 3 CARACTERES)\n> ");
    scanf(" %3s", &codigo);

    fseek(db, 0, SEEK_SET);
    int32_t head_atual = 0;
    char cod_atual[4];
    while(1) {
        fread(&head_atual, sizeof(int32_t), 1, db);
        if(head_atual == -1) break;

        fscanf(db, "%3[^#]s", &cod_atual);

        if(strcmp(codigo, cod_atual) == 0) {
            fseek(db, -7, SEEK_CUR);
            head_atual = -head_atual;
            fwrite(&head_atual, sizeof(int32_t), 1, db);
            fclose(db);

            printf("Registro removido com sucesso!\n\n");
            return;
        }

        fseek(db, head_atual - 3, SEEK_CUR);
    }

    printf("O registro não foi encontrado.\n\n");

    fclose(db);

}