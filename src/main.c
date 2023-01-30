/*
 * @Author: B1ank
 * @Date: 2022-12-20 23:41:14
 * @LastEditTime: 2023-01-30 12:12:41
 * @LastEditors: Blank-vax 15554467517@163.com
 * @Description: 1) Programming to realize the overall process of FTCR-LMPPDA scheme, which can be executed on different platforms to achieve the total runtime test(~/FTCR-LMPPDATest) 
 * 2) Complete the algorithm performance test of each unit of FTCR-LMPPDA scheme(~/FTCR-LMPPDABlockTest)
 * @FilePath: /FTCR-LMPPDA/src/main.c
 */

#include <stdio.h>
#include "dataEmbedding.h"
#include "Dilithium.h"
#include "Fisher-YatesShuffle.h"
#include "gaussianSampling.h"
#include "numberCRT.h"
#include "params.h"
#include "PH-NTRU.h"
#include "poly.h"
#include "zeroSumRandomNumber.h"
#include <time.h>

int main(int argc, char** argv) {
    // ? Variables initialization

    // ! PH-NTRU algorithm
    int index;
    keyPairs keyPairsForPHNTRU;
    poly publicKeyForEncryption, privateKeyForEncryption, ciphertext;
    int64_t *primesArr;
    uint64_t decryptionResult = 0;

    // ! numberCRT
    primeBlock pB;
    int64_t processedData = 0;
    int64_t *recoveryResult;

    // ! Dilithium signature 
    uint8_t *publicKeyForSignature = NULL;
    uint8_t *privateKeyForSignature = NULL;
    size_t messageLength = NTRU_N;
    uint8_t *message = NULL;

    OQS_STATUS rc;
    keyPair keyPairForDilithium;
    dilithiumSignature signatureResultSetsForSM[participantsNumber];
    dilithiumSignature signatureResultForGW;
    OQS_SIG *sig = NULL;

    // ! Efficiency evaluation
    struct timespec begin1, end1, begin2, end2;
    struct timespec begin3, end3, begin4, end4;

    long seconds1, nanoseconds1;
    long seconds2, nanoseconds2;

    long durationSeconds1, nanoDurationSeconds1;
    long durationSeconds2, nanoDurationSeconds2;

    // ? Total Execution Time in Different Devices
    double smartMeterREALTime = 0;
    double smartMeterCPUTime = 0;

    double edgeGatewayREALTime = 0;
    double edgeGatewayCPUTime = 0;

    double controlCenterREALTime = 0;
    double controlCenterCPUTime = 0;

    // ? Atomic Operations

    double numberCRTDataProcessREALTime = 0;
    double numberCRTDataProcessCPUTime = 0;

    double numberCRTDataRecoveryREALTime = 0;
    double numberCRTDataRecoveryCPUTime = 0;

    double encryptionREALTime = 0;
    double encryptionCPUTime = 0;

    double signatureREALTimeOfSM = 0;
    double signatureCPUTimeOfSM = 0;

    double signatureREALTimeOfGW = 0;
    double signatureCPUTimeOfGW = 0;

    double verificationREALTimeOfGW = 0;
    double verificationCPUTimeOfGW = 0;

    double verificationREALTimeOfCC = 0;
    double verificationCPUTimeOfCC = 0;

    double homomorphicAddREALTime = 0;
    double homomorphicAddCPUTime = 0;

    double decryptionREALTime = 0;
    double decryptionCPUTime = 0;

    // Zeroing for ciphertexts
    poly ciphertexts[participantsNumber];
    memset(ciphertexts, 0, sizeof(poly)*participantsNumber);
    for(index = 0;index < participantsNumber;index++) {
        polyZeroing(&ciphertexts[index], NTRU_N);
    }

    // Generation of original data
    // TODO After system upgrade, we consider perform efficiency evaluation on the real multidimensional power datasets
    // TODO In the initial version, we use automatically generated random power data for evaluation
    // ? There are total 10 participants, each collects the 10-dimensions random data less than 4

    uint64_t testDataSet [participantsNumber][dimensionNumber] = {0};
    // Initalization for test dataset
    for(int i = 0;i < participantsNumber;i++) {
        for (int j = 0;j < dimensionNumber;j++) {
            testDataSet[i][j] = random() % upperBoundOfEachDimension;
        }
    }
    // PolyZeroing
    polyZeroing(&publicKeyForEncryption, NTRU_N);
    polyZeroing(&privateKeyForEncryption, NTRU_N);
    polyZeroing(&ciphertext, NTRU_N);
    polyCopy(&publicKeyForEncryption, &keyPairsForPHNTRU.publicKey);
    polyCopy(&privateKeyForEncryption, &keyPairsForPHNTRU.privateKey);
    // Key generation process
    keyGeneration(&keyPairsForPHNTRU);
    // numberCRT transform process
    // Zeroing for numberCRT
    for(index = 0; index < dimensionNumber; index++) {
        pB.alphaArr[index] = 0;
    }
    // Init for numberCRT
    primesArr = primesGeneration(participantsNumber, upperBoundOfEachDimension);
    numberCRTInit(primesArr, &pB);
    // Space allocation of message
    message = malloc(messageLength);
    if (message == NULL) {
        // Something error in message space allocation
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(NULL, NULL, message, NULL, sig);
        rc = OQS_ERROR;
    }

    printf("<============>Operations in Smart Meters<============>\n");

    // ! Time Evaluation: total time of operations performed in smart meters
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin3);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin4);    

    // ? Smart Meters
    // ! Encryption in smart meters
    for(int i = 0; i < participantsNumber;i++) {
        // Data process for numberCRT
        // ! Time Evaluation: numberCRT data process in smart meters
        // Real time set
        clock_gettime(CLOCK_REALTIME, &begin1);
        // CPU time set
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
        processedData = numberCRTDP(testDataSet[i], &pB);
        // Real time end
        clock_gettime(CLOCK_REALTIME, &end1);
        // CPU time end
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
        // REALTIME count
        seconds1 = end1.tv_sec - begin1.tv_sec;
        nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
        numberCRTDataProcessREALTime += seconds1 + nanoseconds1*1e-9;
        // CPUTIME count
        seconds2 = end2.tv_sec - begin2.tv_sec;
        nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
        numberCRTDataProcessCPUTime += seconds2 + nanoseconds2*1e-9;

        // ! Time Evaluation1: PH-NTRU encryption in smart meters
        // Real time set
        clock_gettime(CLOCK_REALTIME, &begin1);
        // CPU time set
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
        encryption(processedData, &keyPairsForPHNTRU.publicKey, i*blockSize, &ciphertexts[i]);
        // Real time end
        clock_gettime(CLOCK_REALTIME, &end1);
        // CPU time end
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
        // REALTIME count
        seconds1 = end1.tv_sec - begin1.tv_sec;
        nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
        encryptionREALTime += seconds1 + nanoseconds1*1e-9;

        // CPUTIME count
        seconds2 = end2.tv_sec - begin2.tv_sec;
        nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
        encryptionCPUTime += seconds2 + nanoseconds2*1e-9;
    }
    encryptionREALTime /= participantsNumber;
    encryptionCPUTime /= participantsNumber;

    numberCRTDataProcessREALTime /= participantsNumber;
    numberCRTDataProcessCPUTime /= participantsNumber;

    printf("numberCRTDataProcessREALTime in SM: %.10f seconds\n", numberCRTDataProcessREALTime);
    printf("numberCRTDataProcessCPUTime in SM: %.10f seconds\n", numberCRTDataProcessCPUTime);

    printf("encryptionREALTime in SM: %.10f seconds\n", encryptionREALTime);
    printf("encryptionCPUTime in SM: %.10f seconds\n", encryptionCPUTime);

    // Dilithium signature generation for 10 ciphertexts
    
    // Zeroing for signature results
    // ! Signature generation in smart meters
    memset(signatureResultSetsForSM, 0, sizeof(dilithiumSignature)*participantsNumber);
    // Initialization process of OQS_SIG object
    sig = OQS_SIG_new(OQS_SIG_alg_dilithium_3);
    if (sig == NULL) {
        printf("OQS_SIG_alg_dilithium_3 was not enabled at compile-time.\n");
        rc = OQS_ERROR;
        printf("Something error in the initialization process of Dilithium signature\n");
    }
    rc = keypairGeneration(sig, &keyPairForDilithium);
    if (rc != OQS_SUCCESS) {
        printf("Something error in the signature generation process of Dilithium signature\n");
    }

    privateKeyForSignature = malloc(sig->length_secret_key);
    publicKeyForSignature = malloc(sig->length_public_key);

    if ((privateKeyForSignature == NULL) || (publicKeyForSignature == NULL)) {
        // Something error in privateKey/publicKey space allocation
        fprintf(stderr, "ERROR: malloc failed!\n");
        cleanupHeap(publicKeyForSignature, privateKeyForSignature, NULL, NULL, sig);
        rc = OQS_ERROR;
    }
    memcpy(publicKeyForSignature, getPubKey(&keyPairForDilithium), sig->length_public_key);
    memcpy(privateKeyForSignature, getSecKey(&keyPairForDilithium), sig->length_secret_key);
    for (int i = 0;i < participantsNumber;i++) {
        // ! Time Evaluation2: Dilithium signatures generation in smart meters
        // Real time set
        clock_gettime(CLOCK_REALTIME, &begin1);
        // CPU time set
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
        memcpy(message, messageMapper(&ciphertexts[i]), messageLength);
        // Dilithium signature generation
        rc = dilithiumSign(sig, message, messageLength, privateKeyForSignature, &signatureResultSetsForSM[i]);
        // Real time end
        clock_gettime(CLOCK_REALTIME, &end1);
        // CPU time end
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
        if (rc != OQS_SUCCESS) {
            // Something error in signature generation process in Dilithium
            printf("Dilithium signature generation failed for user %d\n", i);
            break;
        } else {
            // REALTIME count
            seconds1 = end1.tv_sec - begin1.tv_sec;
            nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
            signatureREALTimeOfSM += seconds1 + nanoseconds1*1e-9;
            // CPUTIME count
            seconds2 = end2.tv_sec - begin2.tv_sec;
            nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
            signatureCPUTimeOfSM += seconds2 + nanoseconds2*1e-9;
        }
    }
    signatureREALTimeOfSM /= participantsNumber;
    signatureCPUTimeOfSM /= participantsNumber;
    printf("signatureREALTime in SM: %.10f seconds\n", signatureREALTimeOfSM);
    printf("signatureCPUTime in SM: %.10f seconds\n", signatureCPUTimeOfSM);

    // Real time end
    clock_gettime(CLOCK_REALTIME, &end3);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end4);
    // REALTIME count
    durationSeconds1 = end3.tv_sec - begin3.tv_sec;
    nanoDurationSeconds1 = end3.tv_nsec - begin3.tv_nsec;
    smartMeterREALTime = (durationSeconds1 + nanoDurationSeconds1*1e-9) / participantsNumber;
    // CPUTIME count
    durationSeconds2 = end4.tv_sec - begin4.tv_sec;
    nanoDurationSeconds2 = end4.tv_nsec - begin4.tv_nsec;
    smartMeterCPUTime = (durationSeconds2 + nanoDurationSeconds2*1e-9) / participantsNumber;

    printf("totalExecutionREALTime in SM: %.10f seconds\n", smartMeterREALTime);
    printf("totalExecutionCPUTime in SM: %.10f seconds\n", smartMeterCPUTime);

    printf("<============>Operations in Edge Gateway<============>\n");
    // ! Time Evaluation: total time of operations performed in edge gateway devices
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin3);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin4);    
    // ? Edge Gateway
    // ! Signature verification in edge gateway
    // Dilithium signature verification for 10 ciphertexts
    for (int k = 0;k < participantsNumber;k++) {
        // ! Time Evaluation3: Dilithium signatures verification in edge gateway
        // Real time set
        clock_gettime(CLOCK_REALTIME, &begin1);
        // CPU time set
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
        memcpy(message, messageMapper(&ciphertexts[k]), messageLength);
        rc = dilithiumVerify(sig, message, messageLength, publicKeyForSignature, &signatureResultSetsForSM[k]);
        // Real time end
        clock_gettime(CLOCK_REALTIME, &end1);
        // CPU time end
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
        if (rc != OQS_SUCCESS) {
            // Something error in verification process in Dilithium
            printf("Dilithium signature verification failed for user %d\n", k);
            break;
        } else {
            // REALTIME count
            seconds1 = end1.tv_sec - begin1.tv_sec;
            nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
            verificationREALTimeOfGW += seconds1 + nanoseconds1*1e-9;
            // CPUTIME count
            seconds2 = end2.tv_sec - begin2.tv_sec;
            nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
            verificationCPUTimeOfGW += seconds2 + nanoseconds2*1e-9;
        }
    }
    verificationREALTimeOfGW /= participantsNumber;
    verificationCPUTimeOfGW /= participantsNumber;
    printf("verificationREALTime in GW: %.10f seconds\n", verificationREALTimeOfGW);
    printf("verificationCPUTime in GW: %.10f seconds\n", verificationCPUTimeOfGW);
    
    // ! Homomorphic addition operation in edge gateway
    // Homomorphic addition
    for(int j = 1; j < participantsNumber;j++) {
        // ! Time Evaluation4: Homomorphic addition in edge gateway
        // Real time set
        clock_gettime(CLOCK_REALTIME, &begin1);
        // CPU time set
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
        homomorphicAdd(&ciphertexts[0], &ciphertexts[j]);
        // Real time end
        clock_gettime(CLOCK_REALTIME, &end1);
        // CPU time end
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
        // REALTIME count
        seconds1 = end1.tv_sec - begin1.tv_sec;
        nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
        homomorphicAddREALTime += seconds1 + nanoseconds1*1e-9;

        // CPUTIME count
        seconds2 = end2.tv_sec - begin2.tv_sec;
        nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
        homomorphicAddCPUTime += seconds2 + nanoseconds2*1e-9;
    }
    homomorphicAddREALTime /= (participantsNumber-1);
    homomorphicAddCPUTime /= (participantsNumber-1);
    printf("homomorphic addition REALTime in GW: %.10f seconds\n", homomorphicAddREALTime);
    printf("homomorphic addition CPUTime in GW: %.10f seconds\n", homomorphicAddCPUTime);

    // ! Signature generation in edge gateway
    // ! Time Evaluation5: Dilithium signature generation in edge gateway
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin1);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    memcpy(message, messageMapper(&ciphertexts[0]), messageLength);
    rc = dilithiumSign(sig, message, messageLength, privateKeyForSignature, &signatureResultForGW);
    // Real time end
    clock_gettime(CLOCK_REALTIME, &end1);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    signatureREALTimeOfGW = seconds1 + nanoseconds1*1e-9;
    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    signatureCPUTimeOfGW = seconds2 + nanoseconds2*1e-9;
    if (rc != OQS_SUCCESS) {
        // Something error in signature generation process in Dilithium
        printf("Dilithium signature generation failed for edge gateway\n");
    } else {
        printf("signatureREALTime in GW: %.10f seconds\n", signatureREALTimeOfGW);
        printf("signatureCPUTime in GW: %.10f seconds\n", signatureCPUTimeOfGW);
    }

    // Real time end
    clock_gettime(CLOCK_REALTIME, &end3);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end4);
    // REALTIME count
    durationSeconds1 = end3.tv_sec - begin3.tv_sec;
    nanoDurationSeconds1 = end3.tv_nsec - begin3.tv_nsec;
    edgeGatewayREALTime = durationSeconds1 + nanoDurationSeconds1*1e-9;
    // CPUTIME count
    durationSeconds2 = end4.tv_sec - begin4.tv_sec;
    nanoDurationSeconds2 = end4.tv_nsec - begin4.tv_nsec;
    edgeGatewayCPUTime = durationSeconds2 + nanoDurationSeconds2*1e-9;

    printf("totalExecutionREALTime in GW: %.10f seconds\n", edgeGatewayREALTime);
    printf("totalExecutionCPUTime in GW: %.10f seconds\n", edgeGatewayCPUTime);    
   
    printf("<============>Operations in Control Center<============>\n");
    // ! Time Evaluation: total time of operations performed in the control center
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin3);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin4);     

    // ? Control Center
    // ! Signature verification in control center
    // ! Time Evaluation6: Dilithium signature verification in control center
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin1);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    memcpy(message, messageMapper(&ciphertexts[0]), messageLength);
    rc = dilithiumVerify(sig, message, messageLength, publicKeyForSignature, &signatureResultForGW);
    // Real time end
    clock_gettime(CLOCK_REALTIME, &end1);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);

    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    verificationREALTimeOfCC = seconds1 + nanoseconds1*1e-9;
    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    verificationCPUTimeOfCC = seconds2 + nanoseconds2*1e-9;

    if (rc != OQS_SUCCESS) {
        // Something error in verification process in Dilithium
        printf("Dilithium siganture verification failed for edge gateway\n");
    } else {
        printf("verificationREALTime in CC: %.10f seconds\n", verificationREALTimeOfCC);
        printf("verificationCPUTime in CC: %.10f seconds\n", verificationCPUTimeOfCC);
    }

    // ! Decryption in control center
    // ! Time Evaluation7: PH-NTRU decryption algorithm in control center
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin1);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    decryptionResult = decryption(&ciphertexts[0], &keyPairsForPHNTRU.privateKey);
    // Real time end
    clock_gettime(CLOCK_REALTIME, &end1);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);

    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    decryptionREALTime = seconds1 + nanoseconds1*1e-9;
    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    decryptionCPUTime = seconds2 + nanoseconds2*1e-9;
    printf("decryptionREALTime in CC: %.10f seconds\n", decryptionREALTime);
    printf("decryptionCPUTime in CC: %.10f seconds\n", decryptionCPUTime);

    // Data recovery for numberCRT
    // ! Time Evaluation: numberCRT data recovery in control center
    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin1);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    recoveryResult = numberCRTDR(decryptionResult, &pB);
    // Real time end
    clock_gettime(CLOCK_REALTIME, &end1);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    numberCRTDataRecoveryREALTime = seconds1 + nanoseconds1*1e-9;
    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    numberCRTDataRecoveryCPUTime = seconds2 + nanoseconds2*1e-9;

    printf("numberCRTDataRecoveryREALTime in CC: %.10f seconds\n", numberCRTDataRecoveryREALTime);
    printf("numberCRTDataRecoveryCPUTime in CC: %.10f seconds\n", numberCRTDataRecoveryCPUTime);

    // Real time end
    clock_gettime(CLOCK_REALTIME, &end3);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end4);
    // REALTIME count
    durationSeconds1 = end3.tv_sec - begin3.tv_sec;
    nanoDurationSeconds1 = end3.tv_nsec - begin3.tv_nsec;
    controlCenterREALTime = durationSeconds1 + nanoDurationSeconds1*1e-9;
    // CPUTIME count
    durationSeconds2 = end4.tv_sec - begin4.tv_sec;
    nanoDurationSeconds2 = end4.tv_nsec - begin4.tv_nsec;
    controlCenterCPUTime = durationSeconds2 + nanoDurationSeconds2*1e-9;

    printf("totalExecutionREALTime in CC: %.10f seconds\n", controlCenterREALTime);
    printf("totalExecutionCPUTime in CC: %.10f seconds\n", controlCenterCPUTime); 

    // for(int k = 0;k < dimensionNumber; k++) {
    //     printf("recovery result: %d\n", recoveryResult[k]);
    // }

    // // Start measuring time
    // // Real time set
    // clock_gettime(CLOCK_REALTIME, &begin1);
    // // CPU time set
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    // // ? Functions to be measured
    // printf("Hello World\n");
    // // Real time end
    // clock_gettime(CLOCK_REALTIME, &end1);
    // // CPU time end
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);

    // // REALTIME count
    // seconds1 = end1.tv_sec - begin1.tv_sec;
    // nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    // double elapsed1 = seconds1 + nanoseconds1*1e-9;
    // printf("REALTIME measured: %.10f seconds.\n", elapsed1);

    // // CPUTIME count
    // seconds2 = end2.tv_sec - begin2.tv_sec;
    // nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    // double elapsed2 = seconds2 + nanoseconds2*1e-9;
    // printf("CPUTIME measured: %.10f seconds.\n", elapsed2);
    return 0;
}