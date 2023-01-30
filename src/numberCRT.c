/*
 * @Author: B1ank
 * @Date: 2022-12-22 22:46:28
 * @LastEditTime: 2023-01-15 22:28:58
 * @LastEditors: your name
 * @Description: The implementation for numberCRT oeprations
 * @FilePath: /FTCR-LMPPDA/src/numberCRT.c
 */

#include <math.h>
#include "numberCRT.h"

int64_t isPrime(int64_t x){
    int64_t sq = sqrt(x);
    if(x <= 1) return 0;
    for(int i=2;i<=sq;i++){
        if(x%i == 0) {
            return 0;
        }
    }
    return 1;
}

int64_t* primesGeneration(int16_t n, int16_t dMax){
    int16_t upperBound = n*dMax;
    static int64_t qArr[dimensionNumber];
    int index = 0;
    for(int possiblePrime=upperBound+1;;possiblePrime++){
        if(index >= dimensionNumber){
            break;
        }
        // If input possiblePrime is indeed prime
        if(isPrime(possiblePrime) == 1){
            qArr[index] = possiblePrime;
            // printf("Primes: %d\n", qArr[index]);
            index++;
        }
    }
    return qArr;
}

int64_t primesMultiplication(int64_t* primeArr){
    int64_t primesMultiplicationResult = 1;
    for(int index=0;index<dimensionNumber;index++){
        primesMultiplicationResult *= primeArr[index];
    }
    return primesMultiplicationResult;
}

int64_t modInverse(int64_t a, int64_t modulus){
    int64_t x = 0;
    int64_t lastx = 1;
    int64_t y = 1;
    int64_t lasty = 0;
    int64_t b = modulus;
    while (b != 0) {
        int64_t quotient = a / b;
        int64_t temp = a;
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

// numberCRT initialization
void numberCRTInit(int64_t* primeArr, primeBlock* pB){
    // Zeroing the alphaArr list for pB
    for(int j=0;j<dimensionNumber;j++){
        pB->alphaArr[j] = 0;
    }
    int64_t Q = primesMultiplication(primeArr);
    int64_t QIndex, QIndexInverse, qIndex;
    for(int index=0;index<dimensionNumber;index++) {
        qIndex = primeArr[index];
        QIndex = Q / qIndex;
        QIndexInverse = modInverse(QIndex, qIndex);
        pB->alphaArr[index] = QIndex * QIndexInverse;
        pB->qArr[index] = qIndex; 
    }
    pB->primesMultiplicationResult = Q;
}

// numberCRT data process
int64_t numberCRTDP(int64_t* dataVector, primeBlock* pB){
    int64_t transformedResult = 0;
    
    // TODO Import Miracl library to achieve the operations on large number
    // TODO As the type of variable `finalAggregatedResult` is int64_t, the range of which is restricted between 0~2^{64}-1, 
    // TODO therefore when there are more data dimensions or aggregation participants, the calculation of aggregation results is prone to overflow
    // TODO So we restrict the participantsNumber, dimensionNumber and  upperBoundOfEachDimension as 10, 5, 16 respectively.
    
    for(int index=0; index<dimensionNumber;index++) {
        transformedResult += dataVector[index] * pB->alphaArr[index];
        // printf("dataVector: %d, alphaArr: %d\n", dataVector[index], alphaArr[index]);
    }
    transformedResult += pB->primesMultiplicationResult;
    transformedResult %= pB->primesMultiplicationResult;
    // printf("Transformed result: %lld\n", transformedResult);
    return transformedResult;
}

// numberCRT data recovery
int64_t* numberCRTDR(int64_t aggregatedData, primeBlock* pB){
    static int64_t recoveryResult[dimensionNumber];

    for(int index=0;index<dimensionNumber;index++){
        recoveryResult[index] = aggregatedData % pB->primesMultiplicationResult % pB->qArr[index];
    }

    return recoveryResult;
}