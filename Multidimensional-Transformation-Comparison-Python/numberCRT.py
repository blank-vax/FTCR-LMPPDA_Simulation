'''
Author: Blank-vax 15554467517@163.com
Date: 2023-01-30 01:18:07
LastEditors: Blank-vax 15554467517@163.com
LastEditTime: 2023-01-30 11:46:43
FilePath: /FTCR-LMPPDA_Simulation/Multidimensional-Transformation-Comparison-Python/numberCRT.py
Description: Efficiency evaluation of numerical CRT operations
'''
import random
import libnum
import gmpy2
from line_profiler import LineProfiler

# Parameters generation for evaluation
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    primeList = []
    # Generation of k primes with 12 bits
    for i in range(dimensionAccount):
        primeList.append(libnum.generate_prime(12))
    return (smNumber, dimensionAccount, dataUpperBound, primeList)

# Random original data generation for evaluation
def dataGeneration(dimensionAccount):
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # Print the original data collected by smart meters
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i], end = " ")
    return originDataInSmartMeter

# Initialization of numerical CRT, generation of alphaVector
def numberCRTInit(dimensionAccount, primeList):
    alphaVector = []
    Q = 1
    # Generation of the alpha vector
    for i in range(dimensionAccount):
        Q *= primeList[i]
    for i in range(dimensionAccount):
        Qi = Q // primeList[i]
        QiInverse = gmpy2.invert(gmpy2.mpz(Qi), gmpy2.mpz(primeList[i]))
        alphaVector.append(Qi*QiInverse)
    return (alphaVector, Q)

# Data process in numerical CRT
def numberCRTDP(dimensionAccount, originDataInSmartMeter, alphaVector, Q):
    oneDimensionData = 0
    for i in range(dimensionAccount):
        oneDimensionData += originDataInSmartMeter[i]*alphaVector[i]
    oneDimensionData = oneDimensionData % Q
    return oneDimensionData

# Data recovery in numerical CRT
def numberCRTDR(aggregatedOneDimensionData, dimensionAccount, Q, primeList):
    aggregatedMultiDimensionDataList = []
    for index in range(dimensionAccount):
        aggregatedMultiDimensionDataList.append((aggregatedOneDimensionData % Q) % primeList[index])
    return aggregatedMultiDimensionDataList


def main():
    # Parameters generation 
    smNumber, dimensionAccount, dataUpperBound, primeList = paramsGeneration()
    # Initialization of numerical CRT
    alphaVector, Q = numberCRTInit(dimensionAccount=dimensionAccount, primeList=primeList)
    # Generation of smNumber and perform data transformation for original data
    aggregatedResult = 0
    for i in range(smNumber):
        # Generation of original data
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # Perform dimensions transformation operations
        transformedResult = numberCRTDP(dimensionAccount=dimensionAccount, originDataInSmartMeter=originDataInSmartMeter, alphaVector=alphaVector, Q=Q)
        # Addition for data of single dimension 
        aggregatedResult += transformedResult
    # Data dimension separation
    aggregatedMultidimensinDataList = numberCRTDR(aggregatedOneDimensionData=aggregatedResult, dimensionAccount=dimensionAccount, Q=Q, primeList=primeList)
    # Print aggregation result
    for i in range(dimensionAccount):
        print(aggregatedMultidimensinDataList[i])


if __name__ == "__main__":
    
    lp = LineProfiler()
    
    lp.add_function(numberCRTInit)
    lp.add_function(numberCRTDP)
    lp.add_function(numberCRTDR)
    
    test_func = lp(main)
    test_func()
    lp.print_stats()
