/*** 
 * @Author: B1ank
 * @Date: 2023-01-17 00:31:52
 * @LastEditTime: 2023-01-17 00:49:42
 * @LastEditors: your name
 * @Description: Performance evaluation of AES-256 algorithm with the help of the openssl library
 * @FilePath: /FTCR-LMPPDA/src/otherAlgorithmComparison/AES.h
 */

#ifndef AES_H
#define AES_H

#include <openssl/aes.h>

/*** 
 * @description: The transformation from string to hexString
 * @param {char} *str
 * @return {unsigned char*}
 */
unsigned char* str2hex(char *str);

/*** 
 * @description: Performance evaluation function of AES-256
 * @return {*}
 */
void AES256PerformanceEvaluation();


#endif
