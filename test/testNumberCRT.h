/*** 
 * @Author: B1ank
 * @Date: 2022-12-25 15:58:34
 * @LastEditTime: 2022-12-25 18:52:00
 * @LastEditors: your name
 * @Description: The header file of test functions for number Chinese Remainder Theorem
 * @FilePath: /FTCR-LMPPDA/test/testNumberCRT.h
 */

#include <stdint.h>
#include <math.h>
#include "../src/numberCRT.h"

/*** 
 * @description: The test function for prime determination
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testIsPrime();

/*** 
 * @description: Test function for primes generation 
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testPrimesGeneration();

/*** 
 * @description: Test function for primes multiplication operation
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testPrimeMultiplication();

/*** 
 * @description: Test function for integer inverse operation
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testModInverse();

/*** 
 * @description: Execution and equality verification of numberCRT process
 * @return {uint8_t} testResult, 1 for passed while 0 for failed
 */
uint8_t testNumberCRT();

