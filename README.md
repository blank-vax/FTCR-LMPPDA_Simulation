## Project Structure
### src
#### atomicComputationComparison

- `curveOperation.h`, `curveOperation.c`: number operations and curve operations efficiency evaluation, the number to be operated is a random number within 1000, introducing the $Type \ A$ curve in the `PBC` library to complete the curve operations efficiency evaluation.
- `fips202.h`, `fips202.c`: hash operations implementation reference, based on the public domain implementation in `crypto_hash/keccakc512/simple/` from [Keccakc512Reference](http://bench.cr.yp.to/supercop.html) by Ronny Van Keer and the public domain "TweetFips202" implementation from [Fips202Reference](https://twitter.com/tweetfips202) by Gilles Van Assche, Daniel J. Bernstein, and Peter Schwabe.
- `matrixOperation.h`, `matrixOperation.h`: evaluate the effciency of matrix/vector addition/multiplication operations with the help of the `Eigen` library, focusing on the efficiency of atomic operations in the 18' Abdallah et al. scheme and the 21' Qian et al. scheme.
- `atomicCompuationComparison.c`/`atomicComputationComparison.cpp`: the main function of the atomic operation evaluation, which can be written to adapt the **cpp file** to the matrix operations evaluation function to complete the evaluation of **the efficiency of matrix operations** or the **C file** to adapt the curve operations evaluation function to complete the evaluation of **the efficiency of curve operations**.

Complie Options: 

- cpp file: `g++ -fdiagnostics-color=always -g ${workspaceFolder}/src/atomicComputationComparison/*.cpp -o ${fileDirname}/${fileBasenameNoExtension}`.
- C file: `gcc -fdiagnostics-color=always -g ${workspaceFolder}/src/atomicComputationComparison/*.c -lgmp -lpbc -I/usr/local/include/pbc -o ${fileDirname}/${fileBasenameNoExtension}`, where the include path after the option `-I` could be replaced by your own include path.
#### otherAlgorithmComparison

- `AES.h`, `AES.c`: the C implementation of performance evaluation of $AES-256$ symmetric algorithm with the help of `openssl/aes.h`.
- `otherAlgorithmsTest.c`: the entry function for AES efficiency evaluation function.

Compile Options:
`gcc -fdiagnostics-color=always -g ${workspaceFolder}/src/otherAlgorithmComparison/*.c -lssl -lcrypto -o ${fileDirname}/${fileBasenameNoExtension}`
#### Building Blocks for FTCR-LMPPDA

- `cpucycles.h`, `cpucycles.c`: CPU operations utilized in the `gaussianSampling` files, which achieves sampling acceleration using assembly instructions.
- `dataEmbedding.h`, `dataEmbedding.c`: receive the specified binary and convert the original decimal numbers to polynomial coefficients in that binary (including coefficients embedding and extraction), supporting the **specified embedding position**.
- `Dilithium.h`, `Dilithium.c`: the implementation of Dilithium signature with the help of `liboqs` library, including **the key generation, signature generation and verification process**.
- `fips202.h`, `fips202.c`:  hash operations implementation reference.
- `Fisher-YatesShuffle.h`, `Fisher-YatesShuffle.c`: the implementation of FYS shuffle for the input array.
- `gaussianSampling.h`, `gaussianSampling.c`: **discrete Gaussian sampling operations** to figure out the coefficients of sampled polynomials, whose coefficients are located in $[4,6)$ .
- `numberCRT.h`, `numberCRT.c`: the implementation of Chinese Remainder Theorem for numbers, including **the initialization stage, the data process stage and the data recovery stage**. **TODO**: import `Miracl`library to achieve the operations on large number.
- `params.h`: parameters in FTCR-LMPPDA scheme, including parameters for $PH-NTRU$ , parameters for $Dilithium$ and other general limitiations to ensure proper system operations.
- `PH-NTRU.h`, `PH-NTRU.c`: the implementation of $PH-NTRU$ cryptosystem, including **the key generation(public key & private key), the encryption process and related decryption process, finally the homomorphic addition operation**.
-  `poly.h`, `poly.c`: the implementation for polynomials defination and operations utilized in $PH-NTRU$ implementation and throughout the whole scheme.
- `randombytes.h`, `randombytes.c`: random bytes generation algorithm for specific bytes length.
- `zeroSumRandomNumber.h`, `zeroSumRandomNumber.c`: the implementation of the generation and update process of zero-sum random number designed for the collusion resistance of different participants.

Compile Options: 
```makefile
# Makefile for FTCR-LMPPDA program
# The executable file is shown as ./FTCR-LMPPDA1.00 in Linux system
VERSION =1.00
CC =gcc
DEBUG =-DUSE_DEBUG
CFLAGS =-Wall -O

SOURCES =$(wildcard ./*.c)
INCLUDES =-I/usr/include/
LIB_NAMES =-lm -loqs
LIB_PATH =-L/usr/local/lib/


OBJ =$(patsubst %.c, %.o, $(SOURCES))
TARGET =FTCR-LMPPDA

# compile
%.o: %.c
$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

# links
$(TARGET):$(OBJ)
$(CC) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o ./$(TARGET)$(VERSION)
@rm -rf $(OBJ)


.PHONY:clean
clean:
@echo "Remove linked and compiled files....."
rm -rf $(OBJ) $(TARGET) ./
```
The final executable file could be found as `FTCR-LMPPDA1.00` in the path `/src/`.
### test

- `testDGS.h`, `testDGS.c`: the tests for discrete Gaussian distribution sampler.
- `testDilithium.h`, `testDilithium.c`: the tests and usage of **Dilithium signature algorithm**.
- `testNumberCRT.h`, `testNumberCRT.c`: the tests and usage of **Chinese Remainder Theorem for numerical data**.
- `testPH-NTRU.h`, `testPH-NTRU.c`: the tests and usage of $PH-NTRU$ **cryptosystem**.
- `testZeroSumRandomNumber.h`, `testZeroSumRandomNumber.c`: the tests and usage of **the generation, distribution and update of the zero-sum random numbers**.

Compile Options:
```makefile
# Makefile for the test process for all unit, including discrete Gaussian Sampler, Dilihtium signature, numberCRT, PH-NTRU encryption, polynomial operations, 
# generation, distribution and update of zero-sum random numbers
VERSION =1.00
CC =gcc
DEBUG =-DUSE_DEBUG
CFLAGS =-Wall -O

SOURCES =$(wildcard ../src/*.c ./*.c)
INCLUDES =-I/usr/include/
LIB_NAMES =-lm -loqs
LIB_PATH =-L/usr/local/lib/


OBJ =$(patsubst %.c, %.o, $(SOURCES))
TARGET =unitTest

# compile
%.o: %.c
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

# links
$(TARGET):$(OBJ)
	$(CC) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o ./$(TARGET)$(VERSION)
	@rm -rf $(OBJ)


.PHONY:clean
clean:
	@echo "Remove linked and compiled files....."
	rm -rf $(OBJ) $(TARGET) ./

```
  The final executable file could be found as `unitTest1.00` in the path `/test/`.
### Multidimensional-Transformation-Comparison-Python
This folder holds Python and Sage scripts for evaluating the effciency of operations in **five types of transformation algorithms (data embedding and extraction, Horner's Rule, numerical Chinese Remainder Theorem, polynomial Chinese Remainder Theorem and super-increasing sequence) utilized between multidimensional data and single dimensional data**. The specific analysis results are stored in `/Multidimensional-Transformation-Comparison-Python/Multidimensional-Transformation-Comparision-Result.md`.

- `atomicOperating.py`: the efficiency evaluation of atomic operations including **addition, multiplication, division, modular and modular inverse** with the help of `line_profiler` library in Python.
- `dataInsert.py`: the efficiency evaluation of data embedding and extraction operations, including **data embedding and data extraction**.
- `hornerRule.py`: the efficiency evaluation of Horner's Rule, including **initialization, data process and data recovery stages**.
- `numberCRT.py`: the efficiency evaluation of Chinese Remainder Theorem for numerical data with the help of `libnum` and `gmpy2` library.
- `polyCRT.sage`: the efficiency evaluation of Chinese Remainder Theorem for polynomial data coded in Sage script.
- `superincreasingSequence.py`: the efficiency evaluation of super-increasing sequence with the help of `libnum` library.
- `Multidimensional-Transformation-Comparison-Result.md`: Markdown file where stores the efficiency evaluation results of five types of transformation methods.
## Quick Start

1. Protocol Construction
- To build the FTCR-LMPPDA raw protocol, download the `liboqs` library and execute the compile option, **placing the compiled generated header files under** `/usr/include/`** and the library files under **`/usr/local/lib`.
- Execute `make` command under `/src/`, after compile and link operations, the executable file `FTCR-LMPPDA1.00` could be found in `/src/`.
2. Unit Test

To test the operation of each module of the protocol, execute `make` command in `/test/` after completing the installation of `liboqs` library, after complie and link operations, the executable file `unitTest1.00` could be found in `/test/`.
## Efficiency Evaluation
### Evaluation Setting
| **Entity** | **Configuration** |
| --- | --- |
| Raspberry Pi |  |
| PC | Linux Ubuntu 18.04.1 Intel(R) Core(TM) i7-10700 CPU @ 2.90GHz and 4G memory |
| Aliyun Cloud Server |  |

### Results & Conclusion

## Others
### Libraries
The installation addresses and documatations of all third-party libraries utilized in our project are listed below:
#### Multidimensional transformation comparison 

1. `line_profiler`
- Installation: `pip3 install line_profiler`;
- Reference: [Usage of line_profile](https://blog.csdn.net/weixin_42245157/article/details/125415104);
2. `libnum`& `gmpy2`

Installation: `pip3 install libnum`, `pip3 install gmpy2`;

3. `Sagemath`
- Tutorial: [Sagemath Tutorial](https://doc.sagemath.org/pdf/en/tutorial/sage_tutorial.pdf);
- Reference: [Official Website of Sagemath](https://www.sagemath.org/);
- Installation: [Installation and usage of Sage in Ubuntu20.04](https://blog.csdn.net/A33280000f/article/details/128052272);
#### Original Protocol & Unit Test
`liboqs`: [liboqsReference](https://github.com/open-quantum-safe/liboqs); 
#### Other algorithm comparison
`OpenSSL`: [OpenSSL](https://github.com/openssl/openssl), [Official Website of OpenSSL](https://www.openssl.org/); 
`pqNTRUSign`: [pqNTRUSign](https://github.com/zhenfeizhang/pqNTRUSign)
#### Atomic computation comparison

1. `PBC`
- Installation: [PBC environment configuration in Linux](https://www.cnblogs.com/burymyname/p/12061212.html);
- Tutorial: 《基于配对的密码学》;
- Reference: [pbc in Github](https://github.com/blynn/pbc); 
2. `Eigen`
- Installation: [The introduction, installation and usage of Eigen](https://zhuanlan.zhihu.com/p/462494086)
- Reference: [Eigen in Github](https://github.com/PX4/eigen); 
