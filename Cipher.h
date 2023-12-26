//
// Created by Ahmed Elsayed on 12/27/2023.
//

#ifndef KYBER_CIPHER_H
#define KYBER_CIPHER_H
#include "definitions.h"
#include "Poly.h"
typedef struct {
    Poly u[TK_K];
    Poly v;
} Cipher;
void print_cipher(Cipher *c, int k);
#endif //KYBER_CIPHER_H
