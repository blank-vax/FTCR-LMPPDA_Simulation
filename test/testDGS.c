/*
 * @Author: B1ank
 * @Date: 2022-12-23 15:25:52
 * @LastEditTime: 2022-12-23 23:00:42
 * @LastEditors: your name
 * @Description: The implementation for tests of discrete Gaussian distribution sampler
 * @FilePath: /FTCR-LMPPDA/test/testDGS.c
 */
#include <stdio.h>
#include "testDGS.h"
#include "../src/dataEmbedding.h"

uint8_t testDiscreteGaussianSampler(){

    uint8_t valid = 1;
    poly result;
    polyZeroing(&result, 128);
    samplingPolynomials(&result);
    showAllDataEmbedded(&result);

    printf("Discrete Gaussian sampler test: %s\n", valid == 1 ? "SUCCESS" : "FAILED");
    return valid;
}
