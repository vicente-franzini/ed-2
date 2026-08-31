CC=gcc
CFLAGS=-std=c23
ARQS=atualizacao.c busca.c exercicio.c insercao.c merge.c remocao.c
OUT=out/exercicio

.DEFAULT_GOAL := build

build: $(ARQS) exercicio.h
	$(CC) $(CFLAGS) -o $(OUT) $(ARQS)

run: $(OUT)
	$(OUT)

clean:
	rm *.bin out/exercicio

all: build run