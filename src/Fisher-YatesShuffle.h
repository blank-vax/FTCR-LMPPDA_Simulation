/*** 
 * @Author: B1ank
 * @Date: 2022-12-26 00:10:14
 * @LastEditTime: 2023-01-04 15:32:49
 * @LastEditors: your name
 * @Description: The header definition file for the Fisher-Yates Shuffle
 * @FilePath: /FTCR-LMPPDA/src/Fisher-YatesShuffle.h
 */
#ifndef FISHER_YATES_SHUFFLE_H
#define FISHER_YATES_SHUFFLE_H
#include <stdint.h>

/*** 
 * @description: shuffle implement of input array
 * @param {uint64_t} v input integer array
 * @param {uint64_t} size the length of the input array
 * @return {*}
 */
void shuffleSequence(uint64_t v[], uint64_t size);

# endif