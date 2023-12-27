//
// Created by Ahmed Elsayed on 12/17/2023.
//

#ifndef KYBER_TOY_H
#define KYBER_TOY_H
#include <stdio.h>
#include "stdlib.h"
#include "Poly.h"
#include "definitions.h"
#include "Cipher.h"
//polynomial multiplication in Z97[X]/(X^4+1)
static void toy_polmul_naive(
        int *dst,
        const int *a,
        const int *b,
        int add_to_dst //if true: dst += a*b;  if false: dst = a*b;

);
/* [
     * [[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0]]
     * [[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0]]
     * [[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0]]
 * ]
 *
 *
 * */
void add_vector_poly(Poly dst[TK_K], const Poly a[TK_K], const Poly b[TK_K]);
void toy_gen(Poly A[TK_K][TK_K],
             Poly t[TK_K],
             Poly s[TK_K]);
void toy_enc(const Poly A[TK_K][TK_K], const Poly t[TK_K], int plain, Poly u[TK_K], Poly v,int blocks,Cipher c[blocks]);
int toy_dec(Poly s[TK_K],Poly u[TK_K] ,Poly v);
void normal_distribution(Poly A[TK_K][TK_K]);
void binomial_distribution(int row,Poly s[row]);
void print_a_matrix(Poly A[TK_K][TK_K]);
void print2d_matrix(Poly a[TK_K]);
void transpose_matrix(Poly A[TK_K][TK_K]);
void copy_matrix(Poly dst[TK_K][TK_K],Poly src[TK_K][TK_K]);
#endif //KYBER_TOY_H
