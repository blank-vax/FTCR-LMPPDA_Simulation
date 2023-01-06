import random
import libnum
import gmpy2
from line_profiler import LineProfiler

# 生成评估过程所用参数
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    primeList = []
    # 生成k个12比特素数
    for i in range(dimensionAccount):
        primeList.append(libnum.generate_prime(12))
    return (smNumber, dimensionAccount, dataUpperBound, primeList)

# 生成评估所用随机原始数据
def dataGeneration(dimensionAccount):
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # 打印输出智能电表收集的原始数据
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i], end = " ")
    return originDataInSmartMeter

# 数值中国剩余定理初始化,生成alphaVector
def numberCRTInit(dimensionAccount, primeList):
    alphaVector = []
    Q = 1
    # 生成alpha向量
    for i in range(dimensionAccount):
        Q *= primeList[i]
    for i in range(dimensionAccount):
        Qi = Q // primeList[i]
        QiInverse = gmpy2.invert(gmpy2.mpz(Qi), gmpy2.mpz(primeList[i]))
        alphaVector.append(Qi*QiInverse)
    return (alphaVector, Q)

# 数值中国剩余定理数据转换
def numberCRTDP(dimensionAccount, originDataInSmartMeter, alphaVector, Q):
    oneDimensionData = 0
    for i in range(dimensionAccount):
        oneDimensionData += originDataInSmartMeter[i]*alphaVector[i]
    oneDimensionData = oneDimensionData % Q
    return oneDimensionData

# 数值中国剩余定理数据恢复
def numberCRTDR(aggregatedOneDimensionData, dimensionAccount, Q, primeList):
    aggregatedMultiDimensionDataList = []
    for index in range(dimensionAccount):
        aggregatedMultiDimensionDataList.append((aggregatedOneDimensionData % Q) % primeList[index])
    return aggregatedMultiDimensionDataList


def main():
    # 生成算法相关参数
    smNumber, dimensionAccount, dataUpperBound, primeList = paramsGeneration()
    # 数值中国剩余定理初始化
    alphaVector, Q = numberCRTInit(dimensionAccount=dimensionAccount, primeList=primeList)
     # 生成smNumber对原始数据并执行数据转换算法
    aggregatedResult = 0
    for i in range(smNumber):
        # 生成原始数据
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # 执行数据维度转换
        transformedResult = numberCRTDP(dimensionAccount=dimensionAccount, originDataInSmartMeter=originDataInSmartMeter, alphaVector=alphaVector, Q=Q)
        # 执行单维数据加法
        aggregatedResult += transformedResult
    # 数据维度分离
    aggregatedMultidimensinDataList = numberCRTDR(aggregatedOneDimensionData=aggregatedResult, dimensionAccount=dimensionAccount, Q=Q, primeList=primeList)
    # 打印聚合后的数据结果 
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
