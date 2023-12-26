//
// Created by Ahmed Elsayed on 12/27/2023.
//

#include "Cipher.h"
void print_cipher(Cipher *c, int k){
    printf("Block #%d:\n",k);
    printf("-u:\n");
    for (int i = 0; i <TK_K ; ++i) {
        print_poly(&c->u[i]);
    }
    printf("-v:\n");
    print_poly(&c->v);
}