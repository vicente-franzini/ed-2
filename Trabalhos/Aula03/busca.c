#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "exercicio.h"

// Implementação extremamente básica de um vetor dinâmicamente alocado para armazenar
// os ponteiros de localização
typedef struct vetor {
    size_t capacidade;
    size_t tamanho;
    long *arr;
} vetor_t;

void v_pushback(vetor_t *vetor, long valor) {
    if(vetor->tamanho >= vetor->capacidade) {
        vetor->capacidade *= 2;
        vetor->arr = realloc(vetor->arr, sizeof(long) * vetor->capacidade);

        if(vetor->arr == NULL) err(1, "Erro na alocação de memória");
    }

    vetor->arr[vetor->tamanho++] = valor;
}

void busca() {
    FILE *clientes = fopen("clientes.bin", "r+b");
    if(clientes == NULL) {
        err(1, "Houve um erro na abertura dos arquivos");
    }

    // Criação do vetor para armazenar os ponteiros
    vetor_t vetor = {
        .capacidade = 8,
        .tamanho = 0,
        .arr = malloc(8 * sizeof(long)),
    };

    if(vetor.arr == NULL) {
        err(1, "Erro na alocação de memória");
    }

    // Percorre o vetor, contando o número de caracteres '|'.
    // No caso do número de "pipes" ser um múltiplo exato de 5,
    // e de não ter sido inserido ainda no vetor, insira o atual índice
    int pipes = 0;
    char c = '\0';
    while((c = getc(clientes)) != EOF) {
        if(pipes / 5 >= vetor.tamanho)
            v_pushback(&vetor, ftell(clientes) - 1);

        if(c == '|') pipes++;
    }

    // Caso haja alguma mudança no arquivo inicial após esse ponto,
    // o vetor não é mais preciso. Sendo assim, ele só vale para uma
    // snapshot do arquivo prévio a esse ponto.

    if(vetor.tamanho <= 0) {
        fclose(clientes);
        printf("Não existem clientes registrados no sistema.\n\n");
        return;
    }

    // Obtém o CPF sendo procurado
    long long cpf_bus = 0;
    printf("Insira o CPF da pessoa (apenas números)\n> ");
    scanf(" %lld", &cpf_bus);

    // Busca binária pelo vetor
    int ls = 0, rs = vetor.tamanho, achado = 0;
    long long cpf = 0;
    while(1) {
        if(rs <= ls) break;

        // Mova o ponteiro do arquivo para a posição inicial do registro
        fseek(clientes, vetor.arr[(ls + rs) / 2], SEEK_SET);
        fscanf(clientes, "%lld", &cpf);

        if(cpf == cpf_bus) {
            achado = 1;
            break;
        } else if(cpf > cpf_bus) {
            rs = (ls+rs) / 2;
        } else {
            ls = (ls+rs) / 2;
        }
    }

    if(achado == 0) {
        fclose(clientes);
        printf("Cliente não encontrado.\n\n");
        return;
    } else {

        // Obtém as informações do registro do arquivo e imprime-as no terminal
        fseek(clientes, vetor.arr[(ls+rs) / 2], SEEK_SET);
        registro_t registro = {0};

        fscanf(clientes, " %lld", &registro.cpf);
        fseek(clientes, 1, SEEK_CUR);
        fscanf(clientes, " %"STR_SIZE_S"[^|]s", &registro.nome);
        fseek(clientes, 1, SEEK_CUR);
        fscanf(clientes, " %"STR_SIZE_S"[^|]s", &registro.sobrenome);
        fseek(clientes, 1, SEEK_CUR);
        fscanf(clientes, " %"STR_SIZE_S"[^|]s", &registro.telefone);
        fseek(clientes, 1, SEEK_CUR);
        fscanf(clientes, " %"STR_SIZE_S"[^|]s", &registro.cidade);

        printf(
            "Registro do cliente (%lld):\n"
            " %s (%s)\n"
            " Tel: %s\n"
            " Cidade: %s\n\n",
            registro.cpf, registro.nome, registro.sobrenome,
            registro.telefone, registro.cidade
        );
        fclose(clientes);
        return;
    }

}