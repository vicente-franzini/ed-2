#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "exercicio.h"

void insercao() {

    // Tenta abrir os arquivos relevantes.
    FILE *clientes = fopen("clientes.bin", "r+b");
    FILE *temp = fopen("temp.bin", "wb");
    if(clientes == NULL || temp == NULL) {
        err(1, "Houve um erro na abertura dos arquivos");
    }

    // Obtém todas as informações do cliente, para armazenar no arquivo.
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

    // Obtém as posições iniciais e finais para comparação posterior
    int pos = ftell(clientes);
    fseek(clientes, 0, SEEK_END);
    int endpos = ftell(clientes);

    // Se o arquivo estiver vazio, apenas armazene o cliente atual e retorne.
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

    // Percorre o arquivo clientes.bin, procurando o local ideal e copiando
    // o registro ordenado para o arquivo temp
    long long cpf = 0;
    char c = '\0';
    while(ftell(clientes) != endpos) {
        fscanf(clientes, "%lld", &cpf);

        // Caso seja o local ordenado para inserir o registro, insira e saia
        // do loop
        if(cpf >= registro.cpf) {
            fprintf(
                temp, "%lld|%s|%s|%s|%s|%lld",
                registro.cpf, registro.nome, registro.sobrenome,
                registro.telefone, registro.cidade, cpf
            );

            goto exit;
        }


        // Copia o registro lido de clientes.bin para o arquivo temp
        fprintf(temp, "%lld", cpf);

        for(int i = 0; i < 5;) {
            if((c = getc(clientes)) == EOF) break;
            if(c == '|') i++;
            putc(c, temp);
        }
    }

    // Caso o laço não tenha inserido o registro, este deve estar no final.
    // Insira-o
    fprintf(
        temp, "%lld|%s|%s|%s|%s",
        registro.cpf, registro.nome, registro.sobrenome,
        registro.telefone, registro.cidade
    );

    // posição de saída do loop caso o registro tenha sido inserido
    exit: 

    // Copia o resto do arquivo clientes.bin para o arquivo temp
    while((c = getc(clientes)) != EOF) {
        putc(c, temp);
    }

    fclose(clientes);
    fclose(temp);

    // Copia o arquivo temp para o arquivo clientes.bin
    clientes = fopen("clientes.bin", "wb");
    temp = fopen("temp.bin", "rb");

    while((c = getc(temp)) != EOF)
        putc(c, clientes);

    fclose(clientes);
    fclose(temp);

    printf("Cliente adicionado ao sistema!\n\n");
}