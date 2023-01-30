/*** 
 * @Author: B1ank
 * @Date: 2022-12-21 00:04:07
 * @LastEditTime: 2023-01-11 16:56:23
 * @LastEditors: your name
 * @Description: The header definition file for number embedding operations
 * @FilePath: /FTCR-LMPPDA/src/dataEmbedding.h
 */

#ifndef DATA_EMBEDDING_H
#define DATA_EMBEDDING_H

#include <math.h>
#include "poly.h"


/*** 
 * @description: Original data embedding method, no support for specific embedding location
 * @param {poly} *a input and output parameter polynomial
 * @param {uint64_t} origindata original data for embedding in the polynomial
 * @param {uint64_t} system 
 * @return {*}
 */
void originDataEmbedding(poly *a, uint64_t origindata, uint64_t system);


/*** 
 * @description: Data embedding method with the support for specific embedding with the insert parameter `Seq_i`
 * @param {poly} *a input and output parameter polynomial
 * @param {uint64_t} origindata original data for embedding in the polynomial
 * @param {uint64_t} system
 * @param {uint64_t} sequenceNumber embedding location
 * @return {*}
 */
void dataEmbeddingInSequence(poly *a, uint64_t origindata, uint64_t system, uint64_t sequenceNumber);


/*** 
 * @description: Show all the coefficients of the input polynomial, the number of which is totally NTRU_N
 * @param {poly} *a input polynomial
 * @return {*}
 */
void showAllDataEmbedded(poly *a);

/*** 
 * @description: Original data extraction method, providing the extraction support from coefficients of polynomial to decimal number.
 * @param {poly} *a input parameter polynomial
 * @param {uint64_t} system 
 * @return {*}
 */
uint64_t originDataExtraction(poly *a, uint64_t system);


/*** 
 * @description: Data extraction method suitable for PH-NTRUDec algorihtm.
 * @param {poly} *a input parameter polynomial
 * @param {uint64_t} blockSize maximum data bits of each block
 * @param {uint64_t} system
 * @return {uint64_t} aggregation result in decimal type
 */
uint64_t dataExtractionInSequence(poly *a, uint64_t blockLength, uint64_t system);

#endif