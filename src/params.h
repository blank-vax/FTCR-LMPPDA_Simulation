#ifndef PARAMS_H
#define PARAMS_H


// PH-NTRU algorithm

#define NTRU_N 1024
#define NTRU_INT_POLY_SIZE ((NTRU_N+16+7)&0xFFF8)
#define paramP 2

#define blockSize 100

#define originModulus 12289
#define dimensionNumber 10

#define participantsNumber 10
#define upperBoundOfEachDimension 4

// Aggregation rounds \Gamma = 10
#define aggregationRounds 10

// Dilithium parameters
// Length of publicKey, privateKey and signature in Dilithium3
#define publicKeyLengthForDilithium 1952
#define privateKeyLengthForDilithium 4000
#define signatureLengthForDilithium 3293


#endif