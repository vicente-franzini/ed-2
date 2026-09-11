#include <stdio.h>
#include <string.h>

#include "prova.h"

int carrega_i() {
    // tamanho = -1 fim
    // tamanho > 1024 (1024+tam) escrito
    FILE *insere = fopen("insere.bin", "r+b");
    if(insere == NULL) {
        printf("O arquivo \"insere.bin\" não existe!\n");
        return -1;
    }

    registro_t reg = {0};
    int32_t tam_atual;
    for(;;) {
        fread(&tam_atual, sizeof(int32_t), 1, insere);
        if(tam_atual == -1) break;
        if(tam_atual < 0) {
            fseek(insere, -tam_atual, SEEK_CUR);
            continue;
        }

        if(tam_atual >= 1024) {
            fseek(insere, tam_atual - 1024, SEEK_CUR);
            continue;
        }

        fscanf(insere, "%4[^|]s", reg.codigo);
        fseek(insere, 1, SEEK_CUR);

        fscanf(insere, "%60[^|]s", reg.faixa);
        fseek(insere, 1, SEEK_CUR);
        
        fscanf(insere, "%50[^|]s", reg.artista);
        fseek(insere, 1, SEEK_CUR);

        fscanf(insere, "%20[^|]s", reg.genero);
        fseek(insere, 1, SEEK_CUR);
        
        reg.tamanho = 8;
        reg.tamanho += strlen(reg.faixa);
        reg.tamanho += strlen(reg.artista);
        reg.tamanho += strlen(reg.genero);

        printf(
            "Inserir o registro com código %s? (s/n)\n"
            "(faixa %s)\n> ",
            reg.codigo, reg.faixa
        );

        char c = '\0';
        while(c != 's' && c != 'n') {
            scanf(" %c", &c);
        }

        if(c == 's') {
            tam_atual += 1024;            
            insercao_r(&reg);
            fseek(insere, -reg.tamanho - 4, SEEK_CUR);
            fwrite(&tam_atual, sizeof(int32_t), 1, insere);
            fseek(insere, tam_atual - 1024, SEEK_CUR);
            fflush(insere);
        } else {
            fseek(insere, tam_atual - reg.tamanho, SEEK_CUR);
        }
        
    }

    printf("Final do arquivo atingido.\n\n");
    return 0;
}

int carrega_r() {
    FILE *remove = fopen("remove.bin", "r+b");
    if(remove == NULL) {
        printf("O arquivo \"remove.bin\" não existe!\n");
        return -1;
    }

    fseek(remove, 0, SEEK_END);
    long end = ftell(remove);
    fseek(remove, 0, SEEK_SET);

    char codigo[6] = {0};
    while(ftell(remove) != end) {
        fscanf(remove, "%5[^|]s", codigo);
        // codigo[0] == 0 se foi lido e removido
        if(codigo[0] == '0') {
            fseek(remove, 1, SEEK_CUR);
            continue;
        }

        printf(
            "Remover o registro com código %s? (s/n)\n",
            codigo + 1
        );

        char c = '\0';
        while(c != 's' && c != 'n') {
            scanf(" %c", &c);
        }

        if(c == 's') {
            int r = remocao_c(codigo + 1);
            if(r != -13) {
                fseek(remove, -5, SEEK_CUR);
                putc('0', remove);
                fseek(remove, 5, SEEK_CUR);
            }
        } else {
            fseek(remove, 1, SEEK_CUR);
        }
    }

    printf("Final do arquivo atingido.\n\n");
    return 0;
}