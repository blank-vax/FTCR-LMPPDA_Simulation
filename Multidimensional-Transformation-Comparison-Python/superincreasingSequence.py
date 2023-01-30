'''
Author: Blank-vax 15554467517@163.com
Date: 2023-01-30 01:18:07
LastEditors: Blank-vax 15554467517@163.com
LastEditTime: 2023-01-30 12:03:54
FilePath: /FTCR-LMPPDA_Simulation/Multidimensional-Transformation-Comparison-Python/superincreasingSequence.py
Description: Efficiency evaluation for superincreasing sequence operations
'''
import random
import libnum
from line_profiler import LineProfiler


# Parameters generation for evaluation
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    q = libnum.generate_prime(128)
    return (smNumber, dimensionAccount, dataUpperBound, q)

# Random original data generation for evaluation
def dataGeneration(dimensionAccount):
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # Print original data collected by smart meters
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i], end = " ")
    return originDataInSmartMeter

# Initialization of superincreasing sequence
def superincreasingSequenceInit(dimensionAccount, smNumber, dataUpperBound, q):
    superincreasingSequence = []
    sumResult = 0
    for count in range(dimensionAccount):
        superincreasingSequence.append(pow((smNumber*pow(2, dataUpperBound)+1),count))
    for items in superincreasingSequence:
        sumResult += items
    assert(sumResult <= q)
    return superincreasingSequence

# Data transformation 
def superincreasingSequenceDP(superincreasingSequence, origiDataInSmartMeter, dimensionAccount):
    transformedResult = 0
    for i in range(dimensionAccount): 
        transformedResult += superincreasingSequence[i]*origiDataInSmartMeter[i]
    return transformedResult

# Data recovery
def superincreasingSequenceDR(dimensionAccount,superincreasingSequence, aggregatedOneDimensinData):
    aggregatedMultiDimensionDataList = [0]*dimensionAccount
    originNumber = aggregatedOneDimensinData
    for index in range(dimensionAccount-1, 0, -1):
        tmpNumber = originNumber % superincreasingSequence[index]
        aggregatedMultiDimensionDataList[index] = (originNumber - tmpNumber) / superincreasingSequence[index]
        originNumber = tmpNumber
    aggregatedMultiDimensionDataList[0] = originNumber
    return aggregatedMultiDimensionDataList


def main():
    smNumber, dimensionAccount, dataUpperBound, q = paramsGeneration()
    # Initialization of superincreasing sequence
    superincreasingSequence = superincreasingSequenceInit(dimensionAccount=dimensionAccount, smNumber=smNumber, dataUpperBound=dataUpperBound, q=q)
    # Generation of smNumber and perform data transformation for original data
    aggregatedResult = 0
    for i in range(smNumber):
        # Generation of original data
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # Data dimensions transformation
        transformedResult = superincreasingSequenceDP(superincreasingSequence=superincreasingSequence, origiDataInSmartMeter=originDataInSmartMeter, dimensionAccount=dimensionAccount)
        # Addition for data of single dimension
        aggregatedResult += transformedResult
    # Data dimension separation
    aggregatedMultidimensinDataList = superincreasingSequenceDR(dimensionAccount=dimensionAccount, superincreasingSequence=superincreasingSequence, aggregatedOneDimensinData=aggregatedResult)
    # Print aggregation result 
    for i in range(dimensionAccount):
        print(aggregatedMultidimensinDataList[i])
    

if __name__ == "__main__":
    
    lp = LineProfiler()
    
    lp.add_function(superincreasingSequenceInit)
    lp.add_function(superincreasingSequenceDP)
    lp.add_function(superincreasingSequenceDR)
    
    test_func = lp(main)
    test_func()
    lp.print_stats()
    