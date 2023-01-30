/*
 * @Author: B1ank
 * @Date: 2022-12-22 17:49:52
 * @LastEditTime: 2023-01-11 00:01:23
 * @LastEditors: your name
 * @Description: The implementation for tests of polynomial operations 
 * @FilePath: /FTCR-LMPPDA/test/testPoly.c
 */

#include <stdlib.h>
#include <stdio.h>
#include "testPoly.h"

uint8_t testIntInverse(){
    uint64_t i;
    uint8_t valid = 1;
    uint64_t q = originModulus;

    for(i=0;i<10;i++){
        uint64_t a = random() % q;
        uint64_t inv = intInverse(a, q);
        valid &= (a*inv) % q == 1;
    }
    printf("Integer inverse operation for q = %d : %s\n", q, valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

uint8_t testPolyInverseMod(uint64_t modulus, uint64_t p){
    uint64_t i;
    uint8_t valid = 1;
    uint8_t inverseFlag;
    for(i=0;i<10;i++){
        poly a,c;
        randPoly(&a, p, modulus);
        inverseFlag = polyInverse(&a, &c, modulus);
        if (inverseFlag == 0){
            printf("No inverse!\n");
            continue;
        }
        else {
            // Inverse of polynomial found
            printf("Polynomial inverse found!\n");
            poly prod;
            polyMultMod(&a, &c, &prod, modulus);
            valid &= equalsOne(&prod);
        }
    }
    return valid;
}

uint8_t testPolyInverse(){
    uint8_t valid = testPolyInverseMod(originModulus, NTRU_N);
    // valid &= testPolyInverseMod(originModulus, NTRU_N);
    printf("Polynomial inverse operation for modulus = %d: %s\n", originModulus, valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}


uint8_t testDataProcessing(){
    // Generation of the number which is less than originModulus
    uint64_t number = random() % originModulus;
    uint8_t valid = 1;
    poly polyForNumber;
    polyZeroing(&polyForNumber, 20);
    // Data Embedding
    originDataEmbedding(&polyForNumber, number, 2);
    // Data Extracting
    valid &= originDataExtraction(&polyForNumber, 2) == number ? 1 : 0;
    printf("Data processing methods(data embedding and extraction) test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}


uint8_t testPolyAdd(){
    // Generation of two different random number which is under the restriction of originModulus
    uint64_t number1 = random() % originModulus;
    uint64_t number2 = random() % originModulus;
    uint8_t valid = 1;
    poly polyForNumber1, polyForNumber2;
    // Zero processing
    polyZeroing(&polyForNumber1, 20);
    polyZeroing(&polyForNumber1, 20);
    // Data Embedding
    originDataEmbedding(&polyForNumber1, number1, 2);
    originDataEmbedding(&polyForNumber2, number2, 2);
    // Polynomial Addition
    polyAdd(&polyForNumber1, &polyForNumber2);
    // Data Extracting
    valid &= originDataExtraction(&polyForNumber1, 2) == (number1+number2) ? 1 : 0;
    printf("Polynomial addition operation test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

uint8_t testPolyMod() {
    uint8_t valid = 1;
    uint64_t number = random() % originModulus;
    poly polyForNumber, modResult;
    // Zero processing
    polyZeroing(&polyForNumber, 20);
    // Data Embedding
    originDataEmbedding(&polyForNumber, number, 2);
    showAllDataEmbedded(&polyForNumber);
    // Suppose we conduct the modular operation on polynomial x^8-1
    polyMod(&polyForNumber, &modResult, 8, originModulus);
    showAllDataEmbedded(&modResult);
    printf("Polynomial modular operation test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}


uint8_t testPolyMult() {
    uint8_t valid = 1;
    uint64_t number = random() % originModulus;
    poly polyForNumber, inv, result, polyForNumberCopy;
    polyZeroing(&inv, 20);
    inv.coeffs[0] = originModulus - 1;
    inv.coeffs[20] = 1;

    polyZeroing(&result, 20);
    polyZeroing(&polyForNumber, 20);

    originDataEmbedding(&polyForNumber, number, 2);
    polyCopy(&polyForNumber, &polyForNumberCopy);
    // Scalar Multiplication
    polyScalarMultMod(&polyForNumber, 7, originModulus);
    valid &= originDataExtraction(&polyForNumber, 2) == 7*number ? 1 : 0;
    printf("Polynomial scalar multipilication operation test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    // Polynomial Multiplication
    printf("Polynomial1 for multiplication:\n");
    showAllDataEmbedded(&polyForNumberCopy);
    printf("Polynomial2 for multiplication:\n");
    showAllDataEmbedded(&inv);
    polyMultMod(&polyForNumberCopy, &inv, &result, originModulus);
    printf("Multiplication result:\n");
    showAllDataEmbedded(&result);
    printf("Polynomial multipilication operation test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}


uint8_t testPoly(){
    uint8_t valid = 1;
    valid &= testDataProcessing();
    valid &= testPolyAdd();
    valid &= testPolyMod();
    valid &= testPolyMult();
    valid &= testIntInverse();
    valid &= testPolyInverse();
    return valid;
}





