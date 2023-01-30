/*
 * @Author: B1ank
 * @Date: 2022-12-22 19:38:32
 * @LastEditTime: 2023-01-29 00:53:41
 * @LastEditors: your name
 * @Description: Test for poly operations
 * @FilePath: /FTCR-LMPPDA/test/test.c
 */

#include <stdio.h>
#include <stdint.h>
#include "testPoly.h"
#include "testDGS.h"
#include "testNumberCRT.h"
#include "testZeroSumRandomNumber.h"
#include "testDilithium.h"
#include "testPH-NTRU.h"
#include <math.h>

int main(int argc, char** argv) {
    printf("Running tests...\n");
    printf(">>>>>>>>>>>>Test Block1: polynomial operations test<<<<<<<<<<<<\n");
    uint8_t pass = testPoly();
    printf(">>>>>>>>>>>>Test Block2: DGS test<<<<<<<<<<<<\n");
    pass &= testDiscreteGaussianSampler();
    printf(">>>>>>>>>>>>Test Block3: numberCRT operations test<<<<<<<<<<<<<\n");
    pass &= testNumberCRT();
    printf(">>>>>>>>>>>>Test Block4: zeroSum operations test<<<<<<<<<<<<\n");
    pass &= testZeroSumRandomNumber();
    printf(">>>>>>>>>>>>Test Block5: Dilithium signature test<<<<<<<<<<<<\n");
    pass &= testDilithium();
    printf(">>>>>>>>>>>>Test Block6: PH-NTRU algorithm test<<<<<<<<<<<<\n");
    pass &= testPHNTRU();
    printf("%s\n", pass?"All tests passed":"One or more tests failed");
    return pass ? 0 : 1;
}