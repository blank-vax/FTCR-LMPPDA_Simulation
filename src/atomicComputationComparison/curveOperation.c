/*
 * @Author: B1ank
 * @Date: 2023-01-18 00:12:33
 * @LastEditTime: 2023-01-18 16:09:13
 * @LastEditors: your name
 * @Description: C source code for performance evaluation of curve operations
 * @FilePath: /FTCR-LMPPDA/src/atomicComputationComparison/curveOperation.c
 */
#include "curveOperation.h"
#include <stdlib.h>
#include <time.h>

/*** 
 * @description: Performance evaluation of numerical operations, including the hash operation and the multiplication operation
 * @return {*}
 */
void numericalOperationsPerformanceEvaluation() {
    unsigned char multiply1, multiply2, multiplicationResult;
    unsigned char hashInput[100], hashOutput[100];
    unsigned long long hashLength = 100;

    struct timespec begin1, end1, begin2, end2;
    long seconds1, nanoseconds1;
    long seconds2, nanoseconds2;
    double multiplyREALTime, multiplyCPUTime;
    double hashREALTime, hashCPUTime;
    
    srand(time(NULL));
    multiply1 = rand() % 10000;
    multiply2 = rand() % 10000;


    // ! Performance Evaluation1: numerical multiplication

    clock_gettime(CLOCK_REALTIME, &begin1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    for (int count = 0; count < 100; count++) {
        multiplicationResult = multiply1 * multiply2;
    }
    clock_gettime(CLOCK_REALTIME, &end1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);

    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    multiplyREALTime = seconds1 + nanoseconds1*1e-9;

    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    multiplyCPUTime = seconds2 + nanoseconds2*1e-9;

    multiplyREALTime /= 100;
    multiplyCPUTime /= 100;

    printf("Numerical multiplication REALTIME cost: %.10f\n", multiplyREALTime);
    printf("Numerical multiplication CPUTIME cost: %.10f\n", multiplyCPUTime);

    // Initialization of hash array
    for (int index = 0; index < 100; index++) {
        srand(time(NULL));
        hashInput[index] =  rand() % 100;
    }

    // ! Performance Evaluation2: numerical hashing
    // Hash operation, SHA3-512 as choice
    clock_gettime(CLOCK_REALTIME, &begin1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    for (int count = 0; count < 100; count++) {
        sha3_512(hashOutput, hashInput, 100);
    }
    clock_gettime(CLOCK_REALTIME, &end1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
    
    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    hashREALTime = seconds1 + nanoseconds1*1e-9;

    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    hashCPUTime = seconds2 + nanoseconds2*1e-9;

    hashREALTime /= 100;
    hashCPUTime /= 100;

    printf("Numerical SHA3-512 REALTIME cost: %.10f\n", hashREALTime);
    printf("Numerical SHA3-512 CPUTIME cost: %.10f\n", hashCPUTime);
}

/*** 
 * @description: Performance evaluation of curve operations, including point multiplication, point mapping and bilinear pairing operations on Type A curve
 * @return {*}
 */
void curveOperationPerformanceEvaluation() {
    struct timespec begin1, end1, begin2, end2;
    long seconds1, nanoseconds1;
    long seconds2, nanoseconds2;
    double pairingREALTime, pairingCPUTime;
    double pointMultiplicationREALTime, pointMultiplicationCPUTime;
    double pointMapperREALTime, pointMapperCPUTime;

    pairing_t pairing;
    element_t P, Y, M, W;
    element_t x;
    element_t T1, T2;
    
    unsigned char hashInput[100], hashOutput[100];
    static char *aparam =
        "type a\n"
        "q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\n"
        "h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\n"
        "r 730750818665451621361119245571504901405976559617\n"
        "exp2 159\n"
        "exp1 107\n"
        "sign1 1\n"
        "sign0 1\n";

    int byte;

    // Initialization of Type A curve
    
    pairing_init_set_str(pairing, aparam);

    // Initialize the variable to the element in G_1
    element_init_G1(P, pairing);
    element_init_G1(Y, pairing);
    element_init_G1(M, pairing);
    element_init_G1(W, pairing);

    // Initialize the variable to the element in Z_r
    element_init_Zr(x, pairing);

    // Initialize the variable to the element in G_T
    element_init_GT(T1, pairing);
    element_init_GT(T2, pairing);

    // Determine whether this pairing could be used normally
    if (!pairing_is_symmetric(pairing)) {
        fprintf(stderr, "Alert! Only works with symmetric pairing\n");
        exit(1);
    }
    
    element_random(x);
    element_random(P);

    // ! Performance Evaluation3: point multiplication 
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin1);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    for (int count = 0; count < 100; count++) {
        // Y=xP, point multiplication on curve
        element_mul_zn(Y, P, x);
    }
    // Real time end
    clock_gettime(CLOCK_REALTIME, &end1);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    pointMultiplicationREALTime = seconds1 + nanoseconds1*1e-9;
    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    pointMultiplicationCPUTime = seconds2 + nanoseconds2*1e-9;

    pointMultiplicationREALTime /= 100;
    pointMultiplicationCPUTime /= 100;

    printf("Point multiplication REALTime cost: %.10f\n", pointMultiplicationREALTime);
    printf("Point multiplication CPUTime cost: %.10f\n", pointMultiplicationCPUTime);

    for(int index = 0; index < 100; index++) {
        srand(time(NULL));
        hashInput[index] = rand() % 100;
    }

    // ! Performance Evalutaion4: point mapper
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin1);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    for (int count = 0; count < 100; count++) {
        // Convert from message to the point on curve with the help of SHA3-512
        sha3_512(hashOutput, hashInput, 100);
        element_from_hash(M, hashOutput, 100);
    }
    // Real time end
    clock_gettime(CLOCK_REALTIME, &end1);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    pointMapperREALTime = seconds1 + nanoseconds1*1e-9;
    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    pointMapperCPUTime = seconds2 + nanoseconds2*1e-9;

    pointMapperREALTime /= 100;
    pointMapperCPUTime /= 100;

    printf("Point mapper REALTime cost: %.10f\n", pointMapperREALTime);
    printf("Point mapper CPUTime cost: %.10f\n", pointMapperCPUTime);

    // W = xM
    element_mul_zn(W, M, x);

    // ! Performance Evaluation5: bilinear pairing
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin1);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);

    for (int count = 0; count < 100; count++) {
        // T1 = e(P, W)
        pairing_apply(T1, P, W, pairing);
        // T2 = e(Y, H_1(m))
        pairing_apply(T2, Y, M, pairing);
    }
    // Real time end
    clock_gettime(CLOCK_REALTIME, &end1);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    pairingREALTime = seconds1 + nanoseconds1*1e-9;
    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    pairingCPUTime = seconds2 + nanoseconds2*1e-9;

    pairingREALTime /= 10;
    pairingCPUTime /= 10;

    printf("Pairing on Type A curve REALTime cost: %.10f\n", pairingREALTime);
    printf("Pairing on Type A curve CPUTime cost: %.10f\n", pairingCPUTime);

    // Determine whether the signature is valid
    if (!element_cmp(T1, T2)) {
        printf("the signature is valid!\n");
    } else {
        printf("the signature is not valid!\n");
    }

    element_clear(P);
    element_clear(Y);
    element_clear(M);
    element_clear(W);
    element_clear(x);
    element_clear(T1);
    element_clear(T2);
    pairing_clear(pairing);
}