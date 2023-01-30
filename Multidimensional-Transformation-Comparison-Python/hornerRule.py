'''
Author: Blank-vax 15554467517@163.com
Date: 2023-01-30 01:18:07
LastEditors: Blank-vax 15554467517@163.com
LastEditTime: 2023-01-30 11:37:17
FilePath: /FTCR-LMPPDA_Simulation/Multidimensional-Transformation-Comparison-Python/hornerRule.py
Description: Efficiency evaluation of Horner's Rule
'''
import random
import gmpy2
from line_profiler import LineProfiler


# Parameters generation for evaluation
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    return (smNumber, dimensionAccount, dataUpperBound)

# Original random number generation for evaluation
def dataGeneration(dimensionAccount):
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # Print the original data collected by smart meters
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i], end = " ")
    return originDataInSmartMeter


# Initialization of Horner's Rule
def HornerRuleInit(smNumber, dataUpperBound, dimensionAccount):
    # For simplification, determine R as the first prime number not greater than nD
    nD = smNumber*pow(2,dataUpperBound) - 1
    while True:
        # Prime test
        if gmpy2.is_prime(nD):
            break
        nD -= 1
    R = nD
    RVector = []
    # Generation of RVector = (R, R^2, R^3, ..., R^k)
    for i in range(dimensionAccount):
        RVector.append(R)
        R = R*nD
    return RVector

# Data process of Horner's Rule
def HornerRuleDP(RVector, originDataInSmartMeter, dimensionAccount):
    transformedResult = 0
    for j in range(dimensionAccount):
        transformedResult += RVector[j]*originDataInSmartMeter[j]
    return transformedResult
    
# Data recovery of Horner's Rule
def HornerRuleDR(RVector, aggregatedOneDimensionData, dimensionAccount):
    multidimensionResultList = []
    X_0 = aggregatedOneDimensionData // RVector[0]
    for j in range(dimensionAccount):
        multidimensionResultList.append(X_0 % RVector[0])
        X_0 = X_0 // RVector[0]
    return multidimensionResultList
    

def main():
    # Parameters generation of algorithm
    smNumber, dimensionAccount, dataUpperBound = paramsGeneration()
    # Initialization of numerical CRT
    RVector = HornerRuleInit(smNumber=smNumber, dataUpperBound=dataUpperBound, dimensionAccount=dimensionAccount)
     # Generation of smNumber and perform data transformation for original data
    aggregatedResult = 0
    for i in range(smNumber):
        # Generation of original data 
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # Data dimensions transformation
        transformedResult = HornerRuleDP(RVector=RVector, originDataInSmartMeter=originDataInSmartMeter, dimensionAccount=dimensionAccount)
        # Addition for data of single dimension
        aggregatedResult += transformedResult
    # Data dimension separation
    aggregatedMultidimensinDataList = HornerRuleDR(RVector=RVector, aggregatedOneDimensionData=aggregatedResult, dimensionAccount=dimensionAccount)
    # Print the aggregation result
    for i in range(dimensionAccount):
        print(aggregatedMultidimensinDataList[i])


if __name__ == "__main__":
    
    lp = LineProfiler()
    
    lp.add_function(HornerRuleInit)
    lp.add_function(HornerRuleDP)
    lp.add_function(HornerRuleDR)
    
    test_func = lp(main)
    test_func()
    lp.print_stats()