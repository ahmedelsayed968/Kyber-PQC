#include <stdio.h>
#include "toy.h"




Poly a[ TK_K ][ TK_K ];
Poly s[ TK_K ];
Poly t[ TK_K ];
int main() {
    printf("A Matrix\n");
    print_a_matrix(a);
    printf("S Matrix\n");
    print2d_matrix(s);
    printf("t Matrix\n");
    print2d_matrix(t);

    toy_gen(a,t,s);
    printf("A Matrix\n");
    print_a_matrix(a);
    printf("S Matrix\n");
    print2d_matrix(s);
    printf("t Matrix\n");
    print2d_matrix(t);
//    const anonymous struct **a = {1, 2, 3, 4};
    Poly b = {5,6,7,8};
//    swap_poly(&a,&b);
//    print_poly(&a);
//    print_poly(&b);
    Poly u[TK_K], v;
    initialize_poly(&v);
    int blocks = (int)(256/TK_N);
    Cipher c[blocks];
    int plain = 12;
    printf(" plain text is %d\n",plain);
    toy_enc(a,t,plain,u,v,blocks,c);
    int plain_decyphered =  toy_dec(s, u ,v);
    printf(" Decrypted text is %d\n",plain_decyphered);
    for (int i = 0; i < blocks; ++i) {
       // print_cipher(&c[i],i);
    }
    return 0;
}
