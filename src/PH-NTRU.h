/*** 
 * @Author: B1ank
 * @Date: 2022-12-22 19:56:05
 * @LastEditTime: 2023-01-13 14:43:09
 * @LastEditors: your name
 * @Description: The header definition file for the whole process of our designed PH-NTRU algorithm
 * @FilePath: /FTCR-LMPPDA/src/PH-NTRU.h
 */

#ifndef PH_NTRU_H
#define PH_NTRU_H

#include "params.h"
#include "dataEmbedding.h"
#include "gaussianSampling.h"

/*** 
 * @description: Definition of structure named `keyPairs` containing two variables of `poly` type - privateKey and publicKey
 * @return {*}
 */
typedef struct {
    poly privateKey;
    poly publicKey;
} keyPairs;

/*** 
 * @description: Generation of the key pairs of PH-NTRU algorithm
 * @param {keyPairs} *usersKeyPair structure contains the public key and private key of the user
 * @return {*}
 */
void keyGeneration(keyPairs *usersKeyPair);

/*** 
 * @description: Generation of the private key of PH-NTRU algorithm
 * @param {poly} *privateKey
 * @return {*}
 */
void privateKeyGeneration(poly *privateKey);

/*** 
 * @description: Generation of the public key of PH-NTRU algorithm
 * @param {poly} *publicKey
 * @param {poly} *privateKey
 * @return {*}
 */
void publicKeyGeneration(poly *publicKey, poly *privateKey);

/*** 
 * @description: Encryption algorithm of PH-NTRU algorithm
 * @param {uint64_t} originData data processed with CRT and masking operation
 * @param {poly} *publicKey public key of PH-NTRU algorithm
 * @param {uint64_t} sequence the sequence number of user, in other words, the insert location of each user
 * @param {poly} *ciphertext ciphertext of PH-NTRU algorithm
 * @return {*}
 */
void encryption(uint64_t originData, poly *publicKey, uint64_t sequence, poly *ciphertext);

/*** 
 * @description: Homomorphic addition algorithm for two ciphertexts of PH-NTRU algorithm with the type of `poly`
 * @param {poly} *ciphertext1 ciphertext1, also the variable for addition results
 * @param {poly} *ciphertext2
 * @return {*}
 */
void homomorphicAdd(poly *ciphertext1, poly *ciphertext2);

/*** 
 * @description: Decryption algorithm of PH-NTRU algorithm
 * @param {poly} *aggregatedCiphertext aggregated ciphertexts
 * @param {poly} *privateKey private key of PH-NTRU algorithm
 * @return {uint64_t} the decimal aggregation results after superposition summation according to blockSize
 */
uint64_t decryption(poly *aggregatedCiphertext, poly *privateKey);

/*** 
 * @description: Data extraction function which achieve coefficients superposition summation
 * @param {poly} *superpositionResult
 * @return {aggregationResult}
 */
uint64_t dataExtraction(poly *superpositionResult);

/*** 
 * @description: Data embedding function which achieve coefficients insert
 * @param {uint64_t} originalData
 * @param {poly} *r
 * @param {uint64_t} sequence
 * @return {*}
 */
void dataEmbedding(uint64_t originalData, poly *r, uint64_t sequence);

#endif