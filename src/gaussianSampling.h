/*** 
 * @Author: B1ank
 * @Date: 2022-12-22 22:45:46
 * @LastEditTime: 2022-12-23 19:40:09
 * @LastEditors: your name
 * @Description: The header definition file for discrete Gaussian distribution sampler
 * @FilePath: /FTCR-LMPPDA/src/gaussianSampling.h
 */

#ifndef GAUSSIAN_SAMPLING_H
#define GAUSSIAN_SAMPLING_H


#include "randombytes.h"
#include "fips202.h"
#include "cpucycles.h"
#include "poly.h"


/*** 
 * @description: Initialization of random number
 * @param {uint8_t} *x
 * @param {uint32_t} len
 * @return {*}
 */
void initRandom(uint8_t *x, uint32_t len);


/*** 
 * @description: Generation of the sampled polynomial with all coefficients
 * located in the discrete Gaussian distribution.
 * @param {poly} *r
 * @return {*}
 */

void samplingPolynomials(poly *r);

#endif