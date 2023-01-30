/*
 * @Author: B1ank
 * @Date: 2022-12-22 19:56:05
 * @LastEditTime: 2023-01-13 22:32:14
 * @LastEditors: your name
 * @Description: The implementation for PH-NTRU algorithm
 * @FilePath: /FTCR-LMPPDA/src/PH-NTRU.c
 */
#include "PH-NTRU.h"

// TODO The existing coding implementation of the PH-NTRU algorithm works normally only for the following range parameters.
// TODO 1. Single dimensional data ranges up to 4
// TODO 2. Aggregate data dimension not excedding 9
// TODO 3. Number of aggregated participants does not exceed 10
// ! TODO Extend the dimensions support of our data aggregation operations from 9 to 10

void keyGeneration(keyPairs *usersKeyPair){
    // Generation of privateKey
    privateKeyGeneration(&usersKeyPair->privateKey);
    // Generation of publicKey
    publicKeyGeneration(&usersKeyPair->publicKey, &usersKeyPair->privateKey);
}

void privateKeyGeneration(poly *privateKey){
    poly fPrime, inv;
    // Zeroing
    polyZeroing(&fPrime, NTRU_N);
    for(;;){
        // Sampling/Resampling
        samplingPolynomials(&fPrime);
        // Calculation of private key f
        polyScalarMultMod(&fPrime, paramP, originModulus);
        // f = p * fPrime + 1
        polyAddOne(&fPrime);
        // Determination of the existence of poly inverse mod q
        if (polyInverse(&fPrime, &inv, originModulus)) {
            // (f mod q) \in R_{q}^{\times}
            // Sampling success
            // printf("Sampling success\n");
            break;
        }
    }
    // Copy from fPrime to privateKey, return privateKey
    polyCopy(&fPrime, privateKey);
}

void publicKeyGeneration(poly *publicKey, poly *privateKey){
    poly fInverse, g, gInv, a;
    // Zeroing
    polyZeroing(&fInverse, NTRU_N);
    polyZeroing(&a, NTRU_N);
    polyZeroing(&g, NTRU_N);
    // Calculation of the inverse of f -> f^(-1)
    polyInverse(privateKey, &fInverse, originModulus);

    // Test1:
    // poly prod;
    // polyMultMod(privateKey, &fInverse, &prod, originModulus);
    // uint8_t verificationResult = equalsOne(&prod);
    // verificationResult = 1;

    // Sampling for polynomial g
    for(;;) {
        // Sampling/Resampling
        samplingPolynomials(&g);
        // Determination of the existence of poly inverse mod q
        if (polyInverse(&g, &gInv, originModulus)) {
            // printf("Sampling success\n");
            break;
        }
    }
    // Calculation of public key
    polyScalarMultMod(&g, paramP, originModulus);
    polyMultMod(&g, &fInverse, &a, originModulus);

    // Test2:
    // poly prod;
    // polyMultMod(&a, privateKey, &prod, originModulus);
    // g == prod
    // We simulate the operation on publicKey a and privateKey f
    // a = pg/f = p*g*f^{-1}
    // a*f = p*g satisfied
    polyCopy(&a, publicKey);
}

uint64_t dataExtraction(poly *superpositionResult){
    // Data extraction, return the AggD 
    return dataExtractionInSequence(superpositionResult, blockSize, 2);
}

void dataEmbedding(uint64_t originalData, poly *r, uint64_t sequence){
    // Data embedding according to the sequence number input, finally get `poly *r` as M_{i}
    dataEmbeddingInSequence(r, originalData, 2, sequence);
}

void encryption(uint64_t originData, poly *publicKey, uint64_t sequence, poly *ciphertext){
    poly message, s, e, cipher;
    poly multiplicationResult;
    polyZeroing(&message, NTRU_N);
    polyZeroing(&cipher, NTRU_N);
    polyZeroing(&multiplicationResult, NTRU_N);

    polyZeroing(&s, NTRU_N);
    polyZeroing(&e, NTRU_N);
    // Data Embedding
    dataEmbedding(originData, &message, sequence);
    // Sampling from DGS
    samplingPolynomials(&s);
    samplingPolynomials(&e);
    polyMultMod(publicKey, &s, &multiplicationResult, originModulus);
    // C = 0 + as
    polyAdd(&cipher, &multiplicationResult);
    // f*p*e
    polyScalarMultMod(&e, paramP, originModulus);
    // C = C + p*e
    polyAdd(&cipher, &e);
    // C = C + M
    polyAdd(&cipher, &message);
    polyCopy(&cipher, ciphertext);
}

void homomorphicAdd(poly *ciphertext1, poly *ciphertext2){
    // ciphertext1 = ciphertext1 + ciphertext2
    polyAdd(ciphertext1, ciphertext2);
}

uint64_t decryption(poly *aggregatedCiphertext, poly *privateKey){
    poly CPrime;
    uint64_t aggregationResult;
    polyZeroing(&CPrime, NTRU_N);
    // CPrime = f*C mod q
    polyMultMod(aggregatedCiphertext, privateKey, &CPrime, originModulus);
    // AC = CPrime mod p
    scalarMod(&CPrime, paramP);
    // Transformation from the coefficients of polynomial to the final decryption result
    aggregationResult = dataExtractionInSequence(&CPrime, blockSize, 2);
    return aggregationResult;
}