#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "exercicio.h"

void remocao() {
    FILE *clientes = fopen("clientes.bin", "r+b");
    FILE *temp = fopen("temp.bin", "wb");
    if(clientes == NULL || temp == NULL) {
        err(1, "Houve um erro na abertura dos arquivos");
    }

    int pos = ftell(clientes);
    fseek(clientes, 0, SEEK_END);
    int endpos = ftell(clientes);
    if(pos == ftell(clientes)) {
        fclose(clientes);
        fclose(temp);

        printf("Não existem clientes registrados no sistema.\n\n");
        return;
    }

    long long cpf_rem = 0;

    fseek(clientes, 0, SEEK_SET);
    printf("Insira o CPF da pessoa (apenas números)\n> ");
    scanf(" %lld", &cpf_rem);

    int clienteAchado = 0;
    char c = '\0';
    long long cpf = 0;
    while(ftell(clientes) != endpos) {
        fscanf(clientes, "%lld", &cpf);
        if(cpf != cpf_rem) fprintf(temp, "%lld", cpf);

        for(int i = 0; i < 5;) {
            if((c = getc(clientes)) == EOF) break;
            if(c == '|') i++;

            if(cpf != cpf_rem) putc(c, temp);
        }

        if(cpf == cpf_rem) clienteAchado = 1;
    }

    fclose(clientes);
    fclose(temp);

    if(clienteAchado == 0)
        printf("O cliente não foi achado.\n\n");
    else {
        temp = fopen("temp.bin", "rb");
        clientes = fopen("clientes.bin", "wb");

        while((c = getc(temp)) != EOF) putc(c, clientes);

        fclose(temp);
        fclose(clientes);

        printf("Cliente removido com sucesso!\n\n");
    }
}