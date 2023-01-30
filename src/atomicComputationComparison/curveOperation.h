/*** 
 * @Author: B1ank
 * @Date: 2023-01-18 00:12:28
 * @LastEditTime: 2023-01-18 13:24:35
 * @LastEditors: your name
 * @Description:  Performance evaluation of operations on curvers with the help of PBC library
 * @FilePath: /FTCR-LMPPDA/src/atomicComputationComparison/curveOperation.h
 */

#include "pbc/pbc.h"
#include "pbc/pbc_a_param.h"
#include "fips202.h"

/*** 
 * @description: Performance evaluation of numerical operations, including the hash operation and the multiplication operation
 * @return {*}
 */
void numericalOperationsPerformanceEvaluation();

/*** 
 * @description: Performance evaluation of curve operations, including point multiplication, point mapping and bilinear pairing operations on Type A curve
 * @return {*}
 */
void curveOperationPerformanceEvaluation();

