/*
 * @Author: B1ank
 * @Date: 2023-01-08 11:35:33
 * @LastEditTime: 2023-01-10 01:09:18
 * @LastEditors: your name
 * @Description: The implementation for tests of Dilithium signature
 * @FilePath: /FTCR-LMPPDA/test/testDilithium.c
 */

#include "testDilithium.h"
#include <string.h>
#include <stdio.h>

/*** 
 * @description: The test function for Dilithium signature for random messages
 * @return {uint8_t} valid flag
 */
uint8_t testDilithiumInRandomMessages(){
    OQS_STATUS rc;
    uint8_t valid = 1;
    keyPair keyPairForDilithium;
    dilithiumSignature signatureResult;
    uint8_t *message = NULL;
    size_t messageLength = MESSAGE_LEN;
    uint8_t *publicKey = NULL;
    uint8_t *privateKey = NULL;
    OQS_SIG *sig = NULL;

    // Initialization process of OQS_SIG object
    sig = OQS_SIG_new(OQS_SIG_alg_dilithium_3);
    if (sig == NULL) {
        printf("OQS_SIG_alg_dilithium_3 was not enabled at compile-time.\n");
        rc = OQS_ERROR;
        valid &= 0;
    }
    printf("Signature object initialization result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Key pair generation
    rc = keypairGeneration(sig, &keyPairForDilithium);
    if (rc != OQS_SUCCESS) {
        // Something error in key pair generation process
        valid &= 0;
    }
    printf("Key pair generation result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Mallocation of space for privateKey and publicKey
    privateKey = malloc(sig->length_secret_key);
    publicKey = malloc(sig->length_public_key);
    if ((privateKey == NULL) || (publicKey == NULL)){
        // Something error in privateKey/publicKey space allocation
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(publicKey, privateKey, NULL, NULL, sig);
        rc = OQS_ERROR;
    }
    if (rc != OQS_SUCCESS) {
        valid &= 0;
    }
    printf("Key pair for distribution result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    memcpy(publicKey, getPubKey(&keyPairForDilithium), sig->length_public_key);
    memcpy(privateKey, getSecKey(&keyPairForDilithium), sig->length_secret_key);
     // Space allocation for message
    message = malloc(messageLength);
    if (message == NULL) {
        // Something error in message space allocation
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(NULL, NULL, message, NULL, sig);
        rc = OQS_ERROR;
    }
    if (rc != OQS_SUCCESS) {
        valid &= 0;
    }
    printf("Message initialization result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Generation of random message
    OQS_randombytes(message, messageLength);
    // Signature process test
    rc = dilithiumSign(sig, message, messageLength, privateKey, &signatureResult);
    if (rc != OQS_SUCCESS) {
        // Something error in signature process in Dilithium
        valid &= 0;
    }
    printf("Dilithium signature result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Verification process test
    rc = dilithiumVerify(sig, message, messageLength, publicKey, &signatureResult);
    if (rc != OQS_SUCCESS) {
        // Something error in verification process in Dilithium
        valid &= 0;
    }
    printf("Dilithium verification result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    cleanupHeap(publicKey, privateKey, message, NULL, sig);
    return valid;
}


/*** 
 * @description: The test function for Dilithium signature for random messages
 * @return {uint8_t} valid flag
 */
uint8_t testDilithiumFailedInRandomMessages(){
    OQS_STATUS rc;
    uint8_t valid = 1;
    keyPair keyPairForDilithium1;
    keyPair keyPairForDilithium2;

    dilithiumSignature signatureResult;
    uint8_t *message = NULL;
    size_t messageLength = MESSAGE_LEN;

    uint8_t *publicKey1 = NULL;
    uint8_t *publicKey2 = NULL;
    
    uint8_t *privateKey1 = NULL;
    uint8_t *privateKey2 = NULL;

    OQS_SIG *sig1 = NULL;
    OQS_SIG *sig2 = NULL;

    // Initialization process of OQS_SIG object
    sig1 = OQS_SIG_new(OQS_SIG_alg_dilithium_3);
    sig2 = OQS_SIG_new(OQS_SIG_alg_dilithium_3);

    if ((sig1 == NULL) || (sig2 == NULL)) {
        printf("OQS_SIG_alg_dilithium_3 was not enabled at compile-time.\n");
        rc = OQS_ERROR;
        valid &= 0;
    }
    printf("Signature object initialization result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Key pair generation
    rc = keypairGeneration(sig1, &keyPairForDilithium1);
    rc = keypairGeneration(sig2, &keyPairForDilithium2);
    if (rc != OQS_SUCCESS) {
        // Something error in key pair generation process
        valid &= 0;
    }
    printf("Key pair generation result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Mallocation of space for privateKeys and publicKeys
    privateKey1 = malloc(sig1->length_secret_key);
    privateKey2 = malloc(sig2->length_secret_key);

    publicKey1 = malloc(sig1->length_public_key);
    publicKey2 = malloc(sig2->length_public_key);

    if ((privateKey1 == NULL) || (publicKey1 == NULL) || (privateKey2 == NULL) || (publicKey2 == NULL)){
        // Something error in privateKey/publicKey space allocation
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(publicKey1, privateKey1, NULL, NULL, sig1);
        cleanupHeap(publicKey2, privateKey2, NULL, NULL, sig2);
        rc = OQS_ERROR;
    }
    if (rc != OQS_SUCCESS) {
        valid &= 0;
    }
    printf("Key pair for distribution result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Operations for key pair 1
    memcpy(publicKey1, getPubKey(&keyPairForDilithium1), sig1->length_public_key);
    memcpy(privateKey1, getSecKey(&keyPairForDilithium1), sig1->length_secret_key);
    // Operations for key pair 2
    memcpy(publicKey2, getPubKey(&keyPairForDilithium2), sig2->length_public_key);
    memcpy(privateKey2, getSecKey(&keyPairForDilithium2), sig2->length_secret_key);

     // Space allocation for message
    message = malloc(messageLength);
    if (message == NULL) {
        // Something error in message space allocation
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(NULL, NULL, message, NULL, sig1);
        rc = OQS_ERROR;
    }
    if (rc != OQS_SUCCESS) {
        valid &= 0;
    }
    printf("Message initialization result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Generation of random message
    OQS_randombytes(message, messageLength);
    // Signature process test
    rc = dilithiumSign(sig1, message, messageLength, privateKey1, &signatureResult);
    if (rc != OQS_SUCCESS) {
        // Something error in signature process in Dilithium
        valid &= 0;
    }
    printf("Dilithium signature result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Verification process test
    rc = dilithiumVerify(sig2, message, messageLength, publicKey2, &signatureResult);
    if (rc != OQS_SUCCESS) {
        // Something error in verification process in Dilithium
        valid &= 0;
    }
    printf("Dilithium verification result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    cleanupHeap(publicKey1, privateKey1, message, NULL, sig1);
    cleanupHeap(publicKey2, privateKey2, NULL, NULL, sig2);
    return valid;
}

/*** 
 * @description: The test function for Dilithium signature for variable of `poly` type
 * @return {uint8_t} valid flag
 */
uint8_t testDilithiumInPolyMessages(){
    OQS_STATUS rc;
    uint8_t valid = 1;
    keyPair keyPairForDilithium;
    dilithiumSignature signatureResult;
    uint8_t *message = NULL;
    size_t messageLength = 64;
    uint8_t *publicKey = NULL;
    uint8_t *privateKey = NULL;
    OQS_SIG *sig = NULL;
    // Initialization process of OQS_SIG object
    sig = OQS_SIG_new(OQS_SIG_alg_dilithium_3);
    if (sig == NULL) {
        printf("OQS_SIG_alg_dilithium_3 was not enabled at compile-time.\n");
        rc = OQS_ERROR;
        valid &= 0;
    }
    printf("Signature object initialization result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Key pair generation
    rc = keypairGeneration(sig, &keyPairForDilithium);
    if (rc != OQS_SUCCESS) {
        // Something error in key pair generation process
        valid &= 0;
    }
    printf("Key pair generation result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Mallocation of space for privateKey and publicKey
    privateKey = malloc(sig->length_secret_key);
    publicKey = malloc(sig->length_public_key);
    if ((privateKey == NULL) || (publicKey == NULL)){
        // Something error in privateKey/publicKey space allocation
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(publicKey, privateKey, NULL, NULL, sig);
        rc = OQS_ERROR;
    }
    if (rc != OQS_SUCCESS) {
        valid &= 0;
    }
    printf("Key pair for distribution result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    memcpy(publicKey, getPubKey(&keyPairForDilithium), sig->length_public_key);
    memcpy(privateKey, getSecKey(&keyPairForDilithium), sig->length_secret_key);
    // Space allocation of message
    message = malloc(messageLength);
    if (message == NULL) {
        // Something error in message space allocation
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(NULL, NULL, message, NULL, sig);
        rc = OQS_ERROR;
    }
    if (rc != OQS_SUCCESS) {
        valid &= 0;
    }
    printf("Message initalization result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    poly randomPoly;
    // Generation of random variable of `poly` type
    randPoly(&randomPoly, NTRU_N, originModulus);
    // Transformation from variable of `poly` type to `uint8_t` type with the length of 512 bits
    memcpy(message, messageMapper(&randomPoly), messageLength);

    // Signature process test
    rc = dilithiumSign(sig, message, messageLength, privateKey, &signatureResult);
    if (rc != OQS_SUCCESS) {
        // Something error in signature process in Dilithium
        valid &= 0;
    }
    printf("Dilithium signature result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    valid = 1;
    // Verification process test
    rc = dilithiumVerify(sig, message, messageLength, publicKey, &signatureResult);
    if (rc != OQS_SUCCESS) {
        // Something error in verification process in Dilithium
        valid &= 0;
    }
    printf("Dilithium verification result: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    cleanupHeap(publicKey, privateKey, message, NULL, sig);
    return valid;
}

/*** 
 * @description: The test function for Dilithium signature
 * @return {uint8_t} valid flag
 */
uint8_t testDilithium(){
    uint8_t valid = 1;
    printf("====Test 1 Dilithium signature for random byte messages====\n");
    valid &= testDilithiumInRandomMessages();
    printf("====Test 2 Dilithium signature for random polynomial====\n");
    valid &= testDilithiumInPolyMessages();
    printf("====Test 3 Dilithium signature verification failed====\n");
    valid &= !testDilithiumFailedInRandomMessages();
    return valid;
}


