'''
Author: Blank-vax 15554467517@163.com
Date: 2023-01-30 01:18:07
LastEditors: Blank-vax 15554467517@163.com
LastEditTime: 2023-01-30 11:44:14
FilePath: /FTCR-LMPPDA_Simulation/Multidimensional-Transformation-Comparison-Python/dataInsert.py
Description: Efficiency evaluation for data embedding and data extraction operations
'''

import random
import math
from line_profiler import LineProfiler


# Paramerters generation for evaluation
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    maxBits = math.ceil(math.log2(smNumber))+dataUpperBound
    # maxBits = 12
    return (smNumber, dimensionAccount, dataUpperBound, maxBits)

# Random original data generation for evaluation
def dataGeneration(dimensionAccount):
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # Print the original data collected by smart meters
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i], end = " ")
    return originDataInSmartMeter

# Data embedding process
def dataInsertDP(maxBits, dimensionAccount, originDataInSmartMeter):
    transformedResult = 0
    for index in range(dimensionAccount):
        # Convert decimal data to binary data
        binaryString = bin(originDataInSmartMeter[index])[2:]
        # Binary cascade
        binaryString += "0"*(maxBits*(index))
        # Decimal data recovery
        transformedResult += int(binaryString, 2)
    return transformedResult

# Data extraction process
def dataInsertDR(aggregatedResult, dimensionAccount, maxBits):
    multidimensionAggregatedDataList = []
    # Binary coding
    binaryString = bin(aggregatedResult)[2:]
    # Iteration from low to high
    for index in range(dimensionAccount):
        theta1 = maxBits*(index+1)
        theta2 = maxBits*index
        # Intercept binary data in the corresponding location
        blockedBinaryString = binaryString[theta2: theta1-1]
        # Transformed to decimal data 
        multidimensionAggregatedDataList.append(int(blockedBinaryString, 2))
    return multidimensionAggregatedDataList

def main():
    # Parameters generation
    smNumber, dimensionAccount, dataUpperBound, maxBits = paramsGeneration()
    # Generation of smNumber and perform data transformation for original data
    aggregatedResult = 0
    for i in range(smNumber):
        # Generation of original data 
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # Perform data embedding
        transformedResult = dataInsertDP(maxBits=maxBits, dimensionAccount=dimensionAccount, originDataInSmartMeter=originDataInSmartMeter)
        # Perform addition operations for data of single dimention
        aggregatedResult += transformedResult
    # Data extraction of embedded data
    aggregatedMultidimensinDataList = dataInsertDR(aggregatedResult=aggregatedResult, dimensionAccount=dimensionAccount, maxBits=maxBits)
    # Print aggregation result
    for i in range(dimensionAccount):
        print(aggregatedMultidimensinDataList[i])


if __name__ == "__main__":
    
    lp = LineProfiler()
    
    lp.add_function(dataInsertDP)
    lp.add_function(dataInsertDR)
    
    test_func = lp(main)
    test_func()
    lp.print_stats()


