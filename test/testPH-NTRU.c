/*
 * @Author: B1ank
 * @Date: 2023-01-12 00:37:52
 * @LastEditTime: 2023-01-13 23:08:19
 * @LastEditors: your name
 * @Description: The implementation for tests of PH-NTRU homomorphic algorithm
 * @FilePath: /FTCR-LMPPDA/test/testPH-NTRU.c
 */

#include "testPH-NTRU.h"
#include <math.h>
#include <stdio.h>

/*** 
 * @description: The test function for PH-NTRU encryption and decryption 
 * @return {uint8_t} valid flag
 */
uint8_t testPHNTRUEncAndDec() {
    // Initialization for key pair structure
    keyPairs keyPairsForPHNTRU;
    poly publicKey, privateKey, ciphertext;
    uint64_t decryptionResult = 0;
    uint8_t valid = 1;
    uint64_t testData = random() % upperBoundOfEachDimension;
    polyZeroing(&publicKey, NTRU_N);
    polyZeroing(&privateKey, NTRU_N);
    polyZeroing(&ciphertext, NTRU_N);

    polyCopy(&publicKey, &keyPairsForPHNTRU.publicKey);
    polyCopy(&privateKey, &keyPairsForPHNTRU.privateKey);
    // Key generation process
    keyGeneration(&keyPairsForPHNTRU);
    // Encryption process
    encryption(testData, &keyPairsForPHNTRU.publicKey, 0, &ciphertext);
    // Decryption process
    decryptionResult = decryption(&ciphertext, &keyPairsForPHNTRU.privateKey);
    printf("Decryption result: %d\n", decryptionResult);
    // Decryption correctness verification
    if (testData != decryptionResult) {
        // Failed
        valid &= 0;
    }
    printf("PH-NTRU encryption and decryption for single multiple data result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

/*** 
 * @description: The test function for PH-NTRU homomorphism
 * @return {uint8_t} valid flag
 */
uint8_t testPHNTRUHomorphism() {
    // Initialization for key pair structure
    int index;
    keyPairs keyPairsForPHNTRU;
    poly publicKey, privateKey, ciphertext;
    // Zeroing for ciphertexts
    poly ciphertexts[participantsNumber];
    memset(ciphertexts, 0, sizeof(poly)*participantsNumber);
    for(index = 0;index < participantsNumber;index++) {
        polyZeroing(&ciphertexts[index], NTRU_N);
    }
    uint64_t decryptionResult = 0, testDataSum = 0;
    uint8_t valid = 1;
    // Initalization for test dataset
    uint64_t testDataSet [participantsNumber] = {0};
    for(index = 0; index < participantsNumber; index++) {
        // Construction of random number dataset
        testDataSet[index] = random() % upperBoundOfEachDimension;
        printf("Data for user %d: %d\n", index, testDataSet[index]);
        testDataSum += testDataSet[index];
    }
    printf("The summation of test data: %d\n", testDataSum);
    polyZeroing(&publicKey, NTRU_N);
    polyZeroing(&privateKey, NTRU_N);
    polyZeroing(&ciphertext, NTRU_N);
    polyCopy(&publicKey, &keyPairsForPHNTRU.publicKey);
    polyCopy(&privateKey, &keyPairsForPHNTRU.privateKey);
    // Key generation process
    keyGeneration(&keyPairsForPHNTRU);
    // Encryption process
    // Generation of total 10 
    for (index = 0; index < participantsNumber; index++) {
        encryption(testDataSet[index], &keyPairsForPHNTRU.publicKey, index*blockSize, &ciphertexts[index]);
    }
    // Homomorphic addition
    for (index = 1; index < participantsNumber; index++) {
        homomorphicAdd(&ciphertexts[0], &ciphertexts[index]);
    }
    // Decryption process
    decryptionResult = decryption(&ciphertexts[0], &keyPairsForPHNTRU.privateKey);
    printf("Decryption result: %d\n", decryptionResult);
    // Decryption correctness verification
    if (testDataSum != decryptionResult) {
        // Failed
        valid &= 0;
    }
    printf("PH-NTRU homomorphic property verification result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

/*** 
 * @description: The test function for the support for multidimensional data for PH-NTRU algorithm
 * @return {uint8_t} valid flag
 */
uint8_t testPHNTRUForMultidimensionData() {
    // Initialization for key pair structure
    int index;
    keyPairs keyPairsForPHNTRU;
    poly publicKey, privateKey, ciphertext;
    int64_t *primesArr;
    primeBlock pB;
    int64_t processedData = 0;
    int64_t *recoveryResult;

    // Zeroing for ciphertexts
    poly ciphertexts[participantsNumber];
    memset(ciphertexts, 0, sizeof(poly)*participantsNumber);
    for(index = 0;index < participantsNumber;index++) {
        polyZeroing(&ciphertexts[index], NTRU_N);
    }
    uint64_t decryptionResult = 0;
    uint8_t valid = 1;
    uint64_t testDataSum[dimensionNumber] = {0};
    // There are total 10 participants, each collects the 10-dimensions random data less than 4
    uint64_t testDataSet [participantsNumber][dimensionNumber] = {0};
    // Initalization for test dataset
    for(int i = 0;i < participantsNumber;i++) {
        for (int j = 0;j < dimensionNumber;j++) {
            testDataSet[i][j] = random() % upperBoundOfEachDimension;
        }
    }
    // Sum results of each dimension
    for(int i = 0;i < dimensionNumber;i++) {
        for(int j = 0; j < participantsNumber;j++) {
           testDataSum[i] += testDataSet[j][i];
        }
    }
    polyZeroing(&publicKey, NTRU_N);
    polyZeroing(&privateKey, NTRU_N);
    polyZeroing(&ciphertext, NTRU_N);
    polyCopy(&publicKey, &keyPairsForPHNTRU.publicKey);
    polyCopy(&privateKey, &keyPairsForPHNTRU.privateKey);
    // Key generation process
    keyGeneration(&keyPairsForPHNTRU);
    // numberCRT transform process
    // Zeroing for numberCRT
    for(index = 0; index < dimensionNumber; index++) {
        pB.alphaArr[index] = 0;
    }
    // Init for numberCRT
    primesArr = primesGeneration(participantsNumber, upperBoundOfEachDimension);
    numberCRTInit(primesArr, &pB);
    // Data process for numberCRT
    // Encryption
    for(int i = 0; i < participantsNumber;i++) {
        processedData = numberCRTDP(testDataSet[i], &pB);
        encryption(processedData, &keyPairsForPHNTRU.publicKey, i*blockSize, &ciphertexts[i]);
    }
    // Homomorphic addition
    for(int j = 1; j < participantsNumber;j++) {
        homomorphicAdd(&ciphertexts[0], &ciphertexts[j]);
    }

    // Decryption process
    decryptionResult = decryption(&ciphertexts[0], &keyPairsForPHNTRU.privateKey);
    // printf("Decryption result: %d\n", decryptionResult);
    // Data recovery for numberCRT
    recoveryResult = numberCRTDR(decryptionResult, &pB);
    // Decryption correctness verification
    for(int k = 0;k < dimensionNumber; k++) {
        printf("recovery result: %d | test data summation: %d\n", recoveryResult[k], testDataSum[k]);
        valid &= recoveryResult[k] == (int64_t)testDataSum[k];
    }
    printf("The support for multidimensional data of PH-NTRU: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

/*** 
 * @description: The test function for PH-NTRU algorithm
 * @return {uint8_t} valid flag
 */
uint8_t testPHNTRU() {
    uint8_t valid = 1;
    valid &= testPHNTRUForMultidimensionData();
    valid &= testPHNTRUEncAndDec();
    valid &= testPHNTRUHomorphism();
    // uint8_t valid = testPHNTRUForMultidimensionData();
    return valid;
}
