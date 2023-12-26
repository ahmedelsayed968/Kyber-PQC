//
// Created by Ahmed Elsayed on 12/17/2023.
//
#include "toy.h"
#include "Cipher.h"
#include "math.h"

static void toy_polmul_naive(
        int *dst,
        const int *a,
        const int *b,
        int add_to_dst){
    if (!add_to_dst) {
        dst[0] = (((a[0] * b[0] - a[3] * b[1] - a[2] * b[2] - a[1] * b[3]) % TK_Q) + TK_Q)%TK_Q;
        dst[1] = (((a[1] * b[0] + a[0] * b[1] - a[3] * b[2] - a[2] * b[3]) % TK_Q)+TK_Q)%TK_Q;
        dst[2] = (((a[2] * b[0] + a[1] * b[1] + a[0] * b[2] - a[3] * b[3]) % TK_Q)+TK_Q)%TK_Q;
        dst[3] = (((a[3] * b[0] + a[2] * b[1] + a[1] * b[2] + a[0] * b[3]) % TK_Q)+TK_Q)%TK_Q;
    }
    else{
        dst[0] += (((a[0] * b[0] - a[3] * b[1] - a[2] * b[2] - a[1] * b[3]) % TK_Q) + TK_Q)%TK_Q;
        dst[1] += (((a[1] * b[0] + a[0] * b[1] - a[3] * b[2] - a[2] * b[3]) % TK_Q)+TK_Q)%TK_Q;
        dst[2] += (((a[2] * b[0] + a[1] * b[1] + a[0] * b[2] - a[3] * b[3]) % TK_Q)+TK_Q)%TK_Q;
        dst[3] += (((a[3] * b[0] + a[2] * b[1] + a[1] * b[2] + a[0] * b[3]) % TK_Q)+TK_Q)%TK_Q;
    }
}
void transpose_matrix(Poly A[TK_K][TK_K]){
    for (int i = 0; i < TK_K; ++i) {
        for (int j = i+1; j < TK_K; ++j) {
            swap_poly(&A[i][j],&A[j][i]);
        }
    }
}
void copy_matrix(Poly dst[TK_K][TK_K],Poly src[TK_K][TK_K]){
    for (int i = 0; i < TK_K; ++i) {
        for (int j = 0; j < TK_K; ++j) {
            dst[i][j] = src[i][j];
        }
    }
}
void toy_gen(Poly A[TK_K][TK_K],
             Poly t[TK_K],
             Poly s[TK_K]){
    // 1. generate Matrix A(k,k) with uniformly random numbers mod TK_Q
    // A = [[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0],
    //     [x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0],
    //     [x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0],[x^3,x^2,x^1,x^0]]
    // 2. generate s , e with small random numbers mod TK_Q
    /*
     *Pseudocode for the main operations:
        Gen():
        Fill K*K-matrix A with uniformly random numbers mod q
        Fill K-vectors s & e with small random numbers mod q, defined as
        val = rand()&3 //Uniform distribution
        buffer[i] = (val&1) – (val>>1&1) //Binomial distribution
        t = A.s + e //matrix-vector multiplication in Zq[X]/(X^n+1)
        (A, t) is the public key
        While (s) is the private key
     *
     * */
    normal_distribution(A);
    binomial_distribution(TK_K,s);
    Poly e[TK_K];
    binomial_distribution(TK_K,e);
    printf("e matrix\n");
    print2d_matrix(e);

//    // t = A.s +e
    for (int i = 0; i < TK_K; ++i) {
     for (int j = 0; j<TK_K;j++){
         toy_polmul_naive(t[i].coeffs,A[i][j].coeffs,s[j].coeffs,1);
        }
    }
    add_vector_poly(t,t,e);

}
void add_vector_poly(Poly dst[TK_K], const Poly a[TK_K], const Poly b[TK_K]){
    for(int i=0 ; i < TK_K;i++){
        add_poly(&dst[i],&a[i],&b[i]);
    }
}

void toy_enc(const Poly A[TK_K][TK_K], const Poly t[TK_K], int plain, Poly u[TK_K], Poly v,int blocks,Cipher c[blocks]){
//    Fill K-vectors r & e1, and the scalar (one-polynomial) e2 with small
//    random numbers mod q
//    u = A_transpose(K,K) . r(K,1) + e1(K,1)
//    msg_bits[i] = plain>>i&1
//    v = t(1,K) dot r(K,1) + e2 + msg_bits * q/2
//    (u, v) is the ciphertext
//    While (r) is the decryption key
    Poly r[TK_K];
    binomial_distribution(TK_K,r);
    Poly e1[TK_K];
    binomial_distribution(TK_K,e1);
    Poly e2;
    p_binomial_distribution(&e2);
    // transpose A
    Poly A_transpose[TK_K][TK_K];
    copy_matrix(A_transpose,A);
    transpose_matrix(A_transpose);
    // u = A_transpose(K,K) . r(K,1) + e1(K,1)
    for (int i = 0; i < TK_K; ++i) {
        for (int j = 0; j < TK_K; ++j) {
            toy_polmul_naive(u[i].coeffs,A_transpose[i][j].coeffs,r[j].coeffs,1);
        }
    }
    add_vector_poly(u,u,e1);
    //    v = t(1,K) dot r(K,1) + e2 + msg_bits * q/2
    for (int i = 0; i < TK_K; ++i) {
        toy_polmul_naive(v.coeffs,t[i].coeffs,r[i].coeffs,1);
    }
    add_poly(&v,&v,&e2);
//    int blocks = (int)(256/TK_N)+1;
//    Cipher c[blocks];
//    print_poly(&v);
//    for (int i = 0; i < TK_K; ++i) {
//        print_poly(&u[i]);
//    }
    int j = 0;
    for (int i = 0; i < blocks; ++i) {
        Poly msg_bits;
        int k = 0;
        for (; j < 256; ++j) {
            int val = (plain>>j)&1;
            int val2 = (int)ceil(TK_Q/2);
            msg_bits.coeffs[k++] = val*val2;
            if (j && j%TK_N == 0){
                break;
            }
        }
        Poly  temp;
        add_vector_poly(&temp,&v,&msg_bits);
        for (int l = 0; l < TK_K; ++l) {
            c[i].u[l] = u[l];
        }
        c[i].v = temp;

    }

}
int toy_dec(const short *s, const short *u, const short *v){
    return 0;
}
void normal_distribution(Poly A[TK_K][TK_K]){
    srand(time(NULL));
    for (int i = 0; i < TK_K; ++i) {
        for (int j = 0; j < TK_K; ++j) {
            initialize_poly(&A[i][j]);
            for (int k = 0; k < TK_N; ++k) {
                A[i][j].coeffs[k] = rand() % TK_Q;
            }
        }
    }
}
void binomial_distribution(int row,Poly s[row]){
    for (int i = 0; i < row; ++i) {
        p_binomial_distribution(&s[i]);
    }
}

void print_a_matrix(Poly A[TK_K][TK_K]){
    for (int i = 0; i < TK_K; ++i) {
        for (int j = 0; j < TK_K; ++j) {
            for (int k = 0; k < TK_N; ++k) {
                printf("%d ",A[i][j].coeffs[k]);
            }
            printf("\t");
        }
        printf("\n");
    }
}
void print2d_matrix(Poly a[TK_K]){
    for (int i = 0; i < TK_K; ++i) {
        for (int j = 0; j < TK_N; ++j) {
            printf("%d ",a[i].coeffs[j]);
        }
        printf("\n");
    }
    printf("\n");
}