//
// Created by Ahmed Elsayed on 12/26/2023.
//

#ifndef KYBER_POLY_H
#define KYBER_POLY_H
#include "definitions.h"


typedef struct {
    int coeffs[TK_N];
} Poly;
void initialize_poly(Poly *p);
void p_normal_distribution(Poly *p);
void p_binomial_distribution(Poly *p);
void add_poly(Poly *dst, const Poly *a, const Poly *b);
void swap_poly(Poly *a, Poly *b);
void print_poly(Poly *p);
#endif //KYBER_POLY_H
