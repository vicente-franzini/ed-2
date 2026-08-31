#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "exercicio.h"

void atualizacao() {
    // Abre os arquivos necessários para a execução do programa. Assume
    // que eles existam
    FILE *clientes = fopen("clientes.bin", "r+b");
    FILE *temp = fopen("temp.bin", "wb");
    if(clientes == NULL || temp == NULL) {
        err(1, "Houve um erro na abertura dos arquivos");
    }

    // Verifica se o arquivo clientes.bin é vazio ou não.
    // Além disso, armazena o ponteiro para o final do arquivo, usado posteriormente
    int pos = ftell(clientes);
    fseek(clientes, 0, SEEK_END);
    int endpos = ftell(clientes);
    if(pos == ftell(clientes)) {
        fclose(clientes);
        fclose(temp);

        printf("Não existem clientes registrados no sistema.\n\n");
        return;
    }
    fseek(clientes, 0, SEEK_SET);

    // Obtém o CPF do cliente a ser atualizado
    long long cpf_atu = 0;
    printf("Insira o CPF da pessoa (apenas números)\n> ");
    scanf(" %lld", &cpf_atu);

    // Loop que procura o cliente desejado.
    int clienteAchado = 0;
    char c = '\0';
    long long cpf = 0;
    while(ftell(clientes) != endpos) {
        fscanf(clientes, "%lld", &cpf);
        fprintf(temp, "%lld", cpf);

        // Este loop copia o registro da pessoa para o arq temp -
        for(int i = 0; i < 5;) {
            if((c = getc(clientes)) == EOF) break;
            if(c == '|') i++;

            // - caso ele não seja o CPF desejado
            if(cpf != cpf_atu) putc(c, temp);
        }

        // Obtém as novas informações do cliente para serem armazenadas
        if(cpf == cpf_atu) {
            registro_t registro = {0};

            printf("\nInsira o Nome da pessoa\n> ");
            scanf(" %"STR_SIZE_S"[^\n]s", &registro.nome);

            printf("\nInsira o Sobrenome da pessoa\n> ");
            scanf(" %"STR_SIZE_S"[^\n]s", &registro.sobrenome);

            printf("\nInsira o Telefone da pessoa\n> ");
            scanf(" %"STR_SIZE_S"[^\n]s", &registro.telefone);

            printf("\nInsira a Cidade da pessoa\n> ");
            scanf(" %"STR_SIZE_S"[^\n]s", &registro.cidade);

            fprintf(
                temp, "|%s|%s|%s|%s|",
                registro.nome, registro.sobrenome,
                registro.telefone, registro.cidade
            );

            clienteAchado = 1;
        }
    }

    fclose(clientes);
    fclose(temp);

    // Final do código. Imprime uma mensagem caso não tenha achado clientes
    if(clienteAchado == 0)
        printf("O cliente não foi achado.\n\n");
    else {
        temp = fopen("temp.bin", "rb");
        clientes = fopen("clientes.bin", "wb");

        // Copia as informações do arquivo temporário para o arquivo clientes
        while((c = getc(temp)) != EOF) putc(c, clientes);

        fclose(temp);
        fclose(clientes);

        printf("Cliente atualizado com sucesso!\n\n");
    }
}