// Questão 4 • Codifique a sequência AAABBBCCCCCCCCDDDEEEE
// usando RLE com um byte de escape.

// 3:A 3:B 8:C 3:D 4:E
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct RLE_Chunk {
    char magic;
    unsigned char n;
    char c;
};

int main() {
    char buffer[256];
    fgets(buffer, 255, stdin);

    FILE *bin = fopen("rle.bin", "w+b");
    assert(bin != NULL);

    struct RLE_Chunk chunk = {
        .magic = '\0',
        .n = 1,
        .c = buffer[0]
    };

    /* Encode de buffer em RLE para rle.bin */
    for(int i = 1; buffer[i] != '\0'; i++) {
        if(buffer[i] == chunk.c) {
            chunk.n++;
            continue;
        }

        if(chunk.n >= 3) {
            fwrite(&chunk, sizeof(struct RLE_Chunk), 1, bin);  
        }
        else if(chunk.n == 2) fprintf(bin, "%c%c", chunk.c, chunk.c);
        else fputc(chunk.c, bin);

        chunk.c = buffer[i];
        chunk.n = 1;  
    }

    /* Decode de rle.bin para o terminal */
    fseek(bin, 0, SEEK_SET);
    char c;

    unsigned char n;
    while((c = fgetc(bin)) != EOF) {
        if(c != '\0') {
            putchar(c);
            continue;
        }
        
        fseek(bin, -1, SEEK_CUR);
        fread(&chunk, sizeof(struct RLE_Chunk), 1, bin);

        while(chunk.n--) putchar(chunk.c);
    }

    putchar('\n');
    fclose(bin);

    return 0;
}

