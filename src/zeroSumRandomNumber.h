/*** 
 * @Author: B1ank
 * @Date: 2022-12-26 00:00:32
 * @LastEditTime: 2023-01-04 22:12:49
 * @LastEditors: B1ank
 * @Description: The header definition file for the generation and update process of zero-sum random number designed for collusion resistance
 * @FilePath: /FTCR-LMPPDA/src/zeroSumRandomNumber.h
 */

#ifndef ZERO_SUM_RANDOM_NUMBER_H
#define ZERO_SUM_RANDOM_NUMBER_H

#include "params.h"
#include <stdint.h>

// Random number generation process

/*** 
 * @description: Random number slicing operation, aiming at get slices with the number of participantsNumber
 * @return {uint64_t*} distributed random number slices
 */
uint64_t* randomNumberSlicing();

/*** 
 * @description: Combination operation of random number for collusion attack
 * @param {uint64_t*} distributedRandomNumbers the distributed random slices from the smart meter
 * @param {uint64_t*} receivedRandomNumbers the received random slices from the smart meter
 * @param {uint64_t} selfFlag the flag to mark the identity of smart meters
 * @return {uint64_t} combined anti-collusion random number
 */
uint64_t randomNumberCombination(uint64_t* distributedRandomNumbers, uint64_t* receivedRandomNumbers, uint64_t selfFlag);

// Random number update process

/*** 
 * @description: Generation process of the original sequence \Gamma_{1}
 * @return {uint64_t*} return the array with the length of participantsCount containing half of 1s and half of 0s
 */
uint64_t* originalSequenceGeneration();

/*** 
 * @description: Generation of the final information for zero-sum random number update process
 * @param {uint64_t[][]} shuffledSequences the two-dimensional array is utilized to represnet the random 0-1 string after shuffle
 * @return {uint64_t*} random number update array, the element with index i is sent to the ith smart meter
 */
uint64_t* updateInformationGeneration(uint64_t shuffledSequences[aggregationRounds-1][participantsNumber]);

/*** 
 * @description: Update process of the zero-sum random number for smart meter
 * @param {uint64_t} randomNumberOfLastRound 
 * @param {uint64_t} updateInformation
 * @param {uint64_t} indexOfLastRound
 * @return {uint64_t} new random number for the next aggregation round
 */
uint64_t randomNumberUpdate(uint64_t randomNumberOfLastRound, uint64_t updateInformation, uint64_t indexOfLastRound);

#endif