/*
 * @Author: B1ank
 * @Date: 2023-01-18 00:12:41
 * @LastEditTime: 2023-01-18 23:02:59
 * @LastEditors: your name
 * @Description: C source code designed for atomic operation computation overhead comparison, including curve operations (with the help of `pbc.h`) and matrix operations (with the help of `mkl.h`)
 * @FilePath: /FTCR-LMPPDA/src/atomicComputationComparison/atomicComputationComparison.c
 */

// #include "curveOperation.h"
// #include "matrixOperation.h"
// #include <iostream>
// using Eigen::MatrixXd;

// int main(int argc, char** argv) {
    
//     // printf("==========Numerical Operations Evaluation==========\n");
//     // numericalOperationsPerformanceEvaluation();
//     // printf("==========Curve Operations Evaluation==========\n");
//     // curveOperationPerformanceEvaluation();
//     // MatrixXd m(2,2);
//     // m(0,0) = 3;
//     // m(1,0) = 2.5;
//     // m(0,1) = -1;
//     // m(1,1) = m(1,0) + m(0,1);
//     // std::cout << m << std::endl;

//     std::cout << "==========Matrix Operations Evaluation==========\n" << std::endl;
//     std::cout << "Matrix operations in 18'Abdallah et al. scheme:\n" << std::endl;
//     matrixOperationsInAbdallahSchemePerformanceEvaluation();
//     std::cout << "Matrix operations in 21'Qian et al. scheme:\n" << std::endl;
//     matrixOperationsInQianSchemePerformanceEvaluation();
//     return 0;
// }