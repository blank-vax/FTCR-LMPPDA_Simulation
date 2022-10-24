#coding=utf-8
import random
from line_profiler import LineProfiler
# 引入sagemath所有相关库
from sage.all import *


# 生成评估过程所用参数
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    # q \equiv 1 (\mod 2n)
    n = 128
    primeQ = 2*n+1
    R.<x> = PolynomialRing(GF(primeQ, 'a'))
    return (smNumber, dimensionAccount, dataUpperBound, R)

# 生成评估所用随机原始数据
def dataGeneration(dimensionAccount):
    import random
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # 打印输出智能电表收集的原始数据
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i])
    return originDataInSmartMeter

# 生成多项式向量TVector
def polynomialFractionDecomposition(QInverse, PVector, dimensionAccount):
    TVector = []
    fractionDecompositionResult = (QInverse).partial_fraction_decomposition(x)
    for index in dimensionAccount:
        TVector.append(fractionDecompositionResult[1][index]*PVector[index])
    return TVector
    

# 多项式初始化阶段,生成多项式向量QVector, TVector, PVector
def polynomialCRTInit(ringR, dataUpperBound, dimensionAccount):
    PVector = []
    QVector = []
    R.<t> = PolynomialRing(GF(2, 'a'))
    # 生成k个不可约多项式, 最高系数项为1的不可约多项式必互素
    for index in range(dimensionAccount):
        PVector.append(ringR.irreducible_element(dataUpperBound+1, algorithm='random'))
    # 多项式列表排序
    PVector.sort()
    # 计算k个不可约多项式乘积
    Q = 1*t^0
    for index2 in range(dimensionAccount):
        Q *= PVector[index2]
    # 计算Qi(x)
    for index3 in range(dimensionAccount):
        QVector.append(Q // PVector[index3])
    # 计算1/Q(x)
    QInverse = 1 / Q
    TVector = polynomialFractionDecomposition(QInverse=QInverse, PVector=PVector, dimensionAccount=dimensionAccount)
    return (QVector, TVector, PVector)
    
# 数据转换阶段, 执行多项式乘法与加法
def polynomialCRTDP(ringR, dimensionAccount, originDataInSmartMeter, TVector, QVector):
    R.<x> = PolynomialRing(GF(2, 'a'))
    oneDimensionPolynomial = 0*x^0
    oneDimensionPolynomial = oneDimensionPolynomial.change_ring(ringR)
    # 将多维度数据转换为单维度数据
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

# 将多项式还原为原始数据
def constructDecimalDataWithPolynomial(polynomialResult):
    polynomialList = polynomialResult.list()
    polynomialListString = "".join([str(x) for x in polynomialList])
    decimalData = int(polynomialListString, 2)
    return decimalData
    
# 多维数据还原阶段, 执行多项式模操作
def polynomialCRTDR(PVector, aggregatedResultPolynomial, dimensionAccount):
    multidimensionDataResults = []
    for index in range(dimensionAccount):
        polynomialResult = aggregatedResultPolynomial % PVector[index]
        print(polynomialResult)
        multidimensionDataResults.append(constructDecimalDataWithPolynomial(polynomialResult=polynomialResult))
    return multidimensionDataResults    

def main():
    # 生成算法相关参数
    smNumber, dimensionAccount, dataUpperBound, R = paramsGeneration()
    # 多项式中国剩余定理初始化
    QVector, TVector, PVector = polynomialCRTInit(ringR=R, dataUpperBound=dataUpperBound, dimensionAccount=dimensionAccount)
    # 生成smNumber对原始数据并执行数据转换算法
    R2.<x> = PolynomialRing(GF(2, 'a'))
    aggregatedResult = 0*t^0
    aggregatedResult = aggregatedResult.change_ring(R)
    for i in range(smNumber):
        # 生成原始数据
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # 执行数据维度转换
        transformedResult = polynomialCRTDP(ringR=R, dimensionAccount=dimensionAccount, originDataInSmartMeter=originDataInSmartMeter, TVector=TVector, QVector=QVector)
        # 执行单维数据加法
        aggregatedResult += transformedResult
    # 数据维度分离
    aggregatedMultidimensinDataList = polynomialCRTDR(PVector=PVector, aggregatedResultPolynomial=aggregatedResult, dimensionAccount=dimensionAccount)
    # 打印聚合后的数据结果 
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
    
    
    