/*
 * @Author: B1ank
 * @Date: 2023-01-18 00:12:20
 * @LastEditTime: 2023-01-18 17:59:37
 * @LastEditors: your name
 * @Description: C source code for performance evaluation of matrix operations
 * @FilePath: /FTCR-LMPPDA/src/atomicComputationComparison/matrixOperation.c
 */

#include "matrixOperation.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

#define n 9
#define N 50
#define MAX 10 // 2**10
#define p 60 // 2**60
#define repeatTime 100

using namespace Eigen;
using namespace std::chrono;

/*** 
 * @description: Performance evaluation of matrix operations in 18'Abdallah et al. scheme
 * @return {*}
 */
void matrixOperationsInAbdallahSchemePerformanceEvaluation() {
    // Initialization of matrix and vector
    MatrixXd testMatrixN2N(N, 2*N), testMatrixNN(N, N), testDiagonalMatrixNN(N, N);
    VectorXd testVector10Bits(N), testVector1Bits(N), testVector60BitsAlpha(2*N), testVector60BitsBeta(2*N), testVector60BitsNormal(N);
    int rowsCount, columnsCount, timesCount, evaluationCount;
    int powResultOfTwoFor60Bits = pow(2, 10);
    int powResultOfTwoFor10Bits = pow(2, 8);

    // Variables for time evaluation
    
    MatrixXd result1Time2NMatrix(1, 2*N), resultNTimeNMatrix(N, N), result1TimeNMatrix(1, N);
    VectorXd result2NVector(2*N), resultNVector(N);

    // Matrix N x 2N with elements no greater than 60 bits
    for (rowsCount = 0; rowsCount < N; rowsCount++) {
        for (columnsCount = 0; columnsCount < 2*N; columnsCount++) {
            testMatrixN2N(rowsCount, columnsCount) = powResultOfTwoFor60Bits + rand(); // < 2*pow(2, 58) = pow(2, 59) < pow(2, 60)
        }
    }
    
    // Matrix N x N with elements no greater than 60 bits
    for (rowsCount = 0; rowsCount < N; rowsCount++) {
        for (columnsCount = 0; columnsCount < N; columnsCount++) {
            testMatrixNN(rowsCount, columnsCount) = powResultOfTwoFor60Bits + rand();
        }
    }
    
    // Diagonal matrix on GF(p)
    testDiagonalMatrixNN = MatrixXd::Identity(N, N);
    testDiagonalMatrixNN *= powResultOfTwoFor60Bits;
    
    // Column vector of N dimension with elements no greater than 10 bits, 60 bits and 1 bit
    for (rowsCount = 0; rowsCount < N; rowsCount++) {
        testVector10Bits[rowsCount] = powResultOfTwoFor10Bits + rand();
        testVector60BitsNormal[rowsCount] = powResultOfTwoFor60Bits + rand();
        testVector1Bits[rowsCount] = rand() % 2;
    }

    // Column vector of 2*N dimension with elements no greater than 60 bits
    for (rowsCount = 0; rowsCount < 2*N; rowsCount++) {
        testVector60BitsAlpha[rowsCount] = powResultOfTwoFor60Bits + rand();
        testVector60BitsBeta[rowsCount] = powResultOfTwoFor60Bits + rand();
    }

    // ! Performance Evaluation1: Encryption/Verification
    auto t1 = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
    for (evaluationCount = 0; evaluationCount < repeatTime; evaluationCount++) {
        // ? Multiplication for n times between 1*N vector with elements no greater than 10 bits and N*2N matrix with elements no greater than 60 bits
        for (timesCount = 0; timesCount < n; timesCount++) {
            result1Time2NMatrix = testVector10Bits.transpose() * testMatrixN2N;
        }
        // ? Multiplication for one time between 1*N vector with elements no greater than 1 bit and N*2N matrix with elements no greater than 60 bits
        result1Time2NMatrix = testVector1Bits.transpose() * testMatrixN2N;
        // ? Addition for n times between two 1*2N vectors with elements no greater than 60 bits
        for (timesCount = 0; timesCount < n; timesCount++) {
            result2NVector = testVector60BitsAlpha + testVector60BitsBeta;
        }
    }
    auto t2 = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();

    std::cout << "Encryption/Verification Operation Performance Evaluation Result: " << (t2-t1)/repeatTime <<std::endl;
    // ! Performance Evaluation2: Decryption/Verification

    auto t3 = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
    for (evaluationCount = 0; evaluationCount < repeatTime; evaluationCount++) {
        // ? Multiplication for one time between two N*N matrices with elements no greater than 60 bits
        resultNTimeNMatrix = testMatrixNN * testMatrixNN;
        // ? Multiplication for one time between 1*N vector and N*N matrix with elements no greater than 60 bits
        result1TimeNMatrix = testVector60BitsNormal.transpose() * testMatrixNN;
        // ? Multiplication for one time between 1*N vector and N*N diagonal matrix with elements no greater than 60 bits
        result1TimeNMatrix = testVector60BitsNormal.transpose() * testDiagonalMatrixNN;
        // ? Addition for one time between two 1*N vetor with elements no greater than 60 bits
        resultNVector = testVector60BitsNormal + testVector60BitsNormal;
    }
    auto t4 = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();

    std::cout << "Decryption/Signature Operation Perfromance Evaluation Result: " << (t4-t3)/repeatTime << std::endl;
}


/*** 
 * @description: Performance evaluation of matrix operations in 21'Qian et al. shceme
 * @return {*}
 */
void matrixOperationsInQianSchemePerformanceEvaluation() {
    VectorXd testVector60BitsNormal(N), resultNVector(N);
    int rowsCount, evaluationCount;
    int powResultOfTwoFor60Bits = pow(2, 10);

    for (rowsCount = 0; rowsCount < N; rowsCount++) {
        testVector60BitsNormal[rowsCount] = powResultOfTwoFor60Bits + rand();
    }
    // ! Performance Evaluation3: EE
    auto t1 = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
    // ? Addition for one time between two 1*N vector with elements no greater than 60 bits
    for (evaluationCount = 0; evaluationCount < repeatTime; evaluationCount++) {
        resultNVector = testVector60BitsNormal + testVector60BitsNormal;
    }
    auto t2 = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();

    std::cout << "EE Operation Performance Evaluation Result: " << (t2-t1)/repeatTime << std::endl;
}



