/*
 * @Author: B1ank
 * @Date: 2022-12-26 00:00:07
 * @LastEditTime: 2023-01-10 00:54:03
 * @LastEditors: your name
 * @Description: The implementation of Dilithium signature
 * @FilePath: /FTCR-LMPPDA/src/Dilithium.c
 */
#include <stdio.h>
#include <string.h>
#include "Dilithium.h"

void cleanupHeap(uint8_t *publicKey, uint8_t *secretKey, uint8_t *message, uint8_t *signature, OQS_SIG *sig){
    if (sig != NULL) {
        OQS_MEM_secure_free(secretKey, sig->length_secret_key);
    }

    // Securely or insecurely free the space of `ptr` which could be utilized facing the circumstance that `ptr = NULL`, in which no operation
    // is performed
    OQS_MEM_insecure_free(publicKey);
    OQS_MEM_insecure_free(message);
    OQS_MEM_insecure_free(signature);
    // TODO Figure out the reason why the use of `OQS_SIG_free(sig)` operation would throw up the error: free(): double free detected in tcache 2
    // OQS_SIG_free(sig);
}

uint8_t keypairGeneration(OQS_SIG *sig, keyPair *keyPairForDilithium){
    uint8_t *publicKey = NULL;
    uint8_t *secretKey = NULL;
    OQS_STATUS rc;
    // Space mallocation in heap
    publicKey = malloc(sig->length_public_key);
    secretKey = malloc(sig->length_secret_key);
    if((publicKey == NULL) || (secretKey == NULL)) {
        // Something error in mallocation operations
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(publicKey, secretKey, NULL, NULL, sig);
        rc = OQS_ERROR;
    }
    rc = OQS_SIG_keypair(sig, publicKey, secretKey);
    if (rc != OQS_SUCCESS) {
        // Something error in key pair generation process
        fprintf(stderr, "ERROR: OQS_SIG_keypair failed!\n");
        cleanupHeap(publicKey, secretKey, NULL, NULL, sig);
    }
    // Replace the (publicKey=NULL, privateKey=NULL) in variable `keyPairForDilithium` with (publicKey, secretKey) 
    memcpy(keyPairForDilithium->privateKey, secretKey, sig->length_secret_key);
    memcpy(keyPairForDilithium->publicKey, publicKey, sig->length_public_key);
    // Cleanup in heap
    cleanupHeap(publicKey, secretKey, NULL, NULL, sig);
    return rc;
}

uint8_t* getPubKey(keyPair *keyPairForDilithium){
    if (keyPairForDilithium->privateKey == NULL) {
        printf("Something error\n");
    }
    return keyPairForDilithium->publicKey;
}

uint8_t* getSecKey(keyPair *keyPairForDilithium){
    return keyPairForDilithium->privateKey;
}

uint8_t dilithiumSign(OQS_SIG *sig, uint8_t *message, size_t messageLength, uint8_t *secretKey, dilithiumSignature *signatureResult){
    uint8_t *signature = NULL;
    size_t signatureLength;
    uint8_t rc;
    // Space mallocation for signature
    signature = malloc(sig->length_signature);
    if ((message == NULL) || (signature == NULL)) {
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(NULL, secretKey, message, signature, sig);
        rc = OQS_ERROR;
    }
    rc = OQS_SIG_sign(sig, signature, &signatureLength, message, messageLength, secretKey);
    if (rc != OQS_SUCCESS) {
        fprintf(stderr, "ERROR: OQS_SIG_sign failed!\n");
        cleanupHeap(NULL, secretKey, message, signature, sig);
    }
    // Signature generation success
    memcpy(&signatureResult->signature, signature, signatureLength);
    signatureResult->signatureLength = signatureLength;
    // // Cleanup in heap
    // cleanupHeap(NULL, NULL, NULL, signature, sig);
    return rc;
}

uint8_t dilithiumVerify(OQS_SIG *sig, uint8_t *message, size_t messageLength, uint8_t *publicKey, dilithiumSignature *signatureResult){
    OQS_STATUS rc;
    rc = OQS_SIG_verify(sig, message, messageLength, signatureResult->signature, signatureResult->signatureLength, publicKey);
    if (rc != OQS_SUCCESS) {
        fprintf(stderr, "ERROR: OQS_SIG_verify failed!\n");
    }
    return rc;
}

uint8_t* messageMapper(poly *ciphertext){
    // Transform algorithm from variable ciphertext of type `poly*` to `uint8_t*` array
    uint8_t *ciphertextAsChar;
    static uint8_t hashesOfCiphertext[NTRU_N];
    ciphertextAsChar = malloc(NTRU_N);
    memcpy(ciphertextAsChar, &ciphertext->coeffs, NTRU_N);
    // Hash operation on ciphertext, results of which stores in variable `hashesOfCiphertext`, which is utilized as original data for Dilithium signature
    sha3_512(hashesOfCiphertext, ciphertextAsChar, NTRU_N);
    return hashesOfCiphertext;
}