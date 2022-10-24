import random
import math
from line_profiler import LineProfiler


# 生成评估过程所用参数
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    maxBits = math.ceil(math.log2(smNumber))+dataUpperBound
    # maxBits = 12
    return (smNumber, dimensionAccount, dataUpperBound, maxBits)

# 生成评估所用随机原始数据
def dataGeneration(dimensionAccount):
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # 打印输出智能电表收集的原始数据
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i], end = " ")
    return originDataInSmartMeter

# 数据嵌入过程
def dataInsertDP(maxBits, dimensionAccount, originDataInSmartMeter):
    transformedResult = 0
    for index in range(dimensionAccount):
        # 将十进制数据转换为二进制数据
        binaryString = bin(originDataInSmartMeter[index])[2:]
        # 完成二进制级联
        binaryString += "0"*(maxBits*(index))
        # 还原为十进制数据
        transformedResult += int(binaryString, 2)
    return transformedResult

# 数据还原过程
def dataInsertDR(aggregatedResult, dimensionAccount, maxBits):
    multidimensionAggregatedDataList = []
    # 二进制编码
    binaryString = bin(aggregatedResult)[2:]
    # 从低位到高位循环遍历
    for index in range(dimensionAccount):
        theta1 = maxBits*(index+1)
        theta2 = maxBits*index
        # 截取对应维度二进制数据
        blockedBinaryString = binaryString[theta2: theta1-1]
        # 转换为十进制
        multidimensionAggregatedDataList.append(int(blockedBinaryString, 2))
    return multidimensionAggregatedDataList

def main():
    # 生成算法相关参数
    smNumber, dimensionAccount, dataUpperBound, maxBits = paramsGeneration()
     # 生成smNumber对原始数据并执行数据转换算法
    aggregatedResult = 0
    for i in range(smNumber):
        # 生成原始数据
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # 执行数据嵌入
        transformedResult = dataInsertDP(maxBits=maxBits, dimensionAccount=dimensionAccount, originDataInSmartMeter=originDataInSmartMeter)
        # 执行单维数据加法
        aggregatedResult += transformedResult
    # 嵌入数据提取
    aggregatedMultidimensinDataList = dataInsertDR(aggregatedResult=aggregatedResult, dimensionAccount=dimensionAccount, maxBits=maxBits)
    # 打印聚合后的数据结果 
    for i in range(dimensionAccount):
        print(aggregatedMultidimensinDataList[i])


if __name__ == "__main__":
    
    lp = LineProfiler()
    
    lp.add_function(dataInsertDP)
    lp.add_function(dataInsertDR)
    
    test_func = lp(main)
    test_func()
    lp.print_stats()


