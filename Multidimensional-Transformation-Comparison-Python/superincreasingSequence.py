import random
import libnum
from line_profiler import LineProfiler


# 生成评估过程所用参数
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    q = libnum.generate_prime(128)
    return (smNumber, dimensionAccount, dataUpperBound, q)

# 生成评估所用随机原始数据
def dataGeneration(dimensionAccount):
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # 打印输出智能电表收集的原始数据
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i], end = " ")
    return originDataInSmartMeter

# 初始化超递增序列
def superincreasingSequenceInit(dimensionAccount, smNumber, dataUpperBound, q):
    superincreasingSequence = []
    sumResult = 0
    for count in range(dimensionAccount):
        superincreasingSequence.append(pow((smNumber*pow(2, dataUpperBound)+1),count))
    for items in superincreasingSequence:
        sumResult += items
    assert(sumResult <= q)
    return superincreasingSequence

# 数据转换算法
def superincreasingSequenceDP(superincreasingSequence, origiDataInSmartMeter, dimensionAccount):
    transformedResult = 0
    for i in range(dimensionAccount): 
        transformedResult += superincreasingSequence[i]*origiDataInSmartMeter[i]
    return transformedResult

# 数据还原算法
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
    # 初始化超递增序列
    superincreasingSequence = superincreasingSequenceInit(dimensionAccount=dimensionAccount, smNumber=smNumber, dataUpperBound=dataUpperBound, q=q)
    # 生成smNumber对原始数据并执行数据转换算法
    aggregatedResult = 0
    for i in range(smNumber):
        # 生成原始数据
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # 执行数据维度转换
        transformedResult = superincreasingSequenceDP(superincreasingSequence=superincreasingSequence, origiDataInSmartMeter=originDataInSmartMeter, dimensionAccount=dimensionAccount)
        # 执行单维数据加法
        aggregatedResult += transformedResult
    # 数据维度分离
    aggregatedMultidimensinDataList = superincreasingSequenceDR(dimensionAccount=dimensionAccount, superincreasingSequence=superincreasingSequence, aggregatedOneDimensinData=aggregatedResult)
    # 打印聚合后的数据结果 
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
    