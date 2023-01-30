/*** 
 * @Author: B1ank
 * @Date: 2023-01-08 11:35:27
 * @LastEditTime: 2023-01-08 11:35:53
 * @LastEditors: B1ank
 * @Description: The header file of test functions for Dilithium signature
 * @FilePath: /FTCR-LMPPDA/test/testDilithium.h
 */

#include "../src/Dilithium.h"
#include "../src/poly.h"

#define MESSAGE_LEN 128;

/*** 
 * @description: The test function for Dilithium signature for random messages
 * @return {uint8_t} valid flag
 */
uint8_t testDilithiumInRandomMessages();

/*** 
 * @description: The test function for Dilithium signature for variable of `poly` type
 * @return {uint8_t} valid flag
 */
uint8_t testDilithiumInPolyMessages();

/*** 
 * @description: The test function for Dilithium signature
 * @return {uint8_t} valid flag
 */
uint8_t testDilithium();

