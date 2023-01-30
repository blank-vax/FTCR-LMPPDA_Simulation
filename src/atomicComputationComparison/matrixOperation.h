/*** 
 * @Author: B1ank
 * @Date: 2023-01-18 00:12:12
 * @LastEditTime: 2023-01-18 23:27:00
 * @LastEditors: your name
 * @Description: Performance evaluation of matrix operations with the help of MKL library
 * @FilePath: /FTCR-LMPPDA/src/atomicComputationComparison/matrixOperation.h
 */
#ifndef MATRIX_OPERATION_H
#define MATRIX_OPERATION_H

#include <Eigen/Dense>

/*** 
 * @description: Performance evaluation of matrix operations in 18'Abdallah et al. scheme
 * @return {*}
 */
void matrixOperationsInAbdallahSchemePerformanceEvaluation();


/*** 
 * @description: Performance evaluation of matrix operations in 21'Qian et al. shceme
 * @return {*}
 */
void matrixOperationsInQianSchemePerformanceEvaluation();

#endif 