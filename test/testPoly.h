/*** 
 * @Author: B1ank
 * @Date: 2022-12-22 17:49:59
 * @LastEditTime: 2022-12-25 18:52:03
 * @LastEditors: your name
 * @Description: The header file of test functions for polynomial operations
 * @FilePath: /FTCR-LMPPDA/test/testPoly.h
 */

#include <stdint.h>
#include "../src/dataEmbedding.h"

/*** 
 * @description: The test function for integer inverse operation
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testIntInverse();

/*** 
 * @description: Test function for polynomial inverse operation with modulus and p as 
 * @param {uint64_t} modulus
 * @param {uint64_t} p
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testPolyInverseMod(uint64_t modulus, uint64_t p);

/*** 
 * @description: Test function for polynomial inverse operation
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testPolyInverse();

/*** 
 * @description: Function containing all test functions.
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testPoly();


/*** 
 * @description: Test function for the accuracy of data embedding and extraction between number and coefficients of polynomial.
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testDataProcessing();

/*** 
 * @description: Test function for the subtraction and addition operations of input two polynomials.
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testPolyAdd();

/*** 
 * @description: Test function for polynomial modular operations
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testPolyMod();

/*** 
 * @description: Test function for polynomial multiplication operations.
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testPolyMult();
