// Questão 4 • Codifique a sequência AAABBBCCCCCCCCDDDEEEE
// usando RLE com um byte de escape.

// 3:A 3:B 8:C 3:D 4:E
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct RLE_Chunk {
    unsigned char n;
    char c;
};

int main() {
    char buffer[256];
    fgets(buffer, 255, stdin);

    FILE *bin = fopen("rle.bin", "w+b");
    assert(bin != NULL);

    struct RLE_Chunk chunk = {
        .n = 1,
        .c = buffer[0]
    };

    /* Encode de buffer em RLE para rle.bin */
    for(int i = 1; buffer[i] != '\0'; i++) {
        if(buffer[i] == chunk.c) {
            chunk.n++;
            continue;
        }

        fwrite(&chunk, sizeof(struct RLE_Chunk), 1, bin);
        chunk.c = buffer[i];
        chunk.n = 1;
    }

    chunk.c = '\0';
    chunk.n = 255;
    fwrite(&chunk, sizeof(struct RLE_Chunk), 1, bin);


    /* Decode de rle.bin para o terminal */
    fseek(bin, 0, SEEK_SET);

    for(
        fread(&chunk, sizeof(struct RLE_Chunk), 1, bin);
        chunk.c != '\0';
        fread(&chunk, sizeof(struct RLE_Chunk), 1, bin)
    ) {
        printf("%d:%c ", chunk.n, chunk.c);
    }

    putchar('\n');
    fclose(bin);

    return 0;
}

