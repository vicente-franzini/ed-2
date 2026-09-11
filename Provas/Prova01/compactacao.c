#include <stdio.h>
#include <string.h>
#include "prova.h"

int compactacao(){
    FILE *fptr;
    FILE *temp;
    registro_t reg;

    fptr = fopen("db.bin", "r+b");
    if(fptr == NULL){
        return 0;
    }
    temp = fopen("temp.bin", "w+b");
    if(temp == NULL){
        return 0;
    }
    
    for(;;) {
        fread(&reg.tamanho, sizeof(int32_t), 1, fptr);
        if(reg.tamanho == -1) break;

        long int start = ftell(fptr);
        if(reg.tamanho > 0) {
            fscanf(fptr," %4[^|]s ", reg.codigo);
            fseek(fptr, 1, SEEK_CUR);
            fscanf(fptr, " %60[^|]s", reg.faixa);
            fseek(fptr, 1, SEEK_CUR);
            fscanf(fptr, " %50[^|]s ", reg.artista);
            fseek(fptr, 1, SEEK_CUR);
            fscanf(fptr, " %20[^|]s ", reg.genero);
            fseek(fptr, reg.tamanho - ftell(fptr) + start, SEEK_CUR);
            
            // 8 = 4 (codigo) + 4 (pipis)
            reg.tamanho = 8 + strlen(reg.faixa) + strlen(reg.artista) + strlen(reg.genero);
            fwrite(&reg.tamanho, sizeof(int32_t), 1, temp);
            fprintf(temp, "%s|%s|%s|%s|", reg.codigo, reg.faixa, reg.artista, reg.genero);
        } else {
            fseek(fptr, -reg.tamanho, SEEK_CUR);
        }
    }
    
    fclose(fptr);
    fseek(temp, 0, SEEK_SET);
    fptr = fopen("db.bin", "wb");
    if(fptr == NULL){
        return 0;
    }

    char c = '\0';
    while((c = getc(temp)) != EOF)
        putc(c, fptr);

    reg.tamanho = -1;
    fwrite(&reg.tamanho, sizeof(int32_t), 1, fptr);

    fclose(temp);
    fclose(fptr);
    if(!remove("temp.bin")){
        return 0;
    }

    return 1;
}