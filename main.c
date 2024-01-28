#include <stdio.h>
#include "toy.h"
//#include "Poly.h"
#include "definitions.h"

static void toy_polmul_naive(
        int *dst,
        const int *a,
        const int *b,
        int add_to_dst) {
    dst[0] = (((dst[0] & -add_to_dst) + a[0] * b[0] + (a[3]) * b[1] + (a[2]) * b[2] + (a[1]) * b[3]) % TK_Q + TK_Q) %
             TK_Q;
    dst[1] =
            (((dst[1] & -add_to_dst) + a[1] * b[0] + a[0] * b[1] + (a[3]) * b[2] + (a[2]) * b[3]) % TK_Q + TK_Q) % TK_Q;
    dst[2] = (((dst[2] & -add_to_dst) + a[2] * b[0] + a[1] * b[1] + a[0] * b[2] + (a[3]) * b[3]) % TK_Q + TK_Q) % TK_Q;
    dst[3] = (((dst[3] & -add_to_dst) + a[3] * b[0] + a[2] * b[1] + a[1] * b[2] + a[0] * b[3]) % TK_Q + TK_Q) % TK_Q;
}

Poly a[ TK_K ][ TK_K ];
Poly s[ TK_K ];
Poly t[ TK_K ];
//static void toy_dot(short *dst,const short *v1,const short *v2){
//    memset(dst,0,TK_N* sizeof(short));
//    for (int k = 0; k < TK_K * TK_N; k+=TK_N) {
//        toy_polmul_naive(dst,v1+k,v2+k,1);
//        //add is one so add to destination so first make dst=0
//    } }


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
    for (int i = 0; i < TK_K; ++i) {
        initialize_poly(&u[i]);
    }
    printf("u Matrix\n");
    print2d_matrix(u);
    int blocks = (int)(256/TK_N);
    Cipher c[blocks];
    int plain = 0;
    printf(" plain text is %d\n",plain);
    toy_enc(a,t,plain,u,&v,blocks,c);
    int plain_decyphered =  toy_dec(s, u ,v);
    printf(" Decrypted text is %d\n",plain_decyphered);


    return 0;
}
