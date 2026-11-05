/*
 * --------------|Exercício - Typedef Struct|--------------
 *
 *  Em código C, faça structs que permitam a construção de
 *  Hash, com inserção, busca e tratamento de colisão com
 *  sondagem quadrática.
 * 
 * --------------------------------------------------------
 */

#pragma once
#ifndef Q3_H
#define Q3_H

#include <stddef.h>

#define _hash(k, numBuckets) ((k) % (numBuckets))

#define _hashPos(numBuckets, k, i) ((_hash(k, numBuckets) + \
((i)*(i))) % (numBuckets))

typedef struct bucket_t;
typedef struct hash_t;

typedef struct _hash_t {
    size_t numBuckets;
    bucket_t *buckets;
} hash_t;

typedef struct _bucket_t {
    int key;

//  No caso de ser necessário a implementação da operação de
//  remoção, podemos armazenar se o valor em um bucket foi
//  removido ou não, para distinguir entre buckets não
//  alocados e aqueles que, possivelmente, já geraram colisão
//
//  bool removido;
} bucket_t;

void inserirHash(hash_t *hash, int chave);
int buscarHash(hash_t *hash, int chave);

#endif