/*** 
 * @Author: B1ank
 * @Date: 2022-12-26 00:00:00
 * @LastEditTime: 2023-01-10 15:03:49
 * @LastEditors: your name
 * @Description: The header definition file for CRYSTALS-Dilithium signature algorithms with the help of functions provided in open-quantum-safe/liboqs
 * @FilePath: /FTCR-LMPPDA/src/Dilithium.h
 */
#ifndef DILITHIUM_H
#define DILITHIUM_H

// We choose Dilithium3 to ensure the SUF-CMA of chosen signature algorithm
// Signature based on heap are utilized

#include <oqs/oqs.h>
#include <oqs/sig.h>
#include "poly.h"
#include "fips202.h"
#include "params.h"

/*** 
 * @description: Definition of structure named `poly` containing the polynomial coefficients array `coeffs` and its degree `N`
 * @return {*}
 */
typedef struct {
    uint8_t publicKey[publicKeyLengthForDilithium];
    uint8_t privateKey[privateKeyLengthForDilithium];
} keyPair;

typedef struct {
    uint8_t signature[signatureLengthForDilithium];
    size_t signatureLength;
} dilithiumSignature;


/*** 
 * @description: Cleaning up memory operation in heap utilized in Dilithium signature
 * @param {uint8_t*} publicKey
 * @param {uint8_t*} secretKey
 * @param {uint8_t*} message
 * @param {uint8_t*} signature
 * @param {OQS_SIG*} sig whether the generic OQS_SIG object returned is not NULL should be checked
 * @return {*}
 */
void cleanupHeap(uint8_t *publicKey, uint8_t *secretKey, 
                 uint8_t *message, uint8_t *signature,
                 OQS_SIG *sig);

/*** 
 * @description: Finish the key pair generation process for Dilithium3, the public key and the private key are stored in the structure `keyPair`
 * @param {OQS_SIG} *sig
 * @param {keyPair} keyPairForDilithium the structure to store public and secret keys for Dilithium3
 * @return {uint8_t} OQS_ERROR or OQS_SUCCESS
 */
uint8_t keypairGeneration(OQS_SIG *sig, keyPair *keyPairForDilithium);

/*** 
 * @description: Return the array of `uint8_t` type indicating `publicKey` from the `keyPair` structure object
 * @param {keyPair} *keyPairForDilithium
 * @return {uint8_t*} array for publicKey
 */
uint8_t* getPubKey(keyPair *keyPairForDilithium);

/*** 
 * @description: Return the array of `uint8_t` type indicating `secretKey` from the `keyPair` structure object
 * @param {keyPair} *keyPairForDilithium
 * @return {uint8_t*} array for secretKey
 */
uint8_t* getSecKey(keyPair *keyPairForDilithium);

/*** 
 * @description: The wrapper function of the sign operation in Dilithium
 * @param {OQS_SIG} *sig OQS_SIG object for sign operation
 * @param {uint8_t} *message original message input as ciphertext
 * @param {size_t} messageLength the length of original message
 * @param {uint8_t} *secretKey privateKey in Dilithium signature
 * @param {dilithiumSignature} *signatureResult structure with the type `dilithiumSignature`, which contains `uint8_t*` signature and `size_t` signatureLength
 * @return {uint8_t} OQS_ERROR or OQS_SUCCESS
 */
uint8_t dilithiumSign(OQS_SIG *sig, uint8_t *message, size_t messageLength, uint8_t *secretKey, dilithiumSignature *signatureResult);

/*** 
 * @description: The wrapper function of the verify function
 * @param {OQS_SIG} *sig OQS_SIG object for verify operation
 * @param {uin8_t} *message original message received as ciphertext
 * @param {size_t} messageLength the length of original message
 * @param {uint8_t} *publicKey publicKey in Dilithium signature
 * @param {dilithiumSignature} *signatureResult structure with the type `dilithiumSignature`
 * @return {uint8_t} OQS_ERROR or OQS_SUCCESS
 */
uint8_t dilithiumVerify(OQS_SIG *sig, uint8_t *message, size_t messageLength, uint8_t *publicKey, dilithiumSignature *signatureResult);

/*** 
 * @description: The message mapper function to transform the ciphertext from type `poly` to type `uint8_t*`
 * @param {poly} *ciphertext
 * @return {uint8_t*} Transformed result, which should be utilized in Dilithium signature
 */
uint8_t* messageMapper(poly *ciphertext);

#endif 
