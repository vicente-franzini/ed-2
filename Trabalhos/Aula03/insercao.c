#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "exercicio.h"

void insercao() {
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

    FILE *clientes = fopen("clientes.bin", "r+b");
    FILE *temp = fopen("temp.bin", "wb");
    if(clientes == NULL || temp == NULL) {
        err(1, "Houve um erro na abertura dos arquivos");
    }

    int pos = ftell(clientes);
    fseek(clientes, 0, SEEK_END);
    int endpos = ftell(clientes);
    if(pos == ftell(clientes)) {
        fprintf(
            clientes, "%lld|%s|%s|%s|%s|",
            registro.cpf, registro.nome, registro.sobrenome,
            registro.telefone, registro.cidade
        );

        fclose(clientes);
        fclose(temp);

        printf("Cliente adicionado ao sistema!\n\n");
        return;
    }


    fseek(clientes, 0, SEEK_SET);

    long long cpf = 0;
    char c = '\0';
    while(ftell(clientes) != endpos) {
        fscanf(clientes, "%lld", &cpf);
        if(cpf >= registro.cpf) {
            fprintf(
                temp, "%lld|%s|%s|%s|%s|%lld",
                registro.cpf, registro.nome, registro.sobrenome,
                registro.telefone, registro.cidade, cpf
            );

            goto exit;
        }

        fprintf(temp, "%lld", cpf);

        for(int i = 0; i < 5;) {
            if((c = getc(clientes)) == EOF) break;
            if(c == '|') i++;
            putc(c, temp);
        }
    }

    fprintf(
        temp, "%lld|%s|%s|%s|%s",
        registro.cpf, registro.nome, registro.sobrenome,
        registro.telefone, registro.cidade
    );

    exit: 

    while((c = getc(clientes)) != EOF) {
        putc(c, temp);
    }

    fclose(clientes);
    fclose(temp);

    clientes = fopen("clientes.bin", "wb");
    temp = fopen("temp.bin", "rb");

    while((c = getc(temp)) != EOF)
        putc(c, clientes);

    fclose(clientes);
    fclose(temp);

    printf("Cliente adicionado ao sistema!\n\n");
}