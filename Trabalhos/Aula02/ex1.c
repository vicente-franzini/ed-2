// Exercício 1 • Faça um programa capaz de ler um texto
// digitado do teclado e gravá-lo em um arquivo em disco.
// Utilize a tecla ESC (0x1B) para terminar a leitura.
// Utilize um editor de textos para ler e mostrar na
// tela o resultado do seu programa.

// NOTA: Devido ao pedido da utilização da tecla ESC,
// esse programa é feito para ser executado somente em
// sistemas POSIX (como Linux).

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>

struct termios config_padrao;

typedef struct string {
    size_t cap;
    size_t siz;
    char *buf;
} string_t;

void s_pushback(string_t *str, char c) {
    if(str->siz >= (str->cap - 1)) {
        str->cap *= 2;
        str->buf = (char *) realloc(str->buf, sizeof(char) * str->cap);
    }

    assert(str->buf != NULL);
    str->buf[str->siz++] = c;
    str->buf[str->siz] = '\0';
}

void s_popback(string_t *str) {
    str->buf[str->siz--] = '\0';
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &config_padrao);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &config_padrao);
    atexit(disableRawMode);

    struct termios raw = config_padrao;
    raw.c_lflag &= ~(IXON);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &raw);
    fflush(stdout);
}

int main() {
    enableRawMode();

    char c = '\0';
    string_t output = {
        .cap = 8,
        .siz = 0,
        .buf = (char *) calloc(8, sizeof(char))
    };

    assert(output.buf != NULL);

    while(read(STDIN_FILENO, &c, 1) == 1 && c != 27) {
        if(iscntrl(c)) {
            if(c == 127 && output.siz != 0) {
                printf("\e[1D\e[0K");
                fflush(stdout);
                s_popback(&output);
            } else if(c == '\n') {
                s_pushback(&output, '\n');
                putchar('\n');
                fflush(stdout);
            }
        } else {
            putchar(c);
            fflush(stdout);
            s_pushback(&output, c);
        }
    }

    FILE *output_file = fopen("out.txt", "wb");
    for(int i = 0; i < output.siz; i++) fputc(output.buf[i], output_file);
    fclose(output_file);

    return 0;
}