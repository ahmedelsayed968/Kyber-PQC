//
// Created by Ahmed Elsayed on 12/26/2023.
//
#include "Poly.h"
void initialize_poly(Poly *p) {
    for (int i = 0; i < TK_N; ++i) {
        p->coeffs[i] = 0;
    }
}
void p_normal_distribution(Poly *p) {
    for (int i = 0; i < TK_N; ++i) {
        p->coeffs[i] = rand() % TK_Q;
    }
}
void p_binomial_distribution(Poly *p) {
    for (int i = 0; i < TK_N; ++i) {
        int val = rand() & 3;
        p->coeffs[i] = (val & 1) - (val >> 1 & 1);
    }
}
void add_poly(Poly *dst, const Poly *a, const Poly *b) {
    for (int i = 0; i < TK_N; ++i) {
        dst->coeffs[i] = ((a->coeffs[i] + b->coeffs[i]) % TK_Q + TK_Q)%TK_Q;
    }
}
void swap_poly(Poly *a, Poly *b) {
    Poly temp = *a;
    *a = *b;
    *b = temp;
}
void print_poly(Poly *p){
    for (int i = 0; i <TK_N ; ++i) {
        printf("%d ",p->coeffs[i]);
    }
    printf("\n");
}