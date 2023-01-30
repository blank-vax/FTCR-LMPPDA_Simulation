/*
 * @Author: B1ank
 * @Date: 2022-12-20 17:16:19
 * @LastEditTime: 2023-01-13 14:36:19
 * @LastEditors: your name
 * @Description: The implementation for polynomials operations
 * @FilePath: /FTCR-LMPPDA/src/poly.c
 */

#include <stdlib.h>
#include <string.h>
#include "poly.h"

void polyAdd(poly *a, poly *b){
    uint64_t i;
    for (i=0;i<b->N;i++) {
        a->coeffs[i] += b->coeffs[i];
    }
}

void polyAddOne(poly *a){
    a->coeffs[0] += 1;
}

void polySub(poly *a, poly *b){
    uint64_t i;
    for(i=0;i<b->N;i++) {
        a->coeffs[i] -= b->coeffs[i];
    }
}

uint64_t polyMultMod(poly *a, poly *b, poly *c, uint64_t modulus){
    uint64_t N = a->N;
    if(N != b->N) {
        return 0;
    }
    c->N = N;

    memset(&c->coeffs, 0, N*sizeof(c->coeffs[0]));
    uint64_t k;
    for(k=0;k<N;k++){
        uint64_t ck1 = 0;
        uint64_t i;
        for(i=0;i<=k;i++) {
            ck1 += ((uint64_t)a->coeffs[i]) * b->coeffs[k-i];
        }
        uint64_t ck2 = 0;
        for(i=k+1;i<N;i++) {
            ck2 += ((uint64_t)a->coeffs[i]) * b->coeffs[k+N-i];
        }
        uint64_t ck = c->coeffs[k]+ck1+ck2;
        // ! c->coeffs[k] = ck % modulus;
        c->coeffs[k] = ck;
        if(k<N){
            uint64_t ck = c->coeffs[k+1] + ck2;
            // ! c->coeffs[k+1] = ck % modulus;
            c->coeffs[k+1] = ck;
        }
    }
    return 1;
}

void polyScalarMultMod(poly *a, uint64_t scalarFactor, uint64_t modulus){
    uint64_t i;
    for(i=0;i<a->N;i++) {
        // ! a->coeffs[i] = ((a->coeffs[i]) * scalarFactor) % modulus;
        a->coeffs[i] = a->coeffs[i] * scalarFactor;
    }
}

// All the power in result polynomial is less than N, at most N-1
void polyMod(poly *p, poly *result, uint64_t N, uint64_t modulus){
    uint64_t originN = p->N;
    uint64_t remainder = originN % N;
    uint64_t blockNumber = (originN-remainder) / N;
    uint64_t index1, index2;
    for(index1=0;index1<remainder;index1++){
        for(index2=0;index2<blockNumber+1;index2++){
            result->coeffs[index1] += p->coeffs[index1+index2*N];
        }
        result->coeffs[index1] %= modulus;
    }
    for(index1=remainder;index1<N;index1++){
        for(index2=0;index2<blockNumber;index2++){
            result->coeffs[index1] += p->coeffs[index1+index2*N];
        }
        result->coeffs[index1] %= modulus;
    }
}

// According to polyMod, design the scalarMod to perform the modular operation on coefficients
void scalarMod(poly *a, uint64_t modulus){
    uint64_t N = a->N;
    for (int index = 0;index<a->N;index++) {
        a->coeffs[index] = a->coeffs[index] % modulus;
    }
}

// Calculates the multiplicative inverse of a mod modulus using the extended Euclidean algorithm.
uint64_t intInverse(uint64_t a, uint64_t modulus){
    int16_t x = 0;
    int16_t lastx = 1;
    int16_t y = 1;
    int16_t lasty = 0;
    int16_t b = modulus;
    while (b != 0) {
        int16_t quotient = a / b;

        int16_t temp = a;
        a = b;
        b = temp % b;

        temp = x;
        x = lastx - quotient*x;
        lastx = temp;

        temp = y;
        y = lasty - quotient*y;
        lasty = temp;
    }
    if (lastx < 0)
        lastx += modulus;
    return lastx;
}

void polyZeroing(poly *a, uint64_t N){
    a->N = N;
    memset(&a->coeffs, 0, N*sizeof(a->coeffs[0]));
}

void polyCopy(poly *a, poly *b){
    memcpy(&b->coeffs, &a->coeffs, a->N*sizeof(a->coeffs[0]));
    b->N = a->N;
}

