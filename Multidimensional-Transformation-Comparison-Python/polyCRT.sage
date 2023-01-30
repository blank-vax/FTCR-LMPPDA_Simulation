/*
 * @Author: Blank-vax 15554467517@163.com
 * @Date: 2023-01-30 01:18:07
 * @LastEditors: Blank-vax 15554467517@163.com
 * @LastEditTime: 2023-01-30 11:59:22
 * @FilePath: /FTCR-LMPPDA_Simulation/Multidimensional-Transformation-Comparison-Python/polyCRT.sage
 * @Description: Efficiency evaluation for polynomial CRT operations
 */

#coding=utf-8
import random
from line_profiler import LineProfiler
# Import all the related library from sagemath
from sage.all import *


# Parameters generation for evaluation
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    # q \equiv 1 (\mod 2n)
    n = 128
    primeQ = 2*n+1
    R.<x> = PolynomialRing(GF(primeQ, 'a'))
    return (smNumber, dimensionAccount, dataUpperBound, R)

# Random original data generation for evaluation
def dataGeneration(dimensionAccount):
    import random
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # Print the original data collected by smart meters
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i])
    return originDataInSmartMeter

# Polynomial vector TVector generation
def polynomialFractionDecomposition(QInverse, PVector, dimensionAccount):
    TVector = []
    fractionDecompositionResult = (QInverse).partial_fraction_decomposition(x)
    for index in dimensionAccount:
        TVector.append(fractionDecompositionResult[1][index]*PVector[index])
    return TVector
    

# Polynomial initialization stage, generation of polynomial vectors QVector, TVector and PVector
def polynomialCRTInit(ringR, dataUpperBound, dimensionAccount):
    PVector = []
    QVector = []
    R.<t> = PolynomialRing(GF(2, 'a'))
    # Generate k integrable polynomials, the integrable polynomials with the highest coefficient term of 1 must be coprime
    for index in range(dimensionAccount):
        PVector.append(ringR.irreducible_element(dataUpperBound+1, algorithm='random'))
    # Polynomial list sorting
    PVector.sort()
    # Compute the product of k integrable polynomials
    Q = 1*t^0
    for index2 in range(dimensionAccount):
        Q *= PVector[index2]
    # Compute Qi(x)
    for index3 in range(dimensionAccount):
        QVector.append(Q // PVector[index3])
    # Compute 1/Q(x)
    QInverse = 1 / Q
    TVector = polynomialFractionDecomposition(QInverse=QInverse, PVector=PVector, dimensionAccount=dimensionAccount)
    return (QVector, TVector, PVector)
    
# Data conversion phase, performing polynomial multiplication and addition
def polynomialCRTDP(ringR, dimensionAccount, originDataInSmartMeter, TVector, QVector):
    R.<x> = PolynomialRing(GF(2, 'a'))
    oneDimensionPolynomial = 0*x^0
    oneDimensionPolynomial = oneDimensionPolynomial.change_ring(ringR)
    # Data transformation from multidimensional data to single dimension data 
    for index in range(dimensionAccount):
        dataPolynomialMapped = 0*x^0
        power = 0
        binaryString = bin(originDataInSmartMeter[index])[2:]
        for index2 in range(len(binaryString)-1, -1, -1):
            dataPolynomialMapped += int(binaryString[index2])*x^(power)
            power += 1
        dataPolynomialMapped = dataPolynomialMapped.change_ring(ringR)
        oneDimensionPolynomial += dataPolynomialMapped*TVector[index]*QVector[index]
    return oneDimensionPolynomial

# Reduction of polynomials to original data
def constructDecimalDataWithPolynomial(polynomialResult):
    polynomialList = polynomialResult.list()
    polynomialListString = "".join([str(x) for x in polynomialList])
    decimalData = int(polynomialListString, 2)
    return decimalData
    
# Multidimensional data reduction phase, performing polynomial modulo operations
def polynomialCRTDR(PVector, aggregatedResultPolynomial, dimensionAccount):
    multidimensionDataResults = []
    for index in range(dimensionAccount):
        polynomialResult = aggregatedResultPolynomial % PVector[index]
        print(polynomialResult)
        multidimensionDataResults.append(constructDecimalDataWithPolynomial(polynomialResult=polynomialResult))
    return multidimensionDataResults    

def main():
    # Parameters generation
    smNumber, dimensionAccount, dataUpperBound, R = paramsGeneration()
    # Initialization of polynomial CRT
    QVector, TVector, PVector = polynomialCRTInit(ringR=R, dataUpperBound=dataUpperBound, dimensionAccount=dimensionAccount)
    # Generation of smNumber and perform data transformation for original data
    R2.<x> = PolynomialRing(GF(2, 'a'))
    aggregatedResult = 0*t^0
    aggregatedResult = aggregatedResult.change_ring(R)
    for i in range(smNumber):
        # Original data generation
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # Data dimensions transformation
        transformedResult = polynomialCRTDP(ringR=R, dimensionAccount=dimensionAccount, originDataInSmartMeter=originDataInSmartMeter, TVector=TVector, QVector=QVector)
        # Addition operation for single dimension data 
        aggregatedResult += transformedResult
    # Data dimension separation
    aggregatedMultidimensinDataList = polynomialCRTDR(PVector=PVector, aggregatedResultPolynomial=aggregatedResult, dimensionAccount=dimensionAccount)
    # Print aggregation results
    for i in range(dimensionAccount):
        print(aggregatedMultidimensinDataList[i])


if __name__ == "__main__":
    
    lp = LineProfiler()
    
    lp.add_function(polynomialCRTInit)
    lp.add_function(polynomialCRTDP)
    lp.add_function(polynomialCRTDR)
    
    test_func = lp(main)
    test_func()
    lp.print_stats()
    
    
    