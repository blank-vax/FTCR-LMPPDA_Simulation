/*** 
 * @Author: B1ank
 * @Date: 2022-12-22 22:46:22
 * @LastEditTime: 2022-12-25 23:34:50
 * @LastEditors: B1ank
 * @Description: The header definition file for Chinese Remainder Theorem for number
 * @FilePath: /FTCR-LMPPDA/src/numberCRT.h
 */

#ifndef NUMBER_CRT_H
#define NUMBER_CRT_H

#include <stdint.h>
#include <stdlib.h>
#include "params.h"

typedef struct {
    int64_t qArr[dimensionNumber];
    int64_t alphaArr[dimensionNumber];
    int64_t primesMultiplicationResult;
} primeBlock;


/*** 
 * @description: Subfunction to determine whether the input number x is prime or not
 * @param {int64_t} x
 * @return {int64_t} judgment results, return 1 if x is prime and 0 otherwise
 */
int64_t isPrime(int64_t x);

/*** 
 * @description: Generation of prime numbers with the number of dimensionCount
 * Attention: each prime number q should satisfy q > n*dMax
 * @param {int16_t} n the number of participants in aggregation
 * @param {int16_t} dMax the upper limit of each dimension of user's metering data
 * @return {int64_t} prime array generated under the restriction of q > n*dMax
 */
int64_t* primesGeneration(int16_t n, int16_t dMax);

/*** 
 * @description: Multiplication result of input prime array
 * @param {int64_t*} primeArr input prime array
 * @return {int64_t} multiplication result of input primes
 */
int64_t primesMultiplication(int64_t* primeArr);


/*** 
 * @description: Mod inverse result r satisfying a*r = 1 mod b
 * @param {int64_t} a 
 * @param {int64_t} b modulus
 * @return {int64_t} modulus inverse result
 */
int64_t modInverse(int64_t a, int64_t modulus);


/*** 
 * @description: Initialization process for numberCRT
 * @param {int64_t*} primeArr
 * @param {primeBlock} *pB input primeBlock object for initalization process
 * @return {*}
 */
void numberCRTInit(int64_t* primeArr, primeBlock *pB);

/*** 
 * @description: Data process for numberCRT
 * @param {int64_t*} dataVector input data vector
 * @param {int64_t*} alphaArr alphaArr vector for data process
 * @return {int64_t} data transform result s_{i} 
 */
int64_t numberCRTDP(int64_t* dataVector, primeBlock* pB);

/*** 
 * @description: Data recovery for numberCRT
 * @param {int64_t} aggregatedData aggregated data result S=s_{1}+s_{2}+...+s_{w}
 * @param {primeBlock*} pB 
 * @return {int64_t*} aggregation result for each dimension (ad_{1},ad_{2},...ad_{})
 */
int64_t* numberCRTDR(int64_t aggregatedData, primeBlock* pB);

#endif