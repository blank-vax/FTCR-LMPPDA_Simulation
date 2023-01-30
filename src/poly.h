/*** 
 * @Author: B1ank
 * @Date: 2022-12-20 17:16:15
 * @LastEditTime: 2023-01-11 17:04:45
 * @LastEditors: your name
 * @Description: The header definition file for polynomials operations
 * @FilePath: /FTCR-LMPPDA/src/poly.h
 */

#ifndef POLY_H
#define POLY_H


#include <stddef.h>
#include <stdint.h>
#include "params.h"


/*** 
 * @description: Definition of structure named `poly` containing the polynomial coefficients array `coeffs` and its degree `N`
 * @return {*}
 */
typedef struct {
    uint64_t coeffs[NTRU_INT_POLY_SIZE];
    uint64_t N;
} poly;

// Addition and Subtraction

/*** 
 * @description: Addition of two polynomials
 * @param {poly} *a input and output parameter; coefficients are overwritten
 * @param {poly} *b a polynomial to add to the polynomial a
 * @return {*}
 */
void polyAdd(poly *a, poly *b);


/*** 
 * @description: Return a new polynomial with all coefficients plus one
 * @param {poly} *a input and output parameter; coefficients are overwritten
 * @return {*}
 */
void polyAddOne(poly *a);

/*** 
 * @description: Subtraction of two polynomials
 * @param {poly} *a input and output parameter; coefficients are overwritten
 * @param {poly} *b a polynomial to subtract from the polynomial a
 * @return {*}
 */
void polySub(poly *a, poly *b);

// Mutilipication

/*** 
 * @description: Multiplies two poly structure modulo `modulus` q.
 * @param {poly} *a a polynomial
 * @param {poly} *b a polynomial
 * @param {poly} *c output parameter; a pointer to store the new polynomial
 * @param {uint64_t} modulus
 * @return {*}
 */
uint64_t polyMultMod(poly *a, poly *b, poly *c, uint64_t modulus);

/*** 
 * @description: Multiplies a polynomial by an scalar integer, modulo another integer
 * @param {poly} *a a polynomial
 * @param {uint64_t} scalarFactor
 * @param {uint64_t} modulus
 * @return {*}
 */
void polyScalarMultMod(poly *a, uint64_t scalarFactor, uint64_t modulus);

// Modular and its inverse

/*** 
 * @description: Reduction modulo a polynomial
 * @param {poly} *p input parameter polynomial
 * @param {poly} *result output polynomial; coefficients are overwritten
 * @param {uint64_t} N the degree of the modular polynomial x^N-1
 * @param {uint64_t} modulus
 * @return {*}
 */
void polyMod(poly *p, poly *result, uint64_t N, uint64_t modulus);


/*** 
 * @description: Computes the multiplicative inverse of a number using the extened Euclidean algorithm 
 * @param {uint64_t} a the input value
 * @param {uint64_t} modulus
 * @return the inverse of a
 */
uint64_t intInverse(uint64_t a, uint64_t modulus);


/*** 
 * @description: Zeros a polynomial and sets the number of coefficients
 * @param {poly} *a
 * @param {uint64_t} N
 * @return {*}
 */
void polyZeroing(poly *a, uint64_t N);

/*** 
 * @description: Copy the coefficients of one polynomial to another
 * @param {poly} *a the source polynomial of that copy
 * @param {poly} *b the destination polynomial of that copy
 * @return {*}
 */
void polyCopy(poly *a, poly *b);

/*** 
 * @description: Tests whether a polynomial has all zero coefficients 
 * @param {poly *} a the input polynomial
 * @return {*}
 */
uint8_t equalsZero(poly *a);

/*** 
 * @description: Returns the degree of a polynomial, returns 0 if such polynomial equals 0. 
 * @param {poly} *a
 * @return the degree of input polynomial.
 */
uint64_t polyDegree(poly *a);

/*** 
 * @description: Reduces a `poly` modulo x^N-1, where N = a->N.
 * @param {poly} *a the input value.
 * @param {poly} *b the output parameter; a pointer to store the reduced polynomial.
 * @param {uint64_t} modulus
 * @return {*}
 */
void polyReduce(poly *a, poly *b, uint64_t modulus);

/*** 
 * @description: Multiplies a polynomial by x^(-1) in (Z/qZ)[x]/[x^p-1] where p=a->N, q=modulus
 * @param {poly} *a input polynomial
 * @param {uint64_t} modulus
 * @return {*}
 */
void polyDivX(poly *a, uint64_t modulus);

/*** 
 * @description: Subtracts b*u from a
 * @param {poly} *a reduced mod after modulus, input polynomial
 * @param {poly} *b another input polynomial
 * @param {uint64_t} u
 * @param {uint64_t} modulus
 * @return {*}
 */
void polySubMult(poly *a, poly *b, uint64_t u, uint64_t modulus);

/*** 
 * @description: Computes the multiplicative inverse of a polynomial in (Z/q)[x]/[x^p-1],
 * where p is given by a->N and q is given by modulus;
 * @param {poly} *a the input value
 * @param {poly} *b output parameter; a pointer to store the inverse polynomial
 * @param {uint64_t} modulus
 * @return 1 if a is invertible, 0 otherwise.
 */
uint8_t polyInverse(poly *a, poly *inv, uint64_t modulus);

/*** 
 * @description: Generation function of polynomial with random coefficients.
 * @param {poly} *a input and output polynomial
 * @param {uint64_t} N polynomial degree
 * @param {uint64_t} modulus q
 * @return {*}
 */
void randPoly(poly *a, uint64_t N, uint64_t modulus);

/*** 
 * @description: Function of telling whether the input polynomial only contains constant coefficient 1.
 * @param {poly} *a
 * @return {*}
 */
uint8_t equalsOne(poly *a);

/*** 
 * @description: Modular operations on coefficients in input poly, return the poly whose coefficients are moduled by `modulus`
 * @param {poly} *a
 * @param {uint64_t} modulus
 * @return {*}
 */
void scalarMod(poly *a, uint64_t modulus);


#endif

