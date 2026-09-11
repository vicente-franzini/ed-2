#include <stdio.h>
#include <string.h>

#include "prova.h"

int dump() {
    FILE *f;
    int32_t tam;
    char codigoF[5], faixaF[61], artistaF[51], generoF[21];

    int registroTotal = 0, registroDeletados = 0, fragmentacaoInt = 0, fit = 0;
    int fragmentacaoExt = 0;

    if (!(f = fopen("db.bin", "r+b")))
    {
        printf("ERRO: Não foi possível abrir o arquivo.");
        return 1;
    }
    else
    {
        fread(&tam, sizeof(int32_t), 1, f);
        while (tam != -1)
        {
            if(tam < 0) {
                fseek(f, -tam, SEEK_CUR);
                fragmentacaoExt += (-tam);
                registroDeletados++;
                goto jump;
            }

            long int start = ftell(f);

            fscanf(f, " %5[^|]s ", codigoF);
            fseek(f, 1, SEEK_CUR);
            fscanf(f, " %60[^|]s", faixaF);
            fseek(f, 1, SEEK_CUR);
            fscanf(f, " %50[^|]s ", artistaF);
            fseek(f, 1, SEEK_CUR);
            fscanf(f, " %20[^|]s ", generoF);
            fseek(f, 1, SEEK_CUR);

            long int end = ftell(f);

            printf("%s|%s|%s|%s\n", codigoF, faixaF, artistaF, generoF);

            fragmentacaoInt = (tam - (end - start));
            fit += fragmentacaoInt;

            fseek(f, fragmentacaoInt, SEEK_CUR);

            jump:
            registroTotal++;
            fread(&tam, sizeof(int32_t), 1, f);
        }
    }

    printf(
        "\n"
        "Total de registros: %d (Deletados: %d)\n"
        "Fragmentação externa: %d\n"
        "Fragmentação interna: %d\n"
        "Fragmentação total:   %d\n\n",
        registroTotal, registroDeletados,
        fragmentacaoExt, fit, fit + fragmentacaoExt);

    return 0;
}