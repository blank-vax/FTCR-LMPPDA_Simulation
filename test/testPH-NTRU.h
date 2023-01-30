/*** 
 * @Author: B1ank
 * @Date: 2023-01-12 00:37:46
 * @LastEditTime: 2023-01-12 00:59:14
 * @LastEditors: your name
 * @Description: The header file of test functions for PH-NTRU homomorphic algorithm
 * @FilePath: /FTCR-LMPPDA/test/testPH-NTRU.h
 */


#include "../src/PH-NTRU.h"
#include "../src/poly.h"
#include "../src/params.h"
#include "../src/numberCRT.h"

/*** 
 * @description: The test function for PH-NTRU encryption and decryption 
 * @return {uint8_t} valid flag
 */
uint8_t testPHNTRUEncAndDec();

/*** 
 * @description: The test function for PH-NTRU homomorphism
 * @return {uint8_t} valid flag
 */
uint8_t testPHNTRUHomorphism();


/*** 
 * @description: The test function for the support for multidimensional data for PH-NTRU algorithm
 * @return {uint8_t} valid flag
 */
uint8_t testPHNTRUForMultidimensionData();

/*** 
 * @description: The test function for PH-NTRU algorithm
 * @return {uint8_t} valid flag
 */
uint8_t testPHNTRU();