#pragma once
#ifndef EXERCICIO_H
#define EXERCICIO_H

/*

    A definição dessas duas variáveis globais são para definir o tamanho de um buffer genérico de string.
    A necessidade de duas variáveis se deve por causa de um truque no scanf, veja:

    1. em C, duas strings podem ser combinadas da seguinte forma:
        "testa" "ndo" == "testando"
       perceba que C juntou essas strings pois havia apenas espaço vazio entre as aspas. Dessa forma, o
       compilador juntou ambas formando uma só string.

    2. o especificador de formatos "%s" no scanf aceita, dentre outras coisas, como parâmetro o tamanho
       do buffer destino e do caractere a ser usado para delimitar uma string da outra (o que normalmente
       é o que chegar primeiro dentre os caracteres ' ' e '\n', ou seja, espaços e novas linhas).
       Ele funciona da seguinte forma:

       "%128[^.]s"

       O número "128" nesse caso indica que o scanf deve puxar no máximo 128 caracteres, e o [^.] indica
       que uma string acaba quando chegamos no caractere '.'

    3. Juntando tudo, temos que a string
        "%"STR_SIZE_S"[^\n]s"

       é um especificador de formato que vai puxar uma string com no máximo STR_SIZE caracteres para um buffer de
       STR_SIZE caracteres, com cada string acabando quando chegamos no caractere '\n'.

*/
#define STR_SIZE 128
#define STR_SIZE_S "127"

// Arquivo header com as definições de funções dos outros arquivos.

typedef struct registro {
    long long cpf;
    char nome[STR_SIZE];
    char sobrenome[STR_SIZE];
    char telefone[STR_SIZE];
    char cidade[STR_SIZE];
} registro_t;

void insercao();
void remocao();
void atualizacao();
void busca();
void merge();

#endif