/*
 * @Author: B1ank
 * @Date: 2023-01-04 15:43:56
 * @LastEditTime: 2023-01-11 00:38:40
 * @LastEditors: your name
 * @Description: The implementation for tests of zero-sum random number generation and distribution
 * @FilePath: /FTCR-LMPPDA/test/testZeroSumRandomNumber.c
 */
#include "testZeroSumRandomNumber.h"
#include <stdio.h>
#include <string.h>


uint8_t testFYS(){
    uint8_t valid = 1;
    uint64_t originArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    shuffleSequence(originArray, 10);
    printf("Shuffled result:\n");
    for(int i = 0;i < 10;i++) {
        printf("%d\n", originArray[i]);
    }
    printf("Fisher-Yates shuffle test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

uint8_t testRandomNumberDistribution(){
    uint8_t valid = 1;
    uint64_t finalRandomNumber = 0, sum = 0;
    uint64_t randomNumbers[participantsNumber][participantsNumber];
    // Generation of the random number for each participant
    for(int index=0;index<participantsNumber;index++) {
        memcpy(randomNumbers[index], randomNumberSlicing(participantsNumber), sizeof(uint64_t)*(participantsNumber));
    }
    // Combination of the distributed number and the received number 
    for(int index2=0;index2<participantsNumber;index2++){
        // Zeroing
        int count = 0;
        static uint64_t receivedRandomNumbers[participantsNumber-1] = {0};
        for(int index3=0;index3<participantsNumber;index3++) {
            if(index2 == index3) {continue;}
            else{
                receivedRandomNumbers[count] = randomNumbers[index3][index2];
                count++;
            }
        }
        finalRandomNumber = randomNumberCombination(randomNumbers[index2], receivedRandomNumbers, index2);
        sum += finalRandomNumber;
    }
    printf("Sum of the distributed random numbers: %d\n", sum);
    valid &= sum == 0 ? 1 : 0;
    printf("Random number distribution zero-sum property test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

uint8_t testRandomNumberUpdate(){
    uint8_t valid = 1;
    static uint64_t Phi1[participantsNumber];
    static uint64_t finalRandomNumberLists[participantsNumber];
    uint64_t shuffledSequence[aggregationRounds-1][participantsNumber];
    uint64_t distributedPhis[participantsNumber];
    uint64_t randomNumbers[participantsNumber][participantsNumber];
    uint64_t finalRandomNumber = 0, updatedRandomNumber = 0, sum = 0;
    // Generation of the random number for each participant
    for(int index=0;index<participantsNumber;index++) {
        memcpy(randomNumbers[index], randomNumberSlicing(participantsNumber), sizeof(uint64_t)*(participantsNumber-1));
    }
    // Combination of the distributed number and the received number 
    for(int index2=0;index2<participantsNumber;index2++){
        // Zeroing
        int count = 0;
        static uint64_t receivedRandomNumbers[participantsNumber-1] = {0};
        for(int index3=0;index3<participantsNumber;index3++) {
            if(index2 == index3) {continue;}
            else{
                receivedRandomNumbers[count] = randomNumbers[index3][index2];
                count++;
            }
        }
        finalRandomNumber = randomNumberCombination(randomNumbers[index2], receivedRandomNumbers, index2);
        finalRandomNumberLists[index2] = finalRandomNumber; 
    }
    // Output the masked random numbers for the last aggregation round
    // uint64_t sum1 = 0;
    // for(int k = 0;k<participantsNumber;k++){
    //     sum1 += finalRandomNumberLists[k];
    // }
    // printf("The result of the masked random numbers for the last aggregation round: %d\n", sum1);
    // printf("Simulation of the update process of masked random numbers\n");

    // Generation of the update information
    memcpy(Phi1, originalSequenceGeneration(participantsNumber), sizeof(uint64_t)*(participantsNumber));
    // Perform the shuffle operations on the original sequence to get final 
    for(int roundNumber=0;roundNumber<aggregationRounds-1;roundNumber++) {
        memcpy(shuffledSequence[roundNumber], Phi1, sizeof(uint64_t)*(participantsNumber));
        shuffleSequence(Phi1, participantsNumber);
    }
    // distributed Phis for all participants
    memcpy(distributedPhis, updateInformationGeneration(shuffledSequence), sizeof(uint64_t)*(participantsNumber));
    for(int i = 0;i < participantsNumber;i++){
        updatedRandomNumber = randomNumberUpdate(finalRandomNumberLists[i], distributedPhis[i], 1);
        sum += updatedRandomNumber;
    }
    printf("Sum of the updated distributed random numbers: %d\n", sum);
    valid &= sum == 0 ? 1 : 0;
    printf("Random number updated zero-sum property test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}

uint8_t testZeroSumRandomNumber(){
    uint8_t valid = 1;
    valid &= testFYS();
    valid &= testRandomNumberDistribution();
    valid &= testRandomNumberUpdate();
    return valid;
}
