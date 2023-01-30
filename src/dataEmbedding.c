/*
 * @Author: B1ank
 * @Date: 2022-12-21 00:04:14
 * @LastEditTime: 2023-01-13 00:11:54
 * @LastEditors: your name
 * @Description: The implementation for data embedding operations
 * @FilePath: /FTCR-LMPPDA/src/dataEmbedding.c
 */

#include "dataEmbedding.h"
#include <math.h>
#include <string.h>
#include <stdio.h>


void originDataEmbedding(poly *a, uint64_t origindata, uint64_t system){
    a->N = 20;
    uint64_t index=0;
    while(origindata != 0) {
        a->coeffs[index] = origindata % system;
        index++;
        origindata /= system;
    }
}

void dataEmbeddingInSequence(poly *a, uint64_t origindata, uint64_t system, uint64_t sequenceNumber){
    uint64_t index = 0;
    while(origindata != 0) {
        a->coeffs[sequenceNumber+index] = origindata % system;
        index++;
        origindata /= system;
    }
}

void showAllDataEmbedded(poly *a){
    uint64_t index;
    printf("Show all data embedded:\n");
    for(index=0;index<a->N;index++) {
        printf("%ld ", a->coeffs[index]);
    }
    printf("\n");
}

uint64_t originDataExtraction(poly *a, uint64_t system){
    uint64_t N = a->N;
    uint64_t index;
    uint64_t finalResult = 0;
    for(index=0;index<N;index++){
        finalResult += (a->coeffs[index])*pow(system, index);
    }
    return finalResult;
}

uint64_t dataExtractionInSequence(poly *a, uint64_t blockLength, uint64_t system){
    uint64_t index1, index2, blockCount;
    uint64_t blockNumber = a->N / blockLength;
    uint64_t finalResult = 0;
    poly b;
    polyZeroing(&b, blockLength);
    for(index1=0;index1<blockLength;index1++){
        for(blockCount=0;blockCount<blockNumber;blockCount++){
            b.coeffs[index1] += a->coeffs[blockCount*blockLength+index1];
        }
    }

    for(index2=0;index2<blockLength;index2++){
        finalResult += b.coeffs[index2]*pow(system, index2);
    }
    return finalResult;
}

