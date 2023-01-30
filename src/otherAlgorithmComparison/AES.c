/*
 * @Author: B1ank
 * @Date: 2023-01-17 00:31:56
 * @LastEditTime: 2023-01-17 16:30:32
 * @LastEditors: your name
 * @Description: The C implementaion of performance evaluation of AES-256
 * @FilePath: /FTCR-LMPPDA/src/otherAlgorithmComparison/AES.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "AES.h"
#define AESKEY "df98b715d5c6ed2b25817b6f255411a1"
#define AESIV "2841ae97419c2973296a0d4bdfe19a4f"

// /*** 
//  * @description: The transformation from string to hexString
//  * @param {char} *str
//  * @return {unsigned char*}
//  */
unsigned char* str2hex(char *str)	
 {
    unsigned char *ret = NULL;
    int str_len = strlen(str);
    int i;
    assert((str_len%2) == 0);
    ret = (char *)malloc(str_len/2);
    for (i =0;i < str_len; i = i+2 ) 
    {
        sscanf(str+i,"%2hhx",&ret[i/2]);
    }
    return ret;
}

// /*** 
//  * @description: Performance evaluation function of AES-256
//  * @return {*}
//  */

void AES256PerformanceEvaluation()
{
    AES_KEY encryptKey;
    AES_KEY decryptKey;

    struct timespec begin1, end1, begin2, end2;
    long seconds1, nanoseconds1;
    long seconds2, nanoseconds2;
    double AES256EncryptREALTime, AES256EncryptCPUTime, AES256DecryptREALTime, AES256DecryptCPUTime;
    
    int executionCount;

    unsigned char *key;
    unsigned char *stdiv;
    int index;

    key = str2hex(AESKEY);
    stdiv = str2hex(AESIV);
    AES_set_encrypt_key(key,128,&encryptKey);
    AES_set_decrypt_key(key,128,&decryptKey);

    unsigned char plaintext[32];

    memcpy(plaintext, "AES encrypt in openssl demo", 27);
    memset(plaintext + 27, 0, 5);

    // Zero-padding is utilized here to ensure the length of plaintext is 32 bytes

    printf("=====Original Plaintext=====\n");
    for(index = 0; index < 32; index++)
    {
        printf("%02x ", plaintext[index]);
    }
    printf("\n" );

    unsigned char encryptedResult[32];

    memset(encryptedResult, 0, 32);
    unsigned char tmpiv[16];

    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin1);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    for (executionCount = 0; executionCount < 100; executionCount++) {
        memcpy(tmpiv, stdiv, 16);
        AES_cbc_encrypt(plaintext, encryptedResult, 32, &encryptKey, tmpiv, AES_ENCRYPT);
    }
    // Real time end
    clock_gettime(CLOCK_REALTIME, &end1);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    AES256EncryptREALTime = seconds1 + nanoseconds1*1e-9;
    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    AES256EncryptCPUTime = seconds2 + nanoseconds2*1e-9;

    AES256EncryptREALTime /= 100;
    AES256EncryptCPUTime /= 100;
    printf("AES-256 encrypt operation REALTime: %.10f\n", AES256EncryptREALTime);
    printf("AES-256 encrypt operation CPUTime: %.10f\n", AES256EncryptCPUTime);

    printf("=====Encrypted Result=====\n");
    for(index = 0; index < 32; index++)
    {
        printf("%02x ", encryptedResult[index]);
    }
    printf("\n" );


    unsigned char decryptedResult[32];

    memset(decryptedResult, 0, 32);

    // Real time set
    clock_gettime(CLOCK_REALTIME, &begin1);
    // CPU time set
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);
    for (executionCount = 0; executionCount < 100; executionCount++) {
        memcpy(tmpiv, stdiv, 16);
        AES_cbc_encrypt(encryptedResult, decryptedResult, 32, &decryptKey, tmpiv, AES_DECRYPT);
    }
    // Real time end
    clock_gettime(CLOCK_REALTIME, &end1);
    // CPU time end
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);
    // REALTIME count
    seconds1 = end1.tv_sec - begin1.tv_sec;
    nanoseconds1 = end1.tv_nsec - begin1.tv_nsec;
    AES256DecryptREALTime = seconds1 + nanoseconds1*1e-9;
    // CPUTIME count
    seconds2 = end2.tv_sec - begin2.tv_sec;
    nanoseconds2 = end2.tv_nsec - begin2.tv_nsec;
    AES256DecryptCPUTime = seconds2 + nanoseconds2*1e-9;

    AES256DecryptREALTime /= 100;
    AES256DecryptCPUTime /= 100;
    printf("AES-256 decrypt operation REALTime: %.10f\n", AES256DecryptREALTime);
    printf("AES-256 decrypt operation CPUTime: %.10f\n", AES256DecryptCPUTime);

    printf("=====Decrypted Result=====\n");
    for(index = 0; index < 32; index++)
    {
        printf("%02x ", decryptedResult[index]);
    }
    printf("\n" );
}