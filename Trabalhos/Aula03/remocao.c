#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "exercicio.h"

void remocao() {
    
    // Tentamos abrir os arquivos fonte
    FILE *clientes = fopen("clientes.bin", "r+b");
    FILE *temp = fopen("temp.bin", "wb");
    if(clientes == NULL || temp == NULL) {
        err(1, "Houve um erro na abertura dos arquivos");
    }

    // Verificamos se o arquivo clientes está vazio ou não
    int pos = ftell(clientes);
    fseek(clientes, 0, SEEK_END);
    int endpos = ftell(clientes);
    if(pos == ftell(clientes)) {
        fclose(clientes);
        fclose(temp);

        printf("Não existem clientes registrados no sistema.\n\n");
        return;
    }

    // Obtemos o CPF do registro que queremos remover
    long long cpf_rem = 0;
    fseek(clientes, 0, SEEK_SET);
    printf("Insira o CPF da pessoa (apenas números)\n> ");
    scanf(" %lld", &cpf_rem);

    // Percorremos o arquivo inteiro, registro a registro
    int clienteAchado = 0;
    char c = '\0';
    long long cpf = 0;
    while(ftell(clientes) != endpos) {
        // Obtemos o CPF do registro
        fscanf(clientes, "%lld", &cpf);

        // Caso não seja o CPF que queremos remover,
        // copiamos para o arquivo temporário.
        if(cpf != cpf_rem) fprintf(temp, "%lld", cpf);

        // Esse loop percorre todo o registro, contando
        // o número de caracteres '|'
        for(int i = 0; i < 5;) {
            if((c = getc(clientes)) == EOF) break;
            if(c == '|') i++;

            // Idem para cada caractere do registro
            if(cpf != cpf_rem) putc(c, temp);
        }

        if(cpf == cpf_rem) clienteAchado = 1;
    }

    fclose(clientes);
    fclose(temp);

    if(clienteAchado == 0)
        printf("O cliente não foi achado.\n\n");

    // Caso tenha um registro com o CPF solicitado para remoção,
    // o arquivo temporário não vai mais ter ele. Copie todo o
    // conteúdo do arquivo temporário ao arquivo clientes.
    else {
        temp = fopen("temp.bin", "rb");
        clientes = fopen("clientes.bin", "wb");

        while((c = getc(temp)) != EOF) putc(c, clientes);

        fclose(temp);
        fclose(clientes);

        printf("Cliente removido com sucesso!\n\n");
    }
}