#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "exercicio.h"

void insercao(arquivos_t *arquivos) {
    registro_t registro = {0};

    printf("Insira o CPF da pessoa (apenas números)\n> ");
    scanf(" %lld", &registro.cpf);

    printf("\nInsira o Nome da pessoa\n> ");
    scanf(" %"STR_SIZE_S"[^\n]s", &registro.nome);

    printf("\nInsira o Sobrenome da pessoa\n> ");
    scanf(" %"STR_SIZE_S"[^\n]s", &registro.sobrenome);

    printf("\nInsira o Telefone da pessoa\n> ");
    scanf(" %"STR_SIZE_S"[^\n]s", &registro.telefone);

    printf("\nInsira a Cidade da pessoa\n> ");
    scanf(" %"STR_SIZE_S"[^\n]s", &registro.cidade);

    if(arquivos->cli != NULL) fclose(arquivos->cli);
    arquivos->cli = fopen("temp.bin", "rb");
    if(arquivos->tmp != NULL) fclose(arquivos->tmp);
    arquivos->tmp = fopen("temp.bin", "wb");

    long long cpf = 0;
    char buf[STR_SIZE];
    while(feof(arquivos->cli) != 0) {
        fscanf(arquivos->cli, "%lld", &cpf);
        if(cpf >= registro.cpf) break;

        // Escrever CPF
        fprintf(arquivos->tmp, "%lld|", cpf);
        fseek(arquivos->cli, 1, SEEK_CUR);

        // Escrever Nome
        fscanf(arquivos->cli, "%"STR_SIZE_S"[^|]s", &buf);
        fprintf(arquivos->tmp, "%s|", buf);
        fseek(arquivos->cli, 1, SEEK_CUR);

        // Escrever Sobrenome
        fscanf(arquivos->cli, "%"STR_SIZE_S"[^|]s", &buf);
        fprintf(arquivos->tmp, "%s|", buf);
        fseek(arquivos->cli, 1, SEEK_CUR);

        // Escrever Telefone
        fscanf(arquivos->cli, "%"STR_SIZE_S"[^|]s", &buf);
        fprintf(arquivos->tmp, "%s|", buf);
        fseek(arquivos->cli, 1, SEEK_CUR);

        // Escrever Cidade
        fscanf(arquivos->cli, "%"STR_SIZE_S"[^|]s", &buf);
        fprintf(arquivos->tmp, "%s|", buf);
        fseek(arquivos->cli, 1, SEEK_CUR);

        printf("%d\n", ftell(arquivos->cli));
    }

    fprintf(
        arquivos->tmp, "%lld|%s|%s|%s|%s|",
        registro.cpf, registro.nome,
        registro.sobrenome, registro.telefone,
        registro.cidade
    );

    char c = '\0';
    while((c = fgetc(arquivos->cli)) != EOF) 
        fputc(c, arquivos->tmp);

    fclose(arquivos->cli);
    arquivos->cli = fopen("temp.bin", "wb");
    fclose(arquivos->tmp);
    arquivos->tmp = fopen("temp.bin", "rb");

    while((c = fgetc(arquivos->tmp)) != EOF)
        fputc(c, arquivos->cli);

}