/*** 
 * @Author: B1ank
 * @Date: 2023-01-04 15:43:46
 * @LastEditTime: 2023-01-04 15:43:59
 * @LastEditors: B1ank
 * @Description: The header file of test functions for zero sum random generation and distribution
 * @FilePath: /FTCR-LMPPDA/test/testZeroSumRandom.h
 */

#include <stdint.h>
#include "../src/Fisher-YatesShuffle.h"
#include "../src/zeroSumRandomNumber.h"

/*** 
 * @description: The test function for Fisher-Yates shuffle function
 * @return {uint8_t} valid flag
 */
uint8_t testFYS();

/*** 
 * @description: The test function for random number distribution
 * Verifying: whether the sum of all the anti-collusion random numbers distributed among participants equals to zero
 * @return {uint8_t} valid flag
 */
uint8_t testRandomNumberDistribution();

/*** 
 * @description: The test function for random number update
 * Verifying: after the update process, whether the sum of all the new updated random numbers among participants equals to zero
 * @return {uint8_t} valid flag
 */
uint8_t testRandomNumberUpdate();

/*** 
 * @description: The test function for all functions contained in zero-sum random number opeartions
 * @return {uint8_t} valid flag
 */
uint8_t testZeroSumRandomNumber();
