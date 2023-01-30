/*
 * @Author: B1ank
 * @Date: 2022-12-26 00:10:22
 * @LastEditTime: 2022-12-26 00:16:20
 * @LastEditors: B1ank
 * @Description: The implementation for the Fisher-Yates Shuffle
 * @FilePath: /FTCR-LMPPDA/src/Fisher-YatesShuffle.c
 */
#include "Fisher-YatesShuffle.h"
#include <time.h>
#include <math.h>

void shuffleSequence(uint64_t v[], uint64_t size){
    uint64_t i, r;
    for(i=0;i<size;++i) {
        // random seed generation according to the current time
        srand(time(NULL));
        r = rand() % (i+1);
        uint64_t tmp = v[i];
        v[i] = v[r];
        v[r] = tmp;
    }
}

