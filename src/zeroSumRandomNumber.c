/*
 * @Author: B1ank
 * @Date: 2022-12-26 00:00:43
 * @LastEditTime: 2023-01-06 17:55:37
 * @LastEditors: your name
 * @Description: The implementation for the generation and update process of zero-sum random number designed for collusion resistance
 * @FilePath: /FTCR-LMPPDA/src/zeroSumRandomNumber.c
 */

#include "zeroSumRandomNumber.h"
#include "Fisher-YatesShuffle.h"
#include <time.h>
#include <math.h>

// Random number generation process

uint64_t* randomNumberSlicing(){
    // Generation of random number located in [10, 20] 
    srand((unsigned)time(NULL));
    static uint64_t slices[participantsNumber];
    for(uint64_t index=0;index<participantsNumber;index++) {
        slices[index] = rand() % 10 + 10;
    }
    return slices;
}

uint64_t randomNumberCombination(uint64_t* distributedRandomNumbers, uint64_t* receivedRandomNumbers, uint64_t selfFlag){
    uint64_t antiCollusionFlag = 0, sum1 = 0, sum2 = 0;
    for(int index=0;index<participantsNumber-1;index++) {
        sum2 += receivedRandomNumbers[index];
    }
    for(int index2=0;index2<participantsNumber;index2++) {
        if(index2 == selfFlag) {continue;}
        sum1 += distributedRandomNumbers[index2];
    }
    antiCollusionFlag = sum1 - sum2;
    return antiCollusionFlag;
}

// Random number update process

uint64_t* originalSequenceGeneration(){
    // Generation of the original sequence with half 0s and half 1s
    static uint64_t originalSequence[participantsNumber];
    for(int i = 0; i < participantsNumber/2;i++){
        originalSequence[i] = 1;
    }
    for(int j = participantsNumber/2; j < participantsNumber;j++){
        originalSequence[j] = 0;
    }
    // Fisher-Yates Shuffle function on original sequence
    shuffleSequence(originalSequence, participantsNumber);
    return originalSequence;
}

uint64_t* updateInformationGeneration(uint64_t shuffledSequences[aggregationRounds-1][participantsNumber]){
    static uint64_t concatenationResult[participantsNumber];
    for(int index1 = 0;index1 < participantsNumber;index1++){
        uint64_t decimalNumber = 0;
        for(int index2 = 0;index2 < aggregationRounds-1;index2++) {
            decimalNumber += shuffledSequences[index2][index1]*pow(2,index2);
        }
        concatenationResult[index1] = decimalNumber;
    }
    return concatenationResult;
}

uint64_t randomNumberUpdate(uint64_t randomNumberOfLastRound, uint64_t updateInformation, uint64_t indexOfLastRound){
    uint64_t randomNumberForNextRound = 0;
    // Change from decimal number to binary strings
    uint64_t binaryTransformResult[aggregationRounds-1];
    for(int index=aggregationRounds-2; index >=0;index--){
        binaryTransformResult[index] = updateInformation % 2;
        updateInformation /= 2;
    }
    uint64_t flag = binaryTransformResult[indexOfLastRound-1];
    if(flag == 1) {
        randomNumberForNextRound = randomNumberOfLastRound + 1;
    }else {
        randomNumberForNextRound = randomNumberOfLastRound - 1;
    }
    return randomNumberForNextRound;
}
