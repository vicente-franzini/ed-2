#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "exercicio.h"

void merge() {

    // Tente abrir os arquivos fonte
    FILE *clientes = fopen("clientes.bin", "r+b");
    FILE *importados = fopen("importados.bin", "r+b");
    if(clientes == NULL || importados == NULL) {
        printf("Não existe o arquivo 'importados.bin'. Crie ele e tente novamente.\n\n");
        return;
    }

    // Tente abrir o arquivo saida
    FILE *merge = fopen("clientes_merged.bin", "w+b");
    if(merge == NULL) {
        err(1, "Erro ao abrir arquivos.");
    }

    // Obtenha os ponteiros para o final do arquivo
    fseek(clientes, 0, SEEK_END);
    fseek(importados, 0, SEEK_END);
    int final_clientes = ftell(clientes);
    int final_importados = ftell(importados);

    fseek(clientes, 0, SEEK_SET);
    fseek(importados, 0, SEEK_SET);

    // Enquanto pelo menos um dos dois arquivos não tiver acabado
    while(
        ftell(clientes) != final_clientes || 
        ftell(importados) != final_importados
    ) {
        // Puxe o CPF do registro atual de ambos os arquivos
        long long cpf_c, cpf_i;
        fscanf(clientes, "%lld", &cpf_c);
        fscanf(importados, "%lld", &cpf_i);
        

        // Caso o registro do arquivo cliente seja mais ordenado do que o
        // registro do arquivo importados, ou o arquivo importados já tenha chegado ao final,
        // insira o registro do arquivo clientes
        if(
            (cpf_c < cpf_i || ftell(importados) == final_importados) &&
            ftell(clientes) != final_clientes
        ) {
            fprintf(merge, "%lld", cpf_c);

            char c = '\0';
            for(int pipes = 0; pipes < 5;) {
                if((c = getc(clientes)) == '|') pipes++;
                if(c == EOF) break;
                putc(c, merge);
            }

            if(ftell(importados) != final_importados) {
                // assumimos que o CPF tem 11 caracteres
                // precisamos retroceder o outro arquivo para poder puxar
                // o CPF novamente
                fseek(importados, -11, SEEK_SET);
            }

        // No caso de o arquivo clientes ter chegado ao final, ou o arquivo importados ainda não ter acabado,
        // insira o registro de importados.
        } else if(ftell(importados) != final_importados || ftell(clientes) == final_clientes) {
            fprintf(merge, "%lld", cpf_i);

            char c = '\0';
            for(int pipes = 0; pipes < 5;) {
                if ((c = getc(importados)) == '|') pipes++;
                if(c == EOF) break;
                putc(c, merge);
            }

            if(ftell(clientes) != final_clientes) {
                // assumimos que o CPF tem 11 caracteres
                // precisamos retroceder o outro arquivo para poder puxar
                // o CPF novamente
                fseek(clientes, -11, SEEK_SET);
            }
        }
    }

    fclose(clientes);
    fclose(importados);
    fclose(merge);

    printf("Merge concluido com sucesso!\n\n");
}