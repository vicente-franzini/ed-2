// Exercício 3 • Faça um programa similar ao comando do Unix tail –n.
// Esse programa imprime na saída padrão as últimas n linhas de um
// arquivo especificado pelo usuário.

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Uso correto:\n %s <linhas> <arquivo>\n", argv[0]);
        return 1;
    }

    int linhas = atoi(argv[1]);
    assert(linhas > 0);

    FILE *arquivo = fopen(argv[2], "rb");
    assert(arquivo != NULL);

    int i = 1;
    fseek(arquivo, -i, SEEK_END);

    long file_size = ftell(arquivo) + 1;
    char c = '\0';
    while(linhas > 0 && i <= file_size) {
        fseek(arquivo, -i, SEEK_END);
        c = fgetc(arquivo);
        if(c == '\n') linhas--;
        i++;
    }

    if(c == '\n') i--;

    fseek(arquivo, -i + 1, SEEK_END);
    while((c = fgetc(arquivo)) != EOF) {
        putchar(c);
    }

    return 0;
    
}