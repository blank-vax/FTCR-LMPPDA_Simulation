/*
 * @Author: B1ank
 * @Date: 2022-12-25 15:58:40
 * @LastEditTime: 2022-12-25 23:48:58
 * @LastEditors: your name
 * @Description: The implementation for tests of number Chinese Remainder Theorem
 * @FilePath: /FTCR-LMPPDA/test/testNumberCRT.c
 */
#include <stdio.h>
#include "testNumberCRT.h"

uint8_t testIsPrime() {
    uint8_t valid = 1;
    int64_t numberForTest[10] = {3203, 3325, 3517, 4010, 4515, 4850, 5171, 6000, 6529, 7523};

    // Standard answer array
    int64_t answerArr[10] = {1, 0, 1, 0, 0, 0, 1, 0, 1, 1};

    // Test for isPrime() function
    for(int index = 0;index < 10; index++) {
        valid &= isPrime(numberForTest[index]) == answerArr[index] ? 1 : 0;
    }
    printf("Vegetarian test function result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}


uint8_t testPrimesGeneration() {
    int index;
    uint8_t valid = 1;
    int64_t* primesArr;
    primesArr = primesGeneration(participantsNumber, upperBoundOfEachDimension);
    // Print the prime list
    printf("All generated primes are listed as below:\n"); 
    for(index=0;index<dimensionNumber;index++) {
        printf("%d|", primesArr[index]);
    }
    printf("\n");
    // Judgement of the vegetarian of the generated primes
    for(index=0;index<dimensionNumber;index++) {
        valid &= isPrime(primesArr[index]) == 1 ? 1: 0;
    }
    printf("Primes generation test result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

uint8_t testPrimeMultiplication(){
    // Generation of the prime list
    uint8_t valid = 1;
    int64_t* primesArr;
    int64_t multiplicationResult;
    primesArr = primesGeneration(10, 10);
    multiplicationResult = primesMultiplication(primesArr);
    valid &= multiplicationResult > 0 ? 1 : 0;
    printf("Primes multiplication test result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

uint8_t testModInverse(){
    int index;
    uint8_t valid = 1;
    int64_t q = originModulus;
    for(index=0;index<10;index++) {
        int64_t a = random() % q;
        int64_t inv = modInverse(a, q);
        valid &= (a*inv) % q == 1;
    }
    printf("Integer modular inverse operation for q = %d : %s\n", q, valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

uint8_t testNumberCRT(){
    uint8_t valid = 1;
    valid &= testIsPrime();
    valid &= testPrimesGeneration();
    valid &= testPrimeMultiplication();
    valid &= testModInverse();
    // Generation of 100 x 10 matrix consisting of random number less than 16
    int i, j, index;
    int64_t randomMatrix[participantsNumber][dimensionNumber] = {{0}};
    
    for(i=0;i<participantsNumber;i++) {
        for(j=0;j<dimensionNumber;j++) {
            randomMatrix[i][j] = random() % upperBoundOfEachDimension;
        }
    }
    // Initialization of numberCRT
    int64_t* primesArr;
    primeBlock pB;
    // Zeroing
    for(index = 0;index < dimensionNumber; index++) {
        pB.alphaArr[index] = 0;
    }
    primesArr = primesGeneration(participantsNumber, upperBoundOfEachDimension);
    numberCRTInit(primesArr, &pB);

    // Data process utilizing numberCRT
    int64_t finalAggregatedResult = 0;

    for(i=0;i<participantsNumber;i++) {
        finalAggregatedResult += numberCRTDP(randomMatrix[i], &pB);
    }

    finalAggregatedResult = (finalAggregatedResult + pB.primesMultiplicationResult) % pB.primesMultiplicationResult;
    // Data recovery utilizing numberCRT
    int64_t* recoveryResult;
    int64_t aggregatedResult;
    recoveryResult = numberCRTDR(finalAggregatedResult, &pB);
    for(j=0;j<dimensionNumber;j++) {
        aggregatedResult = 0;
        for(i=0;i<participantsNumber;i++) {
            aggregatedResult += randomMatrix[i][j];
        }
        // printf("%d, %d\n", recoveryResult[j], aggregatedResult);
        valid &= recoveryResult[j] == aggregatedResult ? 1 : 0;
    }
    printf("Whole process of numberCRT test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}
