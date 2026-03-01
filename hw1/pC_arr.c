#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *buf;
    int gapL, gapR;
    int size;
} GapBuffer;

void initGapBuffer(GapBuffer *gb, const char *init, int reserve) {
    int len = strlen(init);
    gb->size = len + reserve;
    gb->buf = (char*)malloc(gb->size * sizeof(char));
    memcpy(gb->buf, init, len);
    gb->gapL = len;
    gb->gapR = gb->size;
}

void expand(GapBuffer *gb) {
    int oldSize = gb->size;
    int newSize = oldSize * 2;
    char *newBuf = (char*)malloc(newSize * sizeof(char));

    int rightLen = oldSize - gb->gapR;
    int newGapR = newSize - rightLen;

    memcpy(newBuf, gb->buf, gb->gapL);  // left part
    memcpy(newBuf + newGapR, gb->buf + gb->gapR, rightLen); // right part

    free(gb->buf);
    gb->buf = newBuf;
    gb->size = newSize;
    gb->gapR = newGapR;
}

void moveLeft(GapBuffer *gb) {
    if (gb->gapL > 0)
        gb->buf[--gb->gapR] = gb->buf[--gb->gapL];
}

void moveRight(GapBuffer *gb) {
    if (gb->gapR < gb->size)
        gb->buf[gb->gapL++] = gb->buf[gb->gapR++];
}

void insertChar(GapBuffer *gb, char c) {
    if (gb->gapL == gb->gapR)
        expand(gb);
    gb->buf[gb->gapL++] = c;
}

void deleteLeft(GapBuffer *gb) {
    if (gb->gapL > 0)
        gb->gapL--;
}

void printResult(GapBuffer *gb) {
    // print left part
    fwrite(gb->buf, 1, gb->gapL, stdout);
    // print right part
    fwrite(gb->buf + gb->gapR, 1, gb->size - gb->gapR, stdout);
    putchar('\n');
}

void freeGapBuffer(GapBuffer *gb) {
    free(gb->buf);
}

int main() {
    while (true) {
        static char init[300]; // initial string (max 255)
        if (fgets(init, sizeof(init), stdin) == NULL) {
            if (feof(stdin)) break;
            ferror(stdin);
            exit(1);
        }
        // remove trailing newline if present
        int len = strlen(init);
        if (len > 0 && init[len - 1] == '\n') init[len - 1] = '\0';

        int M;
        scanf("%d", &M);
        getchar();
        GapBuffer gb;
        initGapBuffer(&gb, init, 2200000 + 300);

        for (int i = 0; i < M; i++) {
            char op;
            scanf(" %c", &op);
            getchar();
            if (op == 'L') moveLeft(&gb);
            else if (op == 'R') moveRight(&gb);
            else if (op == 'D') deleteLeft(&gb);
            else if (op == 'I') {
                char c;
                scanf(" %c", &c);
                getchar();
                insertChar(&gb, c);
            }
        }

        printResult(&gb);
        freeGapBuffer(&gb);
    }

    return 0;
}