// Exercicio 2 • Programas que fazem dump de arquivos são
// muito populares. Esses programas basicamente mostram o
// conteúdo do arquivo na tela na forma de números em
// hexadecimal e caracteres ASCII. Por exemplo, esta é
// a saída do programa hexdump do Unix para um arquivo
// conhecido

// Repare que os números à esquerda são os valores
// byte-a-byte do conteúdo do arquivo e os valores
// à direita são os respectivos caracteres ASCII. Alguns
// caracteres ASCII não são imprimíveis (0A 0D, por exemplo,
// que marcam o final da linha no DOS). Esses caracteres
// são impressos à direita como um ponto decimal. Cada
// linha apresenta 16 bytes do conteúdo do arquivo.
// Algumas dicas úteis:
// • As máscaras %x e %X do printf imprimem um número em
//   hexadecimal;
// • isprint(c) em ctype.h retorna verdade se c é um
//   caractere imprimível.

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

const int colunas = 16;

int main(int argc, char *argv[]) {
    // Verifica se todos os argumentos estão corretos
    if(argc < 2) {
        printf("Uso correto:\n %s <arquivo>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo e verifica se ele abriu sem erros
    FILE *arquivo = fopen(argv[1], "rb");
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -ENOLINK;
    }

    // Se o arquivo for vazio, apenas saia
    fseek(arquivo, 0, SEEK_END);
    long final  = ftell(arquivo);

    fseek(arquivo, 0, SEEK_SET);
    long comeco = ftell(arquivo);

    if(final == comeco) return 0;

    int c = '\0';                       // Buffer de caractere
    char rh_side[colunas + 1] = {0};    // String que monta o output de texto do lado direito
    size_t i = 1, coluna = 1;           // Valores para gravar em que byte e coluna estamos
    for(;; i++, coluna++) {
        // Imprime o header da linha caso seja a primeira coluna
        if(coluna == 1) printf("%08X  ", i-1);

        // Obtém um novo caractere e, caso seja o último, saia do loop
        c = fgetc(arquivo);
        if(c == EOF) break;
        
        // Imprima o caractere em hexadecimal
        printf("%02X ", c);

        // Adicione o caractere a string do lado direito
        if(!isprint(c)) rh_side[coluna - 1] = '.';
        else rh_side[coluna - 1] = c;

        rh_side[coluna] = '\0';

        // Caso seja a última coluna, imprima o lado direito e resete para a próxima linha
        if(i % colunas == 0) {
            printf("\e[%dC|%s|\n", (colunas - coluna)*3 + 1, rh_side);

            coluna = 0;
        }

    }

    // Imprima a última linha manualmente, caso ela não tenha sido impressa.
    if(coluna != 1) printf("\e[%dC|%s|\n%08X", (colunas-coluna)*3 + 4, rh_side, i-1);

    printf("\n");
    fclose(arquivo);

}