uint8_t equalsZero(poly *a){
    uint64_t i;
    for(i=0;i<a->N;i++){
        if(a->coeffs[i] != 0)
            return 0;
    }
    return 1;
}

uint64_t polyDegree(poly *a){
    uint64_t i;
    for(i=a->N-1;i>0;i--){
        if(a->coeffs[i] != 0){
            return i;
        }
    }
    return 0;
}

void polyReduce(poly *a, poly *b, uint64_t modulus){
    uint64_t N = a->N -1;
    memcpy(&b->coeffs, &a->coeffs, N*sizeof(a->coeffs[0]));
    b->coeffs[0] = (((uint64_t)b->coeffs[0]) + a->coeffs[N]) % modulus;
    b->coeffs[1] = (((uint64_t)b->coeffs[1]) + a->coeffs[N]) % modulus;
    b->N = N;
}

void polyDivX(poly *a, uint64_t modulus){
    uint64_t N = a->N;
    uint64_t a0 = a->coeffs[0];
    memmove(&a->coeffs[0], &a->coeffs[1], (N-1)*sizeof(a->coeffs[0]));
    a->coeffs[N-1] = a0;
    a->coeffs[0] = (((uint64_t)a->coeffs[0])-a0+modulus) % modulus;
}

void polySubMult(poly *a, poly *b, uint64_t u, uint64_t modulus){
    uint64_t N = a->N;
    if(b->N > N) {
        N = b->N;
    }

    uint64_t i;
    for(i=0;i<N;i++){
        uint64_t ai = a->coeffs[i];
        ai += ((uint64_t)u) * (modulus-b->coeffs[i]);
        a->coeffs[i] = ai % modulus;
    }
}


// Calculates the multiplicative inverse of the input polynomial of a mod modulus
// with the help of the extended Euclidean algorithm.
uint8_t polyInverse(poly *a, poly *inv, uint64_t modulus){
    uint64_t N = a->N;
    uint64_t k = 0;
    poly *b = alloca(sizeof(*b));
    polyZeroing(b, N+1);
    b->coeffs[0] = 1;
    poly *c = alloca(sizeof(*c));
    polyZeroing(c, N+1);

    // f = a
    poly *f = alloca(sizeof(*f));
    f->N = N + 1;
    polyCopy(a, f);
    f->coeffs[N] = 0;

    // g = x^p-1
    poly *g = alloca(sizeof(*g));
    polyZeroing(g, N+1);
    g->coeffs[0] = modulus - 1;
    g->coeffs[1] = modulus - 1;
    g->coeffs[N] = 1;

    for(;;) {
        while(f->coeffs[0] == 0){
            uint64_t i;

            // f(X) = f(x) / x
            for(i=1;i<=N;i++){
                f->coeffs[i-1] = f->coeffs[i];
            }
            f->coeffs[N] = 0;

            // c(x) = c(x) * x
            for(i=N-1;i>0;i--){
                c->coeffs[i] = c->coeffs[i-1];
            }
            c->coeffs[0] = 0;

            k++;
            if(equalsZero(f)){ // not invertible
                return 0;
            }
        }

        if(polyDegree(f) == 0) {
            uint64_t f0Inv = intInverse(f->coeffs[0], modulus);
            polyScalarMultMod(b, f0Inv, modulus); // b = b * f[0]^(-1)
            polyReduce(b, inv, modulus);
            uint64_t i;

            // b = b * x^(-k)
            for(i=0;i<k;i++){
                polyDivX(inv, modulus);
            }

            return 1;
        }
        if(polyDegree(f) < polyDegree(g)) {
            // exchange f and g
            poly *temp = f;
            f = g;
            g = temp;
            // exchange b and c
            temp = b;
            b = c;
            c = temp;
        }
        // u = f[0]*g[0]^(-1)
        uint64_t g0Inv = intInverse(g->coeffs[0], modulus);
        uint64_t u = (f->coeffs[0]*(uint64_t)g0Inv) % modulus;

        polySubMult(f, g, u, modulus); // f = f - u * g
        polySubMult(b, c, u, modulus); // b = b - u * c
    }
}

void randPoly(poly *a, uint64_t N, uint64_t modulus){
    uint64_t i;
    a->N = N;
    for(i=0;i<N;i++){
        // a->coeffs[i] = random() % modulus;
        a->coeffs[i] = rand() % modulus;
    }
}

uint8_t equalsOne(poly *a){
    uint64_t i;
    for(i=1;i<a->N;i++) {
        if(a->coeffs[i] != 0){
            return 0;
        }
    }
    return a->coeffs[0] == 1;
}

