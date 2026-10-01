#include <stdio.h>
#include <string.h>

#include "exercicio.h"

void insercao() {
    FILE *db = fopen("db.bin", "r+b");
    if(db == NULL) {
        printf("Houve um erro na abertura do arquivo.\n\n");
        return;
    }

    // Obtém todas as informações do cliente, para armazenar no arquivo.
    registro_t registro = {0};

    printf("Insira o código do segurado (APENAS 3 CARACTERES)\n> ");
    scanf(" %3s", &registro.codigo);

    printf("\nInsira o Nome do segurado\n> ");
    scanf(" %50[^\n]s", &registro.nome);

    printf("\nInsira o Nome da Seguradora\n> ");
    scanf(" %50[^\n]s", &registro.seguradora);

    printf("\nInsira o Tipo do seguro\n> ");
    scanf(" %30[^\n]s", &registro.tipo);

    registro.tamanho += strlen(registro.nome);
    registro.tamanho += strlen(registro.seguradora);
    registro.tamanho += strlen(registro.tipo);
    
    // cdg segurado + separadores
    registro.tamanho += 7;

    fseek(db, 0, SEEK_SET);
    int32_t head_atual = 0;
    while(1) {
        fread(&head_atual, sizeof(int32_t), 1, db);
        if(head_atual == -1) {
            fseek(db, -4, SEEK_CUR);
            fwrite(&registro.tamanho, sizeof(int32_t), 1, db);
            fprintf(
                db, "%s#%s#%s#%s#",
                registro.codigo, registro.nome,
                registro.seguradora, registro.tipo
            );
            fwrite(&head_atual, sizeof(int32_t), 1, db);

            break;
        } else if(head_atual < 0 && -head_atual >= registro.tamanho) {
            head_atual = -head_atual;
            fseek(db, -4, SEEK_CUR);
            fwrite(&head_atual, sizeof(int32_t), 1, db);
            fprintf(
                db, "%s#%s#%s#%s#",
                registro.codigo, registro.nome,
                registro.seguradora, registro.tipo
            );

            break;
        } else if(head_atual > 0) {
            fseek(db, head_atual, SEEK_CUR);
        } else {
            fseek(db, -head_atual, SEEK_CUR);
        }

    }

    fclose(db);

}