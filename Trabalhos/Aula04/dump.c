#include <err.h>
#include <stdio.h>
#include <string.h>

#include "exercicio.h"

void dump() {
    FILE *db = fopen("db.bin", "r+b");
    if(db == NULL) {
        printf("Houve um erro na abertura do arquivo.\n\n");
        return;
    }

    fseek(db, 0, SEEK_END);
    long tamanho = ftell(db);
    fseek(db, 0, SEEK_SET);

    int32_t tamanho_reg, frag_int = 0, frag_ext = 0;
    int registros = 0, reg_deletados = 0;
    char buf[51];
    for(;;) {
        fread(&tamanho_reg, sizeof(int32_t), 1, db);

        if(tamanho_reg == -1 || ferror(db) || feof(db)) break;
        if(tamanho_reg < 0) {
            frag_ext -= tamanho_reg;
            frag_ext += 4;
            registros++;
            reg_deletados++;
            fseek(db, -tamanho_reg, SEEK_CUR);
            continue;
        }

        long ini = ftell(db);
        fscanf(db, "%3[^#]s", buf);
        printf("(Cliente %s)\n", buf);
        fseek(db, 1, SEEK_CUR);

        fscanf(db, "%50[^#]s", buf);
        printf("  Nome: %s\n", buf);
        fseek(db, 1, SEEK_CUR);

        fscanf(db, "%50[^#]s", buf);
        printf("  Seguradora: %s\n", buf);
        fseek(db, 1, SEEK_CUR);

        fscanf(db, "%30[^#]s", buf);
        printf("  Tipo: %s\n\n", buf);
        fseek(db, 1, SEEK_CUR);

        frag_int += tamanho_reg - (ftell(db) - ini);
        fseek(db, tamanho_reg - (ftell(db) - ini), SEEK_CUR);
        registros++;
    }

    printf(
        "Registros: %d (%d deletados)\n"
        "Fragmentação\n"
        "   Interna: %d bytes\n"
        "   Externa: %d bytes\n"
        "   Total:   %d bytes\n\n",
        registros, reg_deletados, frag_int,
        frag_ext, frag_int + frag_ext
    );

